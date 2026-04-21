#ifndef APPLICATION_USER_CORE_INC_DSPINTERFACE_H_
#define APPLICATION_USER_CORE_INC_DSPINTERFACE_H_

#include "DSPFilters.h"
#include "cmsis_os.h"

#define DSP_FLAG_UPDATE_COEF		(1U << 0)
#define DSP_FLAG_TOGGLE_DSP			(1U << 1)
#define DSP_FLAG_PAUSE				(1U << 2)
#define DSP_FLAG_RESUME				(1U << 3)

typedef struct{
	float lowG, midG, highG,
		  lowS, midQ, highS,
		  lowFC, midFC, highFC,
		  vol;
}EQ_PARAMS;

typedef struct{
	BiquadDF2T iLowL, iMidL, iHighL,
				iLowR, iMidR, iHighR;
}EQ_BIQUADS;


void initInterface(osThreadId_t dspT);
void pauseDSP();
void resumeDSP();
void toggleDSP();
void updateCoefs(EQ_PARAMS params);
float getVolume();
EQ_BIQUADS getBiquads();

#endif /* APPLICATION_USER_CORE_INC_DSPINTERFACE_H_ */
