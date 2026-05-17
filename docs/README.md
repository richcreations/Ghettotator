# Reference Documentation

## Guides

| File | Description |
|------|-------------|
| [adding-drivers.md](adding-drivers.md) | How to add a new IMU or magnetometer driver |

## Datasheets

| File | Description |
|------|-------------|
| ICM-20948-datasheet-v1.3.pdf | ICM-20948 9-axis IMU — full register map, I²C master, and AK09916 magnetometer section |
| MPU-6000-Datasheet1.pdf | MPU-6050 product specification — electrical characteristics and pin description |
| RM-MPU-6000A.pdf | MPU-6050 register map and descriptions |
| HMC5883L.pdf | Honeywell HMC5883L 3-axis magnetometer — register map and I²C protocol |

## Key datasheet sections for driver writing

**ICM-20948**
- Section 7 — Register map (Bank 0, 1, 2, 3)
- Section 8 — I²C interface and protocol
- Section 9 — AK09916 I²C master configuration

**MPU-6050** (use RM-MPU-6000A.pdf for registers)
- Register 107 (0x6B) — PWR_MGMT_1
- Register 27–28 (0x1B–0x1C) — GYRO_CONFIG, ACCEL_CONFIG
- Register 37 (0x25) — I²C_SLV0 master setup
- Register 106 (0x6A) — USER_CTRL (I²C master enable)

**HMC5883L**
- Table 2 — Register list
- Register 0x00–0x02 — Config A, Config B, Mode
- Register 0x03–0x08 — Data output (note: Z before Y in byte order)

## Other useful references (not included)

- **ICM-20948 v1.6 datasheet** — Latest version, requires TDK registration at invensense.tdk.com
- **AK09916 standalone datasheet** — Available from Asahi Kasei via OEM channels
- **SparkFun Qwiic ICM-20948 hookup guide** — sparkfun.com product page for the breakout board
