#ifndef _VIBE_SEQUENTIAL_H_
#define _VIBE_SEQUENTIAL_H_

#ifdef __cplusplus
extern "C"
{
#endif 

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define COLOR_BACKGROUND   0 
#define COLOR_FOREGROUND 255 


typedef struct vibeModel_Sequential vibeModel_Sequential_t;


vibeModel_Sequential_t *libvibeModel_Sequential_New();


uint32_t libvibeModel_Sequential_PrintParameters(const vibeModel_Sequential_t *model);


int32_t libvibeModel_Sequential_SetNumberOfSamples(
	vibeModel_Sequential_t *model,
	const uint32_t numberOfSamples
);


uint32_t libvibeModel_Sequential_GetNumberOfSamples(const vibeModel_Sequential_t *model);

int32_t libvibeModel_Sequential_SetMatchingThreshold(
  vibeModel_Sequential_t *model,
  const uint32_t matchingThreshold
);

uint32_t libvibeModel_Sequential_GetMatchingThreshold(const vibeModel_Sequential_t *model);


int32_t libvibeModel_Sequential_SetMatchingNumber(
  vibeModel_Sequential_t *model,
  const uint32_t matchingNumber
);

int32_t libvibeModel_Sequential_SetUpdateFactor(
  vibeModel_Sequential_t *model,
  const uint32_t updateFactor
);


uint32_t libvibeModel_Sequential_GetMatchingNumber(const vibeModel_Sequential_t *model);

uint32_t libvibeModel_Sequential_GetUpdateFactor(const vibeModel_Sequential_t *model);

int32_t libvibeModel_Sequential_Free(vibeModel_Sequential_t *model);

int32_t libvibeModel_Sequential_AllocInit_8u_C1R(
	vibeModel_Sequential_t *model,
	const uint8_t *image_data,
	const uint32_t width,
	const uint32_t height
);

int32_t libvibeModel_Sequential_Segmentation_8u_C1R(
	vibeModel_Sequential_t *model,
	const uint8_t *image_data,
	uint8_t *segmentation_map
);


int32_t libvibeModel_Sequential_Update_8u_C1R(
	vibeModel_Sequential_t *model,
	const uint8_t *image_data,
	uint8_t *updating_mask
);


int32_t libvibeModel_Sequential_AllocInit_8u_C3R(
	vibeModel_Sequential_t *model,
	const uint8_t *image_data,
	const uint32_t width,
	const uint32_t height
);

int32_t libvibeModel_Sequential_Segmentation_8u_C3R(
	vibeModel_Sequential_t *model,
	const uint8_t *image_data,
	uint8_t *segmentation_map
);

int32_t libvibeModel_Sequential_Update_8u_C3R(
	vibeModel_Sequential_t *model,
	const uint8_t *image_data,
	uint8_t *updating_mask
);

#ifdef __cplusplus
}
#endif

#endif