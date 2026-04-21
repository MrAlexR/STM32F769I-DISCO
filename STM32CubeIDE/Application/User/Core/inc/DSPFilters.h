#ifndef INC_DSPFILTERS_H_
#define INC_DSPFILTERS_H_

#include <stdint.h>
#include <math.h>

#define PCM24_SCALE_F  (8388608.0f)
#define PCM24_MAX_I    ( 8388607)
#define PCM24_MIN_I    (-8388608)

float uint32_to_float(uint32_t value);
uint32_t float_to_uint32(float value);

typedef struct {
    float b0, b1, b2;
    float a1, a2;
    float z1, z2;
} BiquadDF2T;

BiquadDF2T rbj_low_shelf(float Fs, float f0, float gain_dB, float S);
BiquadDF2T rbj_high_shelf(float Fs, float f0, float gain_dB, float S);
BiquadDF2T rbj_peaking_eq(float Fs, float f0, float gain_dB, float Q);
BiquadDF2T biquad_reset(BiquadDF2T s);
float biquad_process_f32(BiquadDF2T *s, float x);
void swapCoefs(BiquadDF2T *base, BiquadDF2T clone);

#endif
