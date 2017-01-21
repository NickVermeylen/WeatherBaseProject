/*
 * Processing.c
 *
 *  Created on: 20-jan.-2017
 *      Author: Nick Vermeylen
 */

#include "Processing.h"
/*-----------------------------------------------------------*/

/* Begin Static function prototypes */


/* End Static function prototypes */


/* Begin extern variables */

extern UART_HandleTypeDef huart1;

/* End extern variables */

/*-----------------------------------------------------------*/

/* Begin public functions */

void vProcessingSnipping( char ucInfo[2000] , data * pxInput )
{
	char * pcResp = "EMPTY RESPONSE";
	pcResp = strstr(ucInfo, "number=");

	if(pcResp != NULL)
	{
		//This should get pxInput number
		char * pcToken;
		pcToken = strtok( pcResp , "\"" ); //front part = useless
		pcToken = strtok( NULL , "\"" ); //schould be min val
		if( strcmp( pcToken , "800" ) )
		{
			pxInput->usCode = 12;
		}
		else
		{
			pxInput->usCode = pcToken[0] - '0';
		}

		//This gets cloudyness
		pcResp = strstr( ucInfo , "<clouds" );
		pcResp = strstr( pcResp , "name=" );
		pcToken = strtok( pcResp , "\"" ); //front part = useless
		pcToken = strtok( NULL , "\"" ); //schould be cloudy val
		sprintf( pxInput->ucClouds , pcToken );

		//This gets ucWindyness
		pcResp = strstr( ucInfo , "<wind><speed" );
		pcResp = strstr( pcResp , "name=" );
		pcToken = strtok( pcResp , "\"" ); //front part = useless
		pcToken = strtok( NULL , "\"" ); //schould be ucWindy val
		sprintf( pxInput->ucWind , pcToken );

		//This gets Min en Max temperatuur
		pcResp = strstr( ucInfo , "<temperature" );
		pcResp = strstr( pcResp , "min=" );
		pcToken = strtok( pcResp , "\"" ); //front part = useless
		pcToken = strtok( NULL , "\"" ); //schould be min val
		sprintf( pxInput->ucMin , pcToken );

		pcToken = strtok( NULL , "\"" ); //throw away
		pcToken = strtok( NULL , "\"" ); //schould be max val
		sprintf( pxInput->ucMax , pcToken );
	}
	else
	{
		HAL_UART_Transmit( &huart1, ( uint8_t* ) "No MATCH\n\r\n\r" , strlen( "No MATCH\n\r\n\r" ) , 100 );
	}
}


/*-----------------------------------------------------------*/

/* End public functions */

/* Begin Static functions */


/*-----------------------------------------------------------*/

/* End Static functions */


