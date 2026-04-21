#include "DSPFilters.h"

float uint32_to_float(uint32_t value)
{
	// 1) Sign-extend 24-bit right-justified to int32
	int32_t x24 = ((int32_t)(value << 8)) >> 8;

	// 2) Normalize to float in approximately [-1.0, +1.0)
	return (float)x24 * (1.0f / 8388608.0f);   // 2^23
}

uint32_t float_to_uint32(float value)
{
	// 1) Saturate float to valid range
	// +1.0 cannot be represented as positive 24-bit
	if (value >=  0.9999998807907104f) value =  0.9999998807907104f; // (8388607 / 8388608)
	if (value <= -1.0f)                value = -1.0f;

	// 2) Scale to signed 24-bit range
	float scaled = value * PCM24_SCALE_F;

	// 3) Round to nearest integer
	int32_t y24 = (scaled >= 0.0f)
	               ? (int32_t)(scaled + 0.5f)
	               : (int32_t)(scaled - 0.5f);

	// 4) Safety clamp (paranoia, but cheap)
	if (y24 > PCM24_MAX_I) y24 = PCM24_MAX_I;
	if (y24 < PCM24_MIN_I) y24 = PCM24_MIN_I;

	// 5) Pack into 32-bit word, right-justified 24-bit
	return (uint32_t)(y24 & 0x00FFFFFFu);
}

BiquadDF2T rbj_low_shelf(float Fs, float f0, float gain_dB, float S)
{
	BiquadDF2T s;
    const float A  = powf(10.0f, gain_dB / 40.0f);
    const float w0 = 2.0f * (float)M_PI * (f0 / Fs);
    const float c  = cosf(w0);
    const float sn = sinf(w0);

    // alpha = sin(w0)/2 * sqrt( (A + 1/A) * (1/S - 1) + 2 )
    float term = (A + 1.0f / A) * (1.0f / S - 1.0f) + 2.0f;
    if (term < 0.0f) term = 0.0f; // numerical guard
    const float alpha = 0.5f * sn * sqrtf(term);

    // beta = 2*sqrt(A)*alpha
    const float beta = 2.0f * sqrtf(A) * alpha;

    // Unnormalized RBJ low-shelf
    const float b0 = A * ((A + 1.0f) - (A - 1.0f) * c + beta);
    const float b1 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * c);
    const float b2 = A * ((A + 1.0f) - (A - 1.0f) * c - beta);

    const float a0 =      (A + 1.0f) + (A - 1.0f) * c + beta;
    const float a1 = -2.0f * ((A - 1.0f) + (A + 1.0f) * c);
    const float a2 =      (A + 1.0f) + (A - 1.0f) * c - beta;

    // Normalize to a0 = 1
    const float inv_a0 = 1.0f / a0;
    s.b0 = b0 * inv_a0;
    s.b1 = b1 * inv_a0;
    s.b2 = b2 * inv_a0;
    s.a1 = a1 * inv_a0;
    s.a2 = a2 * inv_a0;
    return s;
}

BiquadDF2T rbj_high_shelf(float Fs, float f0, float gain_dB, float S)
{
	BiquadDF2T s;
    const float A  = powf(10.0f, gain_dB / 40.0f);
    const float w0 = 2.0f * (float)M_PI * (f0 / Fs);
    const float c  = cosf(w0);
    const float sn = sinf(w0);

    // alpha = sin(w0)/2 * sqrt( (A + 1/A) * (1/S - 1) + 2 )
    float term = (A + 1.0f / A) * (1.0f / S - 1.0f) + 2.0f;
    if (term < 0.0f) term = 0.0f; // numerical guard
    const float alpha = 0.5f * sn * sqrtf(term);

    // beta = 2*sqrt(A)*alpha
    const float beta = 2.0f * sqrtf(A) * alpha;

    // Unnormalized RBJ high-shelf
    const float b0 = A * ((A + 1.0f) + (A - 1.0f) * c + beta);
    const float b1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * c);
    const float b2 = A * ((A + 1.0f) + (A - 1.0f) * c - beta);

    const float a0 =      (A + 1.0f) - (A - 1.0f) * c + beta;
    const float a1 =  2.0f * ((A - 1.0f) - (A + 1.0f) * c);
    const float a2 =      (A + 1.0f) - (A - 1.0f) * c - beta;

    // Normalize to a0 = 1
    const float inv_a0 = 1.0f / a0;
    s.b0 = b0 * inv_a0;
    s.b1 = b1 * inv_a0;
    s.b2 = b2 * inv_a0;
    s.a1 = a1 * inv_a0;
    s.a2 = a2 * inv_a0;
    return s;
}

BiquadDF2T rbj_peaking_eq(float Fs, float f0, float gain_dB, float Q)
{
	BiquadDF2T s;
    const float A  = powf(10.0f, gain_dB / 40.0f);
    const float w0 = 2.0f * (float)M_PI * (f0 / Fs);
    const float c  = cosf(w0);
    const float sn = sinf(w0);

    // alpha = sin(w0)/(2Q)
    const float alpha = sn / (2.0f * Q);

    // Unnormalized RBJ peaking EQ
    const float b0 = 1.0f + alpha * A;
    const float b1 = -2.0f * c;
    const float b2 = 1.0f - alpha * A;

    const float a0 = 1.0f + alpha / A;
    const float a1 = -2.0f * c;
    const float a2 = 1.0f - alpha / A;

    // Normalize to a0 = 1
    const float inv_a0 = 1.0f / a0;
    s.b0 = b0 * inv_a0;
    s.b1 = b1 * inv_a0;
    s.b2 = b2 * inv_a0;
    s.a1 = a1 * inv_a0;
    s.a2 = a2 * inv_a0;
    return s;
}

BiquadDF2T biquad_reset(BiquadDF2T s)
{
    s.z1 = 0.0f;
    s.z2 = 0.0f;
    return s;
}

float biquad_process_f32(BiquadDF2T *s, float x)
{
    // DF2T:
    // y  = b0*x + z1
    // z1 = b1*x - a1*y + z2
    // z2 = b2*x - a2*y
    float y  = s->b0 * x + s->z1;
    float z1 = s->b1 * x - s->a1 * y + s->z2;
    float z2 = s->b2 * x - s->a2 * y;

    s->z1 = z1;
    s->z2 = z2;
    return y;
}

void swapCoefs(BiquadDF2T *base, BiquadDF2T clone)
{
	base->a1 = clone.a1;
	base->a2 = clone.a2;
	base->b0 = clone.b0;
	base->b1 = clone.b1;
	base->b2 = clone.b2;
}
