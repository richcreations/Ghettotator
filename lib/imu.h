#ifndef IMU_H_
#define IMU_H_

#ifdef IMU_FEEDBACK

#include <stdint.h>
#include <math.h>

// Standardized sensor data structs — all device drivers fill these
struct RawIMU {
    float ax, ay, az;  // accelerometer in g
    float gx, gy, gz;  // gyroscope in rad/s
};

struct RawMag {
    float mx, my, mz;  // magnetometer in µT
    bool valid;
};

/*
Madgwick 9DOF AHRS filter + AZ/EL coordinate transform.

Sensor mount convention (NED body frame):
  X → bow (forward)
  Y → starboard (right)
  Z → down

IMU_BETA: lower = more smoothing (waves filtered out), higher = faster heading tracking.
IMU_DECLINATION: degrees added to magnetometer heading to get true North (positive East).
*/
class MadgwickFilter {
public:
    MadgwickFilter() : _q0(1.0f), _q1(0.0f), _q2(0.0f), _q3(0.0f) {}

    void update(const RawIMU& imu, const RawMag& mag, float dt) {
        float gx = imu.gx, gy = imu.gy, gz = imu.gz;
        float ax = imu.ax, ay = imu.ay, az = imu.az;

        // Apply declination rotation to mag in horizontal plane
        float cd = cosf(IMU_DECLINATION * 0.017453293f);
        float sd = sinf(IMU_DECLINATION * 0.017453293f);
        float mx = mag.mx * cd - mag.my * sd;
        float my = mag.mx * sd + mag.my * cd;
        float mz = mag.mz;

        if (mag.valid) {
            madgwickUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, dt);
        } else {
            madgwickUpdate(gx, gy, gz, ax, ay, az, 0, 0, 0, dt);
        }
    }

    // Transform fixed-frame AZ/EL (from ground station) into vehicle-frame AZ/EL (to motors)
    void correctAzEl(float az_in, float el_in, float& az_out, float& el_out) {
        float az_r = az_in * 0.017453293f;
        float el_r = el_in * 0.017453293f;

        // Target unit vector in NED Earth frame
        float vN = cosf(el_r) * cosf(az_r);
        float vE = cosf(el_r) * sinf(az_r);
        float vD = -sinf(el_r);

        // Rotate Earth→body using R^T (transpose of body-to-Earth rotation matrix)
        float w = _q0, x = _q1, y = _q2, z = _q3;
        float bN = (1-2*(y*y+z*z))*vN + 2*(x*y+w*z)*vE  + 2*(x*z-w*y)*vD;
        float bE =  2*(x*y-w*z)*vN    + (1-2*(x*x+z*z))*vE + 2*(y*z+w*x)*vD;
        float bD =  2*(x*z+w*y)*vN    + 2*(y*z-w*x)*vE  + (1-2*(x*x+y*y))*vD;

        el_out = asinf(-bD) * 57.295779f;
        az_out = atan2f(bE, bN) * 57.295779f;
        if (az_out < 0.0f) az_out += 360.0f;
    }

private:
    float _q0, _q1, _q2, _q3;

    float invSqrt(float x) {
        union { float f; uint32_t i; } u = { .f = x };
        u.i = 0x5f3759df - (u.i >> 1);
        u.f *= 1.5f - 0.5f * x * u.f * u.f;
        return u.f;
    }

    // Madgwick 9DOF AHRS — from Madgwick (2010), NED frame
    // Falls back to 6DOF (gyro + accel only) when mx==my==mz==0
    void madgwickUpdate(float gx, float gy, float gz,
                        float ax, float ay, float az,
                        float mx, float my, float mz,
                        float dt) {
        float rn, s0, s1, s2, s3, qd0, qd1, qd2, qd3;
        float hx, hy, _2bx, _2bz, _4bx, _4bz;
        float _2q0mx, _2q0my, _2q0mz, _2q1mx;
        float _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3;
        float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
        float w = _q0, x = _q1, y = _q2, z = _q3;

        qd0 = 0.5f * (-x*gx - y*gy - z*gz);
        qd1 = 0.5f * ( w*gx + y*gz - z*gy);
        qd2 = 0.5f * ( w*gy - x*gz + z*gx);
        qd3 = 0.5f * ( w*gz + x*gy - y*gx);

        if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
            rn = invSqrt(ax*ax + ay*ay + az*az);
            ax *= rn; ay *= rn; az *= rn;

            bool hasMag = !((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f));
            if (hasMag) {
                rn = invSqrt(mx*mx + my*my + mz*mz);
                mx *= rn; my *= rn; mz *= rn;
            }

            _2q0mx = 2.0f*w*mx; _2q0my = 2.0f*w*my; _2q0mz = 2.0f*w*mz;
            _2q1mx = 2.0f*x*mx;
            _2q0 = 2.0f*w; _2q1 = 2.0f*x; _2q2 = 2.0f*y; _2q3 = 2.0f*z;
            _2q0q2 = 2.0f*w*y; _2q2q3 = 2.0f*y*z;
            q0q0=w*w; q0q1=w*x; q0q2=w*y; q0q3=w*z;
            q1q1=x*x; q1q2=x*y; q1q3=x*z;
            q2q2=y*y; q2q3=y*z; q3q3=z*z;

            if (hasMag) {
                hx = mx*q0q0 - _2q0my*z + _2q0mz*y + mx*q1q1 + _2q1*my*y + _2q1*mz*z - mx*q2q2 - mx*q3q3;
                hy = _2q0mx*z + my*q0q0 - _2q0mz*x + _2q1mx*y - my*q1q1 + my*q2q2 + _2q2*mz*z - my*q3q3;
                _2bx = sqrtf(hx*hx + hy*hy);
                _2bz = -_2q0mx*y + _2q0my*x + mz*q0q0 + _2q1mx*z - mz*q1q1 + _2q2*my*z - mz*q2q2 + mz*q3q3;
                _4bx = 2.0f*_2bx; _4bz = 2.0f*_2bz;

                s0 = -_2q2*(2.0f*q1q3-_2q0q2-ax) + _2q1*(2.0f*q0q1+_2q2q3-ay)
                     - _2bz*y*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
                     + (-_2bx*z+_2bz*x)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
                     + _2bx*y*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);
                s1 = _2q3*(2.0f*q1q3-_2q0q2-ax) + _2q0*(2.0f*q0q1+_2q2q3-ay)
                     - 4.0f*x*(1.0f-2.0f*q1q1-2.0f*q2q2-az)
                     + _2bz*z*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
                     + (_2bx*y+_2bz*w)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
                     + (_2bx*z-_4bz*x)*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);
                s2 = -_2q0*(2.0f*q1q3-_2q0q2-ax) + _2q3*(2.0f*q0q1+_2q2q3-ay)
                     - 4.0f*y*(1.0f-2.0f*q1q1-2.0f*q2q2-az)
                     + (-_4bx*y-_2bz*w)*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
                     + (_2bx*x+_2bz*z)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
                     + (_2bx*w-_4bz*y)*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);
                s3 = _2q1*(2.0f*q1q3-_2q0q2-ax) + _2q2*(2.0f*q0q1+_2q2q3-ay)
                     + (-_4bx*z+_2bz*x)*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
                     + (-_2bx*w+_2bz*y)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
                     + _2bx*x*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);
            } else {
                // 6DOF fallback (accel + gyro only)
                s0 = -_2q2*(2.0f*q1q3-_2q0q2-ax) + _2q1*(2.0f*q0q1+_2q2q3-ay);
                s1 =  _2q3*(2.0f*q1q3-_2q0q2-ax) + _2q0*(2.0f*q0q1+_2q2q3-ay) - 4.0f*x*(1.0f-2.0f*q1q1-2.0f*q2q2-az);
                s2 = -_2q0*(2.0f*q1q3-_2q0q2-ax) + _2q3*(2.0f*q0q1+_2q2q3-ay) - 4.0f*y*(1.0f-2.0f*q1q1-2.0f*q2q2-az);
                s3 =  _2q1*(2.0f*q1q3-_2q0q2-ax) + _2q2*(2.0f*q0q1+_2q2q3-ay);
            }

            rn = invSqrt(s0*s0 + s1*s1 + s2*s2 + s3*s3);
            s0 *= rn; s1 *= rn; s2 *= rn; s3 *= rn;
            qd0 -= IMU_BETA*s0; qd1 -= IMU_BETA*s1;
            qd2 -= IMU_BETA*s2; qd3 -= IMU_BETA*s3;
        }

        w += qd0*dt; x += qd1*dt; y += qd2*dt; z += qd3*dt;
        rn = invSqrt(w*w + x*x + y*y + z*z);
        _q0 = w*rn; _q1 = x*rn; _q2 = y*rn; _q3 = z*rn;
    }
};

#endif // IMU_FEEDBACK
#endif // IMU_H_
