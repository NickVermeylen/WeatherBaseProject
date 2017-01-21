/*
 * screen.h
 *
 *  Created on: 20-jan.-2017
 *      Author: Nick Vermeylen
 */

#ifndef OWN_SCREEN_H_
#define OWN_SCREEN_H_

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery_lcd.h"

#include "Processing.h"

void vScreenInit( void );
void vScreenTouchInit( void );
void vScreenDraw( data xInput );

#endif /* OWN_SCREEN_H_ */
