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

void vScreenInit( void );
void vScreenTouchInit( void );
uint8_t ucScreenSwitch( uint8_t ucMenu );

#endif /* OWN_SCREEN_H_ */
