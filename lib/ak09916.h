#ifndef AK09916_H_
#define AK09916_H_

#ifdef MAG_DEVICE_AK09916

// AK09916 magnetometer — embedded in ICM-20948, accessed via I2C master
// I2C address on the auxiliary bus
#define AK09916_ADDR        0x0C

// Registers
#define AK09916_WIA         0x01  // Device ID (reads 0x09)
#define AK09916_ST1         0x10  // Status 1: bit0=DRDY, bit1=DOR
#define AK09916_HXL         0x11  // Measurement start — read 9 bytes: ST1,HXL–HZH,dummy,ST2
#define AK09916_ST2         0x18  // Status 2: bit3=HOFL — must read to unlock next sample
#define AK09916_CNTL2       0x31  // Control 2: operation mode
#define AK09916_CNTL3       0x32  // Control 3: bit0=SRST (soft reset)

// CNTL2 mode values
#define AK09916_MODE_OFF    0x00
#define AK09916_MODE_CONT1  0x02  //  10 Hz
#define AK09916_MODE_CONT2  0x04  //  20 Hz
#define AK09916_MODE_CONT3  0x06  //  50 Hz
#define AK09916_MODE_CONT4  0x08  // 100 Hz

// 0.15 µT per LSB (measurement range ±4912 µT, 16-bit output ±32752)
#define AK09916_SCALE       0.15f

#endif // MAG_DEVICE_AK09916
#endif // AK09916_H_
