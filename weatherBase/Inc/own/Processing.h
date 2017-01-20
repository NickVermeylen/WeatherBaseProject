/*
 * Processing.h
 *
 *  Created on: 20-jan.-2017
 *      Author: Nick Vermeylen
 */

#ifndef OWN_PROCESSING_H_
#define OWN_PROCESSING_H_

#include "stm32f7xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
	uint32_t code;
	char clouds[30];
	char wind[30];
	char min;
	char max;
}data;

void vProcessingSnipping(char server_reply[2000], data * weather);

#endif /* OWN_PROCESSING_H_ */
