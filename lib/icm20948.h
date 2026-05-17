#ifndef ICM20948_H_
#define ICM20948_H_

#ifdef IMU_DEVICE_ICM20948

#include <Wire.h>

// Default I2C address: AD0 high. Override in config.h if AD0 is pulled low.
#ifndef ICM20948_ADDR
    #define ICM20948_ADDR   0x69
#endif

// REG_BANK_SEL is 0x7F in every bank — bits [5:4] select bank 0-3
#define REG_BANK_SEL        0x7F

// Bank 0
#define B0_WHO_AM_I         0x00  // reads 0xEA
#define B0_USER_CTRL        0x03  // bit5: I2C_MST_EN
#define B0_PWR_MGMT_1       0x06  // bit7: reset, bit6: sleep, bits[2:0]: CLKSEL
#define B0_INT_STATUS_1     0x1A  // bit0: RAW_DATA_0_RDY
#define B0_ACCEL_XOUT_H     0x2D  // first of 12 bytes: AX,AY,AZ,GX,GY,GZ (big-endian)
#define B0_EXT_SLV_DATA_00  0x3B  // first of mag slave data bytes

// Bank 2
#define B2_GYRO_CONFIG_1    0x01  // bits[2:1]=FS_SEL, bit0=FCHOICE
#define B2_ACCEL_CONFIG     0x14  // bits[2:1]=FS_SEL, bit0=FCHOICE

// Bank 3
#define B3_I2C_MST_CTRL     0x01  // bits[3:0]=clock freq
#define B3_I2C_MST_DLY_CTL 0x02  // bit7=DELAY_ES_SHADOW
#define B3_I2C_SLV0_ADDR    0x03  // bit7=read(1)/write(0), bits[6:0]=slave addr
#define B3_I2C_SLV0_REG     0x04  // slave register to start from
#define B3_I2C_SLV0_CTRL    0x05  // bit7=enable, bits[3:0]=byte count
#define B3_I2C_SLV1_ADDR    0x07  // used to write a single byte to slave (e.g. mode register)
#define B3_I2C_SLV1_REG     0x08
#define B3_I2C_SLV1_CTRL    0x09
#define B3_I2C_SLV1_DO      0x0A  // data byte to write

// Sensitivity constants matching config below
// GYRO_CONFIG_1 = 0x01 → ±250 dps → 131 LSB/dps
#define GYRO_SCALE  (1.0f / 131.0f * 0.017453293f)  // rad/s per LSB
// ACCEL_CONFIG  = 0x03 → ±4g    → 8192 LSB/g
#define ACCEL_SCALE (1.0f / 8192.0f)                 // g per LSB

class ICM20948 {
public:
    bool begin() {
        // Hard reset
        writeReg(0, B0_PWR_MGMT_1, 0x80);
        delay(10);
        // Wake up, auto-select best clock (PLL if ready)
        writeReg(0, B0_PWR_MGMT_1, 0x01);
        delay(10);
        if (readReg(0, B0_WHO_AM_I) != 0xEA) return false;

        // Gyro: ±250 dps, FCHOICE=1 (enable DLPF), DLPFCFG=0 (BW≈197Hz)
        writeReg(2, B2_GYRO_CONFIG_1, 0x01);

        // Accel: ±4g, FCHOICE=1 (enable DLPF), DLPFCFG=0 (BW≈246Hz)
        // bits[2:1]=01 for ±4g, bit[0]=1 for FCHOICE
        writeReg(2, B2_ACCEL_CONFIG, 0x03);

        // Enable I2C master
        writeReg(0, B0_USER_CTRL, 0x20);
        delay(1);

        // I2C master clock: ~345 kHz (value 7 from Table 23)
        writeReg(3, B3_I2C_MST_CTRL, 0x07);

        // Delay shadow until all slave data received (cleaner reads)
        writeReg(3, B3_I2C_MST_DLY_CTL, 0x80);

        #ifdef MAG_DEVICE_AK09916
            // Write CNTL2=0x08 (100 Hz continuous) to AK09916 via SLV1
            writeReg(3, B3_I2C_SLV1_ADDR, AK09916_ADDR);         // write addr (RNW=0)
            writeReg(3, B3_I2C_SLV1_REG,  AK09916_CNTL2);
            writeReg(3, B3_I2C_SLV1_DO,   AK09916_MODE_CONT4);   // 100 Hz
            writeReg(3, B3_I2C_SLV1_CTRL, 0x81);                 // enable, 1 byte
            delay(10);

            // SLV0 reads 9 bytes continuously from AK09916 starting at ST1 (0x10):
            // [ST1, HXL, HXH, HYL, HYH, HZL, HZH, dummy, ST2]
            // Reading ST2 at byte[8] automatically unlocks the next sample.
            writeReg(3, B3_I2C_SLV0_ADDR, 0x80 | AK09916_ADDR);  // read addr (RNW=1)
            writeReg(3, B3_I2C_SLV0_REG,  AK09916_ST1);
            writeReg(3, B3_I2C_SLV0_CTRL, 0x89);                 // enable, 9 bytes
        #endif

        return true;
    }

    bool read(RawIMU& imu, RawMag& mag) {
        if (!(readReg(0, B0_INT_STATUS_1) & 0x01)) return false;

        // Burst-read 12 bytes: AX_H,AX_L, AY_H,AY_L, AZ_H,AZ_L,
        //                       GX_H,GX_L, GY_H,GY_L, GZ_H,GZ_L
        uint8_t buf[12];
        readBytes(0, B0_ACCEL_XOUT_H, buf, 12);

        imu.ax = (int16_t)((buf[0]  << 8) | buf[1])  * ACCEL_SCALE;
        imu.ay = (int16_t)((buf[2]  << 8) | buf[3])  * ACCEL_SCALE;
        imu.az = (int16_t)((buf[4]  << 8) | buf[5])  * ACCEL_SCALE;
        imu.gx = (int16_t)((buf[6]  << 8) | buf[7])  * GYRO_SCALE;
        imu.gy = (int16_t)((buf[8]  << 8) | buf[9])  * GYRO_SCALE;
        imu.gz = (int16_t)((buf[10] << 8) | buf[11]) * GYRO_SCALE;

        #ifdef MAG_DEVICE_AK09916
        {
            // Read 9 bytes: [ST1, HXL, HXH, HYL, HYH, HZL, HZH, dummy, ST2]
            // Mag data is little-endian (L byte first)
            uint8_t mb[9];
            readBytes(0, B0_EXT_SLV_DATA_00, mb, 9);
            if (mb[8] & 0x08) {
                // HOFL bit set in ST2 — magnetic overflow, discard sample
                mag.valid = false;
            } else {
                mag.mx = (int16_t)((mb[2] << 8) | mb[1]) * AK09916_SCALE;
                mag.my = (int16_t)((mb[4] << 8) | mb[3]) * AK09916_SCALE;
                mag.mz = (int16_t)((mb[6] << 8) | mb[5]) * AK09916_SCALE;
                mag.valid = true;
            }
        }
        #else
            mag.valid = false;
        #endif

        return true;
    }

private:
    void selectBank(uint8_t bank) {
        Wire.beginTransmission(ICM20948_ADDR);
        Wire.write(REG_BANK_SEL);
        Wire.write((bank & 0x03) << 4);
        Wire.endTransmission();
    }

    void writeReg(uint8_t bank, uint8_t reg, uint8_t val) {
        selectBank(bank);
        Wire.beginTransmission(ICM20948_ADDR);
        Wire.write(reg);
        Wire.write(val);
        Wire.endTransmission();
    }

    uint8_t readReg(uint8_t bank, uint8_t reg) {
        selectBank(bank);
        Wire.beginTransmission(ICM20948_ADDR);
        Wire.write(reg);
        Wire.endTransmission(false);
        Wire.requestFrom((uint8_t)ICM20948_ADDR, (uint8_t)1);
        return Wire.available() ? Wire.read() : 0;
    }

    void readBytes(uint8_t bank, uint8_t reg, uint8_t* buf, uint8_t len) {
        selectBank(bank);
        Wire.beginTransmission(ICM20948_ADDR);
        Wire.write(reg);
        Wire.endTransmission(false);
        Wire.requestFrom((uint8_t)ICM20948_ADDR, len);
        for (uint8_t i = 0; i < len && Wire.available(); i++) buf[i] = Wire.read();
    }
};

#endif // IMU_DEVICE_ICM20948
#endif // ICM20948_H_
