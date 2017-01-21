/*
 * Processing.h
 *
 *  Created on: 20-jan.-2017
 *      Author: Nick Vermeylen
 */

#ifndef OWN_PROCESSING_H_
#define OWN_PROCESSING_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stm32f7xx_hal.h"

typedef struct{
	uint32_t usCode;
	char ucClouds[30];
	char ucWind[30];
	char ucMin[5];
	char ucMax[5];
}data;

void vProcessingSnipping(char ucInfo[2000], data * pxInput);

#endif /* OWN_PROCESSING_H_ */
