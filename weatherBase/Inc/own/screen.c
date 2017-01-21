/*
 * screen.c
 *
 *  Created on: 20-jan.-2017
 *      Author: Nick Vermeylen
 */
#include "stm32746g_discovery_lcd.h"
#include "screen.h"
#include "partlySunny_data.h"
#include "Sunny_data.h"
#include "Cloudy_data.h"
#include "Rain_data.h"
#include "Showers_data.h"
#include "Foggy_data.h"
#include "StartBttn_data.h"
#include "StartButtonPressed_data.h"
/*-----------------------------------------------------------*/

/* Begin Static function prototypes */

static void prvScreenDrawScrn1( void );
static void prvScreenDrawScrn2( void );
static void prvScreenDrawScrn3( void );

/* End Static function prototypes */


/* Begin extern variables */

extern ucMenu;

/* End extern variables */

/*-----------------------------------------------------------*/

/* Begin public functions */

void vScreenInit( void )
{
	  BSP_LCD_Init();
	  BSP_LCD_LayerDefaultInit(0,LCD_FB_START_ADDRESS);
	  BSP_LCD_LayerDefaultInit(1,LCD_FB_START_ADDRESS + (BSP_LCD_GetXSize()*BSP_LCD_GetYSize()*4));
	  BSP_LCD_DisplayOn();
	  BSP_LCD_SelectLayer(0);
	  BSP_LCD_Clear(LCD_COLOR_BLACK);
	  BSP_LCD_SelectLayer(1);
	  BSP_LCD_Clear(LCD_COLOR_DARKMAGENTA);
	  BSP_LCD_SetTransparency(0,0);
	  BSP_LCD_SetTransparency(1,255);

	  uint32_t usX = 0;
	  uint32_t usY = 0;
	  usX = BSP_LCD_GetXSize();
	  usY = BSP_LCD_GetYSize();

	  BSP_LCD_SelectLayer(1);
	  BSP_LCD_DrawBitmap( (usX-195)/2 , (usY-52)/2 , STARTBTTN_DATA );
}

void vScreenTouchInit( void )
{
	  //Touchscreen part
	  uint32_t usX = 0;
	  uint32_t usY = 0;
	  usX = BSP_LCD_GetXSize();
	  usY = BSP_LCD_GetYSize();
	  BSP_TS_Init( usX , usY );
}

uint8_t ucScreenSwitch( uint8_t ucMenu )
{
	//ucMenu++;
	if( ucMenu > 3 )
	{
	  ucMenu = 0;
	}
	HAL_Delay( 200 );
	switch( ucMenu )
	{
	case 0: prvScreenDrawScrn1(); break;
	case 1: prvScreenDrawScrn2(); break;
	case 2: prvScreenDrawScrn3(); break;
	case 3: prvScreenDrawScrn2(); break;
	}

	return ucMenu;
}



/*-----------------------------------------------------------*/

/* End public functions */

/* Begin Static functions */
static void prvScreenDrawScrn1( void )
{
	uint32_t usX = 0;
	uint32_t usY = 0;

	usX = BSP_LCD_GetXSize();
	usY = BSP_LCD_GetYSize();

	BSP_LCD_Clear(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_DrawBitmap( (usX-192)/2 , 0 , CLOUDY_DATA );
	BSP_LCD_SetFont(&Font12);
	char message[50] = "Temperature of Min: 2°C & Max: 8°C";
	//BSP_LCD_DisplayStringAtLine(14, message);
	BSP_LCD_DisplayStringAt( 0 , 156+10 , message , CENTER_MODE );
}

static void prvScreenDrawScrn2( void )
{
	uint32_t usX = 0;
	uint32_t usY = 0;

	usX = BSP_LCD_GetXSize();
	usY = BSP_LCD_GetYSize();

	BSP_LCD_Clear(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_DrawBitmap( (usX-192)/2 , 0 , RAIN_DATA);
	BSP_LCD_SetFont(&Font12);
	char message[50] = "Temperature of Min: 2°C & Max: 8°C";
	//BSP_LCD_DisplayStringAtLine(14, message);
	BSP_LCD_DisplayStringAt( 0 , 156+10 , message , CENTER_MODE );
}

static void prvScreenDrawScrn3( void )
{
	uint32_t usX = 0;
	uint32_t usY = 0;

	usX = BSP_LCD_GetXSize();
	usY = BSP_LCD_GetYSize();

	BSP_LCD_Clear(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_DrawBitmap( (usX-192)/2 , 0 , SUNNY_DATA );
	BSP_LCD_SetFont(&Font12);
	char message[50] = "Temperature of Min: 2°C & Max: 8°C";
	//BSP_LCD_DisplayStringAtLine(14, message);
	BSP_LCD_DisplayStringAt( 0 , 156+10 , message , CENTER_MODE );
}

/*-----------------------------------------------------------*/

/* End Static functions */
