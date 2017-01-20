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

void vProcessingSnipping(char server_reply[2000], data * weather)
{
	char buffer[20] = "EMPTY BUFFER";
	sprintf(buffer, "Geen integers");
	HAL_UART_Transmit(&huart1, (uint8_t*) "\r\nResponse:", strlen("\r\nResponse:"), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\r\n", strlen("\r\n"), 100);

	HAL_UART_Transmit(&huart1, (uint8_t*) server_reply, strlen(server_reply), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r", strlen("\n\r"), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r", strlen("\n\r"), 100);

	HAL_UART_Transmit(&huart1, (uint8_t*) "Modify string", strlen("Modify string"), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r", strlen("\n\r"), 100);
	char * resp = "EMPTY RESPONSE";
		//resp = strstr(p->payload, "<weather");
		/*HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r", strlen("\n\r"), 100);*/
	resp = strstr(server_reply, "number=");
	if(resp != NULL)
	{
		//This should get weather number
		HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
		char * token;
		token = strtok(resp, "\""); //front part = useless
		token = strtok(NULL, "\""); //schould be min val
		weather->code = (uint32_t) token;
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);

		resp = strstr(server_reply, "<clouds");
		//This gets cloudyness
		HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
		resp = strstr(resp, "name=");
		token = strtok(resp, "\""); //front part = useless
		token = strtok(NULL, "\""); //schould be cloudy val
		sprintf(weather->clouds, token);
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);

		resp = strstr(server_reply, "<wind><speed");
		//This gets windyness
		HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
		resp = strstr(resp, "name=");
		token = strtok(resp, "\""); //front part = useless
		token = strtok(NULL, "\""); //schould be windy val
		sprintf(weather->wind,token);
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);


		resp = strstr(server_reply, "<temperature");
		//This gets Min en Max temperatuur
		HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
		resp = strstr(resp, "min=");
		token = strtok(resp, "\""); //front part = useless
		token = strtok(NULL, "\""); //schould be min val
		sprintf(weather->min, token);
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
		token = strtok(NULL, "\""); //throw away
		token = strtok(NULL, "\""); //schould be max val
		sprintf(weather->max, token);
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) server_reply, strlen(server_reply), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
	}
	else
	{
		HAL_UART_Transmit(&huart1, (uint8_t*) "No MATCH for TEMP\n\r\n\r", strlen("No MATCH for TEMP\n\r\n\r"), 100);
	}
}


/*-----------------------------------------------------------*/

/* End public functions */

/* Begin Static functions */


/*-----------------------------------------------------------*/

/* End Static functions */


