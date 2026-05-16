#ifndef ROTATOR_MATH_H_
#define ROTATOR_MATH_H_

#include <stdint.h>

#ifndef SPR
    #define SPR 200
#endif

inline long deg2step(float deg, float ratio, uint8_t microsteps) {
    return (long)((ratio * (float)SPR * (float)microsteps * deg) / 360.0f);
}

inline float step2deg(long step, float ratio, uint8_t microsteps) {
    return (360.0f * (float)step) / ((float)SPR * ratio * (float)microsteps);
}

#endif /* ROTATOR_MATH_H_ */
