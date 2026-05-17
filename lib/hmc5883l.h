#ifndef HMC5883L_H_
#define HMC5883L_H_

#ifdef MAG_DEVICE_HMC5883L

// HMC5883L 3-axis magnetometer
// Fixed I2C address (no address pin)
#define HMC5883L_ADDR       0x1E

// Registers
#define HMC_CONFIG_A        0x00  // bits[6:5]=MA averaging, bits[4:2]=DO rate, bits[1:0]=MS mode
#define HMC_CONFIG_B        0x01  // bits[7:5]=GN gain select
#define HMC_MODE            0x02  // bits[1:0]: 00=continuous, 01=single, 1x=idle
#define HMC_XOUT_H          0x03  // first of 6 data bytes: X_H,X_L, Z_H,Z_L, Y_H,Y_L (Z before Y!)
#define HMC_STATUS          0x09  // bit0=RDY, bit1=LOCK

// Config A: 8-sample averaging, 15 Hz output rate, normal measurement (0x70)
#define HMC_CFGA_8AVG_15HZ  0x70
// Config B: GN=001 → 1090 LSB/Gauss, ±1.3 Ga range (0x20)
#define HMC_CFGB_1090       0x20
// Mode: continuous measurement
#define HMC_MODE_CONTINUOUS 0x00

// Overflow sentinel: any axis output == -4096 means overflow
#define HMC_OVERFLOW        (-4096)

// 100 µT/Gauss ÷ 1090 LSB/Gauss ≈ 0.09174 µT/LSB at GN=001
#define HMC5883L_SCALE      (100.0f / 1090.0f)

#endif // MAG_DEVICE_HMC5883L
#endif // HMC5883L_H_
