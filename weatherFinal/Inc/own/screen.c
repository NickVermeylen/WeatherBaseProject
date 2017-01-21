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
#include "Sleet_data.h"
#include "Storm_data.h"

#define screenSPRITEX 192
#define screenSPRITEY 156
#define screenBTTNX 195
#define screenBTTNY 52
/*-----------------------------------------------------------*/

/* Begin Static function prototypes */


/* End Static function prototypes */


/* Begin extern variables */


/* End extern variables */

/*-----------------------------------------------------------*/

/* Begin public functions */

/*
 * Init het LCD Scherm
 */
void vScreenInit( void )
{
	BSP_LCD_Init();

	uint32_t usX = 0;
	uint32_t usY = 0;
	usX = BSP_LCD_GetXSize();
	usY = BSP_LCD_GetYSize();

	BSP_LCD_LayerDefaultInit( 0 , LCD_FB_START_ADDRESS );
	BSP_LCD_LayerDefaultInit( 1 , LCD_FB_START_ADDRESS + ( usX * usY * 4 ));
	BSP_LCD_DisplayOn();
	BSP_LCD_SelectLayer( 0 );
	BSP_LCD_Clear( LCD_COLOR_BLACK );
	BSP_LCD_SelectLayer( 1 );
	BSP_LCD_Clear( LCD_COLOR_WHITE );
	BSP_LCD_SetTransparency( 0 , 0 );
	BSP_LCD_SetTransparency( 1 , 255 );

	BSP_LCD_SelectLayer(1);
	BSP_LCD_DrawBitmap( ( usX - screenBTTNX ) / 2 , ( usY - screenBTTNY ) / 2 , STARTBTTN_DATA );
	BSP_LCD_DisplayStringAt( 0 , ( usY - screenBTTNY ) / 2 + 100 , "Plz Press Blue PushButton" , CENTER_MODE );
}

/*
 * Init de touchscreen
 */
void vScreenTouchInit( void )
{
	  //Touchscreen part
	  uint32_t usX = 0;
	  uint32_t usY = 0;
	  usX = BSP_LCD_GetXSize();
	  usY = BSP_LCD_GetYSize();
	  BSP_TS_Init( usX , usY );
}

/*
 * Tekent Het "current weather" scherm me de data van de serverresponse
 */
void vScreenDraw( data xInput )
{
	uint32_t usX = 0;
	char ucMessage[50] = "";

	usX = BSP_LCD_GetXSize();

	BSP_LCD_Clear(LCD_COLOR_WHITE);

	//Huidig weer code
	switch( xInput.usCode )
	{

		case 2 : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , STORM_DATA ); break;
		case 3 : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , SLEET_DATA ); break;
		case 5 : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , RAIN_DATA ); break;
		case 6 : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , SHOWERS_DATA ); break;
		case 7 : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , FOGGY_DATA ); break;
		case 8 : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , CLOUDY_DATA ); break;
		case 12 : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , SUNNY_DATA ); break;
		default : BSP_LCD_DrawBitmap( ( usX - 192 ) / 2 , 0 , SUNNY_DATA ); break;

	}
	//BSP_LCD_DisplayStringAtLine(15, xInput.usCode);
	//print temperature
	BSP_LCD_SetFont( &Font16 );
	sprintf( ucMessage , "Temperature of Min: " );
	strcat( ucMessage , xInput.ucMin );
	strcat( ucMessage , "C & Max: " );
	strcat( ucMessage , xInput.ucMax );
	strcat( ucMessage , "C" );
	BSP_LCD_DisplayStringAt( 0 , 156 + 10 , ucMessage , CENTER_MODE );

	//print clouds en wind
	sprintf( ucMessage , xInput.ucClouds );
	strcat( ucMessage , " & " );
	strcat( ucMessage , xInput.ucWind );
	BSP_LCD_DisplayStringAt( 0 , 156 + 30 , ucMessage , CENTER_MODE );

	//print clouds en wind
	BSP_LCD_SetFont( &Font16 );
	BSP_LCD_SetTextColor( LCD_COLOR_DARKGREEN );
	sprintf( ucMessage , "But it'll probably rain anyway!" );
	BSP_LCD_DisplayStringAt( 0 , 156 + 70 , ucMessage , CENTER_MODE );

}


/*-----------------------------------------------------------*/

/* End public functions */

/* Begin Static functions */


/*-----------------------------------------------------------*/

/* End Static functions */
