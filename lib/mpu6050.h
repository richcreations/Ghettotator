#ifndef MPU6050_H_
#define MPU6050_H_

#ifdef IMU_DEVICE_MPU6050

#include <Wire.h>

// Default I2C address: AD0 low. Override in config.h if AD0 is pulled high.
#ifndef MPU6050_ADDR
    #define MPU6050_ADDR    0x68
#endif

// Registers (single bank — no bank switching)
#define MPU_SMPLRT_DIV      0x19  // sample rate divider
#define MPU_CONFIG          0x1A  // DLPF_CFG
#define MPU_GYRO_CONFIG     0x1B  // bits[4:3]=FS_SEL
#define MPU_ACCEL_CONFIG    0x1C  // bits[4:3]=AFS_SEL
#define MPU_INT_STATUS      0x3A  // bit0=DATA_RDY_INT
#define MPU_ACCEL_XOUT_H    0x3B  // first of 14 bytes: AX,AY,AZ,TEMP,GX,GY,GZ (big-endian)
#define MPU_EXT_SENS_DATA   0x49  // first byte of I2C master read data
#define MPU_I2C_SLV0_ADDR   0x25  // bit7=RNW, bits[6:0]=slave addr
#define MPU_I2C_SLV0_REG    0x26  // slave register to start from
#define MPU_I2C_SLV0_CTRL   0x27  // bit7=enable, bits[3:0]=byte count
#define MPU_I2C_SLV1_ADDR   0x28
#define MPU_I2C_SLV1_REG    0x29
#define MPU_I2C_SLV1_CTRL   0x2A  // bit7=enable, bits[3:0]=byte count
#define MPU_I2C_SLV1_DO     0x64  // byte to write via SLV1
#define MPU_I2C_MST_CTRL    0x24  // bits[3:0]=clock (0x0D=400kHz)
#define MPU_I2C_MST_DLY     0x67  // bit7=DELAY_ES_SHADOW
#define MPU_USER_CTRL       0x6A  // bit5=I2C_MST_EN
#define MPU_PWR_MGMT_1      0x6B  // bit7=reset, bit6=sleep, bits[2:0]=CLKSEL
#define MPU_WHO_AM_I        0x75  // reads 0x68

// Sensitivity constants matching config below
// GYRO_CONFIG FS_SEL=0 → ±250 dps → 131.0 LSB/dps
#define MPU_GYRO_SCALE  (1.0f / 131.0f * 0.017453293f)  // rad/s per LSB
// ACCEL_CONFIG AFS_SEL=1 → ±4g → 8192 LSB/g
#define MPU_ACCEL_SCALE (1.0f / 8192.0f)                 // g per LSB

class MPU6050 {
public:
    bool begin() {
        // Hard reset
        writeReg(MPU_PWR_MGMT_1, 0x80);
        delay(100);
        // Wake up, select PLL with X-axis gyro as clock reference
        writeReg(MPU_PWR_MGMT_1, 0x01);
        delay(10);
        if (readReg(MPU_WHO_AM_I) != 0x68) return false;

        // DLPF_CFG=1 → accel BW 184Hz, gyro BW 188Hz
        writeReg(MPU_CONFIG, 0x01);

        // SMPLRT_DIV=0 → sample rate = gyro rate / (1+0) = 1kHz (with DLPF active)
        writeReg(MPU_SMPLRT_DIV, 0x00);

        // Gyro: FS_SEL=0 → ±250 dps, 131 LSB/dps
        writeReg(MPU_GYRO_CONFIG, 0x00);

        // Accel: AFS_SEL=1 → ±4g, 8192 LSB/g
        writeReg(MPU_ACCEL_CONFIG, 0x08);

        // Enable I2C master, disable bypass mode (already 0 after reset)
        writeReg(MPU_USER_CTRL, 0x20);
        delay(1);

        // I2C master clock: 400 kHz
        writeReg(MPU_I2C_MST_CTRL, 0x0D);

        // Delay shadow until all slave data received
        writeReg(MPU_I2C_MST_DLY, 0x80);

        #ifdef MAG_DEVICE_HMC5883L
            // Write Config A: 8-sample avg, 15 Hz, normal measurement
            writeSlv1(HMC5883L_ADDR, HMC_CONFIG_A, HMC_CFGA_8AVG_15HZ);
            delay(10);
            // Write Config B: GN=001 → 1090 LSB/Gauss
            writeSlv1(HMC5883L_ADDR, HMC_CONFIG_B, HMC_CFGB_1090);
            delay(10);
            // Write Mode: continuous measurement
            writeSlv1(HMC5883L_ADDR, HMC_MODE, HMC_MODE_CONTINUOUS);
            delay(50);
            // Disable SLV1 write transactions
            writeReg(MPU_I2C_SLV1_CTRL, 0x00);

            // SLV0 reads 6 bytes continuously from HMC5883L starting at XOUT_H (0x03):
            // [X_H, X_L, Z_H, Z_L, Y_H, Y_L]  — note Z before Y in HMC register map
            writeReg(MPU_I2C_SLV0_ADDR, 0x80 | HMC5883L_ADDR);  // read (RNW=1)
            writeReg(MPU_I2C_SLV0_REG,  HMC_XOUT_H);
            writeReg(MPU_I2C_SLV0_CTRL, 0x86);                   // enable, 6 bytes
        #endif

        return true;
    }

    bool read(RawIMU& imu, RawMag& mag) {
        if (!(readReg(MPU_INT_STATUS) & 0x01)) return false;

        // Burst-read 14 bytes: AX_H,AX_L, AY_H,AY_L, AZ_H,AZ_L, T_H,T_L,
        //                       GX_H,GX_L, GY_H,GY_L, GZ_H,GZ_L
        uint8_t buf[14];
        readBytes(MPU_ACCEL_XOUT_H, buf, 14);

        imu.ax = (int16_t)((buf[0]  << 8) | buf[1])  * MPU_ACCEL_SCALE;
        imu.ay = (int16_t)((buf[2]  << 8) | buf[3])  * MPU_ACCEL_SCALE;
        imu.az = (int16_t)((buf[4]  << 8) | buf[5])  * MPU_ACCEL_SCALE;
        // buf[6], buf[7] = temperature (skipped)
        imu.gx = (int16_t)((buf[8]  << 8) | buf[9])  * MPU_GYRO_SCALE;
        imu.gy = (int16_t)((buf[10] << 8) | buf[11]) * MPU_GYRO_SCALE;
        imu.gz = (int16_t)((buf[12] << 8) | buf[13]) * MPU_GYRO_SCALE;

        #ifdef MAG_DEVICE_HMC5883L
        {
            // Read 6 bytes: [X_H, X_L, Z_H, Z_L, Y_H, Y_L]
            // HMC5883L data registers order has Z before Y
            uint8_t mb[6];
            readBytes(MPU_EXT_SENS_DATA, mb, 6);

            int16_t mx = (int16_t)((mb[0] << 8) | mb[1]);
            int16_t mz = (int16_t)((mb[2] << 8) | mb[3]);
            int16_t my = (int16_t)((mb[4] << 8) | mb[5]);

            if (mx == HMC_OVERFLOW || my == HMC_OVERFLOW || mz == HMC_OVERFLOW) {
                mag.valid = false;
            } else {
                mag.mx = mx * HMC5883L_SCALE;
                mag.my = my * HMC5883L_SCALE;
                mag.mz = mz * HMC5883L_SCALE;
                mag.valid = true;
            }
        }
        #else
            mag.valid = false;
        #endif

        return true;
    }

private:
    void writeReg(uint8_t reg, uint8_t val) {
        Wire.beginTransmission(MPU6050_ADDR);
        Wire.write(reg);
        Wire.write(val);
        Wire.endTransmission();
    }

    uint8_t readReg(uint8_t reg) {
        Wire.beginTransmission(MPU6050_ADDR);
        Wire.write(reg);
        Wire.endTransmission(false);
        Wire.requestFrom((uint8_t)MPU6050_ADDR, (uint8_t)1);
        return Wire.available() ? Wire.read() : 0;
    }

    void readBytes(uint8_t reg, uint8_t* buf, uint8_t len) {
        Wire.beginTransmission(MPU6050_ADDR);
        Wire.write(reg);
        Wire.endTransmission(false);
        Wire.requestFrom((uint8_t)MPU6050_ADDR, len);
        for (uint8_t i = 0; i < len && Wire.available(); i++) buf[i] = Wire.read();
    }

    void writeSlv1(uint8_t addr, uint8_t reg, uint8_t val) {
        writeReg(MPU_I2C_SLV1_ADDR, addr);        // write direction (RNW=0)
        writeReg(MPU_I2C_SLV1_REG,  reg);
        writeReg(MPU_I2C_SLV1_DO,   val);
        writeReg(MPU_I2C_SLV1_CTRL, 0x81);        // enable, 1 byte
    }
};

#endif // IMU_DEVICE_MPU6050
#endif // MPU6050_H_
