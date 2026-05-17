# Adding IMU / Magnetometer Drivers

Wire Wiggler uses a two-level driver architecture for IMU feedback:

- **Magnetometer header** (`lib/<device>.h`) — register constants and scale factor only. No class, no code.
- **IMU driver header** (`lib/<device>.h`) — a class with `begin()` and `read()`. It sets up the IMU hardware, and if a magnetometer is configured, also sets up the IMU's I²C master to poll the magnetometer automatically.

Only the files for enabled devices compile, so disabled drivers cost zero flash.

---

## How the system fits together

```
config.h           → user selects devices (#define IMU_DEVICE_xxx, MAG_DEVICE_xxx)
defaults.h         → validates selection, includes imu.h then the correct driver headers
imu.h              → defines RawIMU, RawMag structs and MadgwickFilter class
<mag_driver>.h     → constants only (addr, registers, scale)
<imu_driver>.h     → includes the mag header; ICM20948 or MPU6050 class
wire-wiggler.cpp   → instantiates imuDevice, calls begin() and read()
```

The IMU driver is responsible for reading both the IMU and the magnetometer (via the IMU's auxiliary I²C master bus). The Madgwick filter in `imu.h` receives a filled `RawIMU` and `RawMag` and does the rest.

---

## The contract

Every IMU driver must fill these structs (defined in `lib/imu.h`):

```cpp
struct RawIMU {
    float ax, ay, az;  // accelerometer, units: g
    float gx, gy, gz;  // gyroscope, units: rad/s
};

struct RawMag {
    float mx, my, mz;  // magnetometer, units: µT
    bool valid;         // false on overflow or when no mag is configured
};
```

Axis convention — mount the sensor with:
- **X → bow** (forward)
- **Y → starboard** (right)
- **Z → down**

If the chip's axes don't match this layout, swap/negate in the driver's `read()` before storing into `RawIMU`.

---

## Step 1 — Write the magnetometer header

Create `lib/<chipname>.h`. This file only contains the I²C address, register addresses, mode constants, and the scale factor. No class is needed — the IMU driver reads the mag over its auxiliary bus using these constants directly.

Use `#ifdef MAG_DEVICE_<CHIPNAME>` guards so the file compiles to nothing when the device is not selected.

**Template** (modelled on `lib/ak09916.h` and `lib/hmc5883l.h`):

```cpp
#ifndef MYCHIP_H_
#define MYCHIP_H_

#ifdef MAG_DEVICE_MYCHIP

#define MYCHIP_ADDR     0x??   // 7-bit I²C address

// Register addresses
#define MYCHIP_STATUS   0x??   // data-ready flag
#define MYCHIP_DATA     0x??   // first data byte (read N bytes from here)
#define MYCHIP_CTRL     0x??   // mode / rate control register

// Mode values
#define MYCHIP_MODE_CONT 0x??  // continuous measurement

// Overflow sentinel (if the chip has one — check the datasheet)
#define MYCHIP_OVERFLOW (-4096)

// Convert raw LSB to µT.  Find sensitivity in the datasheet (LSB/Gauss or LSB/µT).
// Example: 1090 LSB/Gauss → 100 µT/Gauss → scale = 100.0f / 1090.0f
#define MYCHIP_SCALE    (100.0f / ???)

#endif // MAG_DEVICE_MYCHIP
#endif // MYCHIP_H_
```

**Key datasheet sections to find:**
- I²C address (and whether it has an address pin)
- Data output registers — note the **exact byte order** (some chips put Z before Y)
- Sensitivity / gain (LSB/Gauss or nT/LSB)
- Continuous-measurement mode register and value
- Overflow / saturation indicator (register bit or sentinel value)
- Whether reading a status register is required to unlock the next sample

---

## Step 2 — Write the IMU driver

Create `lib/<chipname>.h`. This is a class (`ICM20948`, `MPU6050`, etc.) with two public methods:

```cpp
bool begin();                          // init chip, returns false on I²C failure
bool read(RawIMU& imu, RawMag& mag);  // fill structs, returns false if no new data
```

Use `#ifdef IMU_DEVICE_<CHIPNAME>` guards.

Inside `begin()`, when `MAG_DEVICE_xxx` is defined, configure the IMU's I²C master to write the magnetometer's mode register and then continuously read its data registers into the IMU's external sensor data FIFO.

Inside `read()`, burst-read the IMU registers, scale to g and rad/s, then read the mag bytes from the IMU's external sensor data area, scale to µT, and set `mag.valid`.

**Template** (modelled on `lib/icm20948.h` and `lib/mpu6050.h`):

```cpp
#ifndef MYIMU_H_
#define MYIMU_H_

#ifdef IMU_DEVICE_MYIMU

#include <Wire.h>

#ifndef MYIMU_ADDR
    #define MYIMU_ADDR  0x??   // default I²C address
#endif

// --- Register addresses ---
#define REG_WHO_AM_I    0x??   // expected value: 0x??
#define REG_PWR_MGMT    0x??
#define REG_ACCEL_H     0x??   // first of N accel/gyro data bytes
#define REG_INT_STATUS  0x??   // bit0 = data ready
#define REG_EXT_DATA    0x??   // first byte of I²C master read-back data
// ... I²C master control registers (SLV0/SLV1, MST_CTRL, etc.) ...

// Scale factors matching the config chosen in begin()
#define MYIMU_GYRO_SCALE  (1.0f / 131.0f * 0.017453293f)  // rad/s per LSB (±250 dps)
#define MYIMU_ACCEL_SCALE (1.0f / 8192.0f)                 // g per LSB (±4g)

class MYIMU {
public:
    bool begin() {
        // 1. Hard reset, wait, wake up with PLL clock
        // 2. Verify WHO_AM_I — return false if wrong
        // 3. Configure gyro and accel range + DLPF
        // 4. Enable I²C master mode
        // 5. (inside #ifdef MAG_DEVICE_xxx) write mag config via SLV1, then
        //    configure SLV0 to continuously read mag data bytes
        return true;
    }

    bool read(RawIMU& imu, RawMag& mag) {
        if (!(readReg(REG_INT_STATUS) & 0x01)) return false;

        uint8_t buf[N];
        readBytes(REG_ACCEL_H, buf, N);

        imu.ax = (int16_t)((buf[0] << 8) | buf[1]) * MYIMU_ACCEL_SCALE;
        // ... fill ay, az, gx, gy, gz ...

        #ifdef MAG_DEVICE_xxx
        {
            uint8_t mb[M];
            readBytes(REG_EXT_DATA, mb, M);
            // check overflow, set mag.mx/my/mz in µT and mag.valid
        }
        #else
            mag.valid = false;
        #endif

        return true;
    }

private:
    void writeReg(uint8_t reg, uint8_t val) { /* Wire transaction */ }
    uint8_t readReg(uint8_t reg) { /* Wire transaction */ }
    void readBytes(uint8_t reg, uint8_t* buf, uint8_t len) { /* Wire transaction */ }
};

#endif // IMU_DEVICE_MYIMU
#endif // MYIMU_H_
```

### I²C master wiring pattern

The IMU acts as I²C master to poll the magnetometer on its auxiliary bus. The general sequence in `begin()`:

1. Enable I²C master (`USER_CTRL` or equivalent)
2. Set I²C master clock rate (typically 400 kHz)
3. **Write** mag config registers via **SLV1** (one byte at a time — change `SLV1_REG` and `SLV1_DO` for each):
   - Enable SLV1 (`SLV1_CTRL = 0x81`), wait ~10 ms, disable
   - Repeat for each config register
4. **Configure SLV0** to continuously **read** the mag data registers:
   - `SLV0_ADDR = 0x80 | mag_addr` (bit 7 = read direction)
   - `SLV0_REG  = first_data_register`
   - `SLV0_CTRL = 0x80 | byte_count` (bit 7 = enable)
5. Wait ~50 ms for the first measurement to arrive

In `read()`, the mag bytes are available at `REG_EXT_DATA` onwards without any extra I²C transaction — the IMU fetched them automatically.

> **Note:** Some chips (e.g. AK09916) require reading a status register at the end of the burst to unlock the next sample. Include those bytes in the SLV0 read count and check the overflow flag there.

---

## Step 3 — Wire it into `defaults.h`

Open `lib/defaults.h` and find the `#ifdef IMU_FEEDBACK` block. Add:

1. A new line in the IMU device check:
   ```cpp
   #if !defined(IMU_DEVICE_ICM20948) && !defined(IMU_DEVICE_MPU6050) && !defined(IMU_DEVICE_MYIMU)
       #error "IMU_FEEDBACK enabled but no IMU device defined..."
   ```

2. A new line in the magnetometer check:
   ```cpp
   #if !defined(MAG_DEVICE_AK09916) && !defined(MAG_DEVICE_HMC5883L) && !defined(MAG_DEVICE_MYMAG)
       #error "IMU_FEEDBACK enabled but no magnetometer device defined..."
   ```

3. Include directives for the new headers (inside the matching `#ifdef`):
   ```cpp
   #ifdef MAG_DEVICE_MYMAG
       #include <../lib/mymag.h>
   #endif
   #ifdef IMU_DEVICE_MYIMU
       #include <../lib/myimu.h>
   #endif
   ```

---

## Step 4 — Wire it into `src/wire-wiggler.cpp`

Add a global object declaration next to the existing ones:

```cpp
#ifdef IMU_DEVICE_MYIMU
    MYIMU imuDevice;
#endif
```

The `imuDevice.begin()` and `imuDevice.read()` calls are already guarded with `#if defined(IMU_DEVICE_ICM20948) || defined(IMU_DEVICE_MPU6050)` — extend these conditions to include your new device:

```cpp
#if defined(IMU_DEVICE_ICM20948) || defined(IMU_DEVICE_MPU6050) || defined(IMU_DEVICE_MYIMU)
```

---

## Step 5 — Document it in `src/config.h`

Add commented-out defines alongside the existing options so users know it exists:

```cpp
//#define IMU_DEVICE_MYIMU     // My new IMU (I²C addr 0x?? default)
//#define MAG_DEVICE_MYMAG     // My new magnetometer (I²C addr 0x??)
//#define MYIMU_ADDR  0x??     // Uncomment if address pin is pulled the other way
```

---

## Flash budget

AVR targets (Uno/Nano/Mega) have limited flash. The ICM-20948 + AK09916 driver with IMU enabled uses roughly **15% extra flash** on a Nano (328p). Keep drivers lean:

- No dynamic allocation, no `String`, no `Serial.print` inside drivers
- Only include `<Wire.h>` — no external IMU libraries
- Single burst reads (one `Wire.requestFrom` call per sensor frame)
- The mag constants header compiles to zero bytes when not enabled

Check flash usage after enabling: `pio run` reports RAM and flash percentage. Nano (328p) has 30 720 bytes flash and 2 048 bytes RAM.

---

## Checklist

- [ ] Datasheet reviewed: register map, byte order, sensitivity, overflow indicator, I²C master setup
- [ ] `lib/<mag>.h` written with correct addr, registers, scale, overflow sentinel
- [ ] `lib/<imu>.h` class with `begin()` returning false on bad WHO_AM_I, and `read()` returning false when data-ready bit is clear
- [ ] Axes mapped to NED convention (X=bow, Y=starboard, Z=down) in `read()`
- [ ] Mag overflow detected and sets `mag.valid = false`
- [ ] `mag.valid = false` in the `#else` branch (no mag configured)
- [ ] `defaults.h` error checks and `#include` directives added
- [ ] `wire-wiggler.cpp` object declaration and `#if defined(...)` conditions extended
- [ ] `config.h` commented-out defines added
- [ ] Flash checked with `pio run` after enabling
