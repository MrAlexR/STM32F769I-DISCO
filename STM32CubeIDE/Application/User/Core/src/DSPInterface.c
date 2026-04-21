#include "DSPInterface.h"

static osThreadId_t dspThread = NULL;
static volatile float intermVol;

static volatile EQ_BIQUADS intBq;

void initInterface(osThreadId_t dspT)
{
	dspThread = dspT;
}

void pauseDSP()
{
	osThreadFlagsSet(dspThread, DSP_FLAG_PAUSE);
}

void resumeDSP()
{
	osThreadFlagsSet(dspThread, DSP_FLAG_RESUME);
}

float getVolume(void)
{
	return intermVol;
}

EQ_BIQUADS getBiquads(){
	return intBq;
}

void updateCoefs(EQ_PARAMS params)
{
	intBq.iLowL = rbj_low_shelf(46875.0f, params.lowFC, params.lowG, params.lowS); // f0=100Hz, +6dB, S=1
	intBq.iLowR = rbj_low_shelf(46875.0f, params.lowFC, params.lowG, params.lowS);
	intBq.iLowL = biquad_reset(intBq.iLowL);
	intBq.iLowR = biquad_reset(intBq.iLowR);

	intBq.iMidL = rbj_peaking_eq(46875.0f, params.midFC, params.midG, params.midQ); // +3 dB at 1 kHz, Q=1
	intBq.iMidR = rbj_peaking_eq(46875.0f, params.midFC, params.midG, params.midQ);
	intBq.iMidL = biquad_reset(intBq.iMidL);
	intBq.iMidR = biquad_reset(intBq.iMidR);

	intBq.iHighL = rbj_high_shelf(46875.0f, params.highFC, params.highG, params.highS);
	intBq.iHighR = rbj_high_shelf(46875.0f, params.highFC, params.highG, params.highS);
	intBq.iHighL = biquad_reset(intBq.iHighL);
	intBq.iHighR = biquad_reset(intBq.iHighR);

	intermVol = params.vol;
	osThreadFlagsSet(dspThread, DSP_FLAG_UPDATE_COEF);
}

void toggleDSP()
{
	osThreadFlagsSet(dspThread, DSP_FLAG_TOGGLE_DSP);
}
