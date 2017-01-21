/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "lwip.h"

/* USER CODE BEGIN Includes */

/*#include <unistd.h>
#include <limits.h>*/
#include "own/Processing.h"
//#include <ctype.h>
#include "jsmn.h"
//#include "cJSON.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_ts.h"
#include "tmp/test.txt"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c3;

LTDC_HandleTypeDef hltdc;

UART_HandleTypeDef huart1;

SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char server_reply[2000];
int counter;
data weather;
uint8_t ucConnectie = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_I2C3_Init(void);
static void MX_LTDC_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void processResponse()
{
	counter=1;
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
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
	  	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);

	  	resp = strstr(server_reply, "<clouds");
		//This gets cloudyness
		HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
	  	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
	  	resp = strstr(resp, "name=");
	  	token = strtok(resp, "\""); //front part = useless
	  	token = strtok(NULL, "\""); //schould be cloudy val
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
	  	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);

	  	resp = strstr(server_reply, "<wind><speed");
		//This gets windyness
		HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
	  	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
	  	resp = strstr(resp, "name=");
	  	token = strtok(resp, "\""); //front part = useless
	  	token = strtok(NULL, "\""); //schould be windy val
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
	  	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);


	  	resp = strstr(server_reply, "<temperature");
		//This gets Min en Max temperatuur
		HAL_UART_Transmit(&huart1, (uint8_t*) resp, strlen(resp), 100);
	  	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
	  	resp = strstr(resp, "min=");
	  	token = strtok(resp, "\""); //front part = useless
	  	token = strtok(NULL, "\""); //schould be min val
		HAL_UART_Transmit(&huart1, (uint8_t*) token, strlen(token), 100);
	  	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r\n\r", strlen("\n\r\n\r"), 100);
	  	token = strtok(NULL, "\""); //throw away
	  	token = strtok(NULL, "\""); //schould be max val
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
/*int ParsingJson(char * server_reply, int len)
{
	char buffer[60];
	cJSON *root;
	cJSON *fmt;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
	cJSON_AddStringToObject(fmt, "type", "rect");
	cJSON_AddNumberToObject(fmt, "width", 1920);
	cJSON_AddNumberToObject(fmt, "height", 1080);
	cJSON_AddFalseToObject (fmt, "interlace");
	cJSON_AddNumberToObject(fmt, "frame rate", 24);
	cJSON * json;
	json = cJSON_Parse(&root);
	//cJSON *format = cJSON_GetObjectItem(json, "format");
	//int framerate = cJSON_GetObjectItem(format, "frame rate")->valueint;
	//sprintf(&buffer, framerate);
	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 100);
	return 1;
}*/
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}
int ParseJson(char server_reply[800], int len)
{
	HAL_UART_Transmit(&huart1, (uint8_t*) "Entering Parse\r\n", strlen("Entering Parse\r\n"), 100);
	int i;
	int r;
	jsmn_parser p;
	jsmntok_t t[800];
	char buffer[60];

	HAL_UART_Transmit(&huart1, (uint8_t*) server_reply, strlen(server_reply), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\n\r", strlen("\n\r"), 100);
	jsmn_init(&p);
	r = jsmn_parse(&p, server_reply, strlen(server_reply), t, sizeof(t)/sizeof(t[0]));
	if (r < 0) {
		sprintf(&buffer, "Failed to parse json: %d\r\n", r);
		HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 100);
		return 1;
	}
	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		HAL_UART_Transmit(&huart1, (uint8_t*) "Object expected\r\n", strlen("Object expected\r\n"), 100);
		return 1;
	}

	HAL_UART_Transmit(&huart1, (uint8_t*) r, 1, 100);
	for (i = 1; i < r; i++) {
		if (jsoneq(server_reply, &t[i], "description") == 0) {
			/* We may use strndup() to fetch string value */
			sprintf(&buffer,"- name: %.*s\r\n", t[i+1].end-t[i+1].start,
					server_reply + t[i+1].start);
			HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 100);
			i++;
		}
		else if (jsoneq(server_reply, &t[i], "main") == 0) {
			/* We may additionally check if the value is either "true" or "false" */
			sprintf(&buffer,"- age: %.*s\r\n", t[i+1].end-t[i+1].start,
					server_reply + t[i+1].start);
			HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 100);
			i++;
		}
		else if (jsoneq(server_reply, &t[i], "weather") == 0) {
					int j;
					printf("- Groups:\n");
					if (t[i+1].type != JSMN_ARRAY) {
						continue; /* We expect groups to be an array of strings */
					}
					for (j = 0; j < t[i+1].size; j++) {
						jsmntok_t *g = &t[i+j+2];
						printf("  * %.*s\n", g->end - g->start, server_reply + g->start);
					}
					i += t[i+1].size + 1;
				}
//		else if (jsoneq(server_reply, &t[i], "uid") == 0) {
//			/* We may want to do strtol() here to get numeric value */
//			printf("- UID: %.*s\n", t[i+1].end-t[i+1].start,
//					server_reply + t[i+1].start);
//			i++;
//		} else if (jsoneq(server_reply, &t[i], "groups") == 0) {
//			int j;
//			printf("- Groups:\n");
//			if (t[i+1].type != JSMN_ARRAY) {
//				continue; /* We expect groups to be an array of strings */
//			}
//			for (j = 0; j < t[i+1].size; j++) {
//				jsmntok_t *g = &t[i+j+2];
//				printf("  * %.*s\n", g->end - g->start, server_reply + g->start);
//			}
//			i += t[i+1].size + 1;
//		}
		else {
			sprintf("Unexpected key: %.*s\n", t[i].end-t[i].start,
					server_reply + t[i].start);
			HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 100);
		}
	}
		return EXIT_SUCCESS;
}

err_t received(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	ucConnectie++;
	BSP_LCD_SetFont(&Font8);
	char message[50] = "Recieving data:";
	BSP_LCD_DisplayStringAtLine(4, message);
	BSP_LCD_DisplayStringAtLine(5, (char*) p->payload);
	sprintf(server_reply, p->payload);
	HAL_UART_Transmit(&huart1, (uint8_t*) "RECIEVING..\r\n", strlen("RECIEVING..\r\n"), 100);
	vProcessingSnipping(server_reply, &weather);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\r\n\r\nTEST..\r\n", strlen("\r\n\r\nTEST..\r\n"), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) weather.clouds, strlen(weather.clouds), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\r\n\r\nTEST..\r\n", strlen("\r\n\r\nTEST..\r\n"), 100);
	return 0;
}
err_t connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
	ucConnectie++;
	char message[50] = "Connected with api";
	BSP_LCD_SetFont(&Font8);
	BSP_LCD_DisplayStringAtLine(2, (uint8_t*) message);
	char message2[50] = "Attempting GET request...";
	BSP_LCD_DisplayStringAtLine(3, (uint8_t*) message2);
	char command[200] = "GET /data/2.5/weather?id=2786641&APPID=6114c658e93e58c695e14114fe716819&units=metric&mode=xml HTTP/1.0\r\n\r\n";
	uint16_t commandlen = strlen(command);
	HAL_UART_Transmit(&huart1, (uint8_t*) command, commandlen, 100);
	tcp_write(tpcb,&command,strlen(command),1);
	tcp_recv(tpcb, received);
	return 0;
}
err_t err(void *arg, struct tcp_pcb *tpcb, err_t err){
	char message[50] = "FAILED TO CONNECT";
		BSP_LCD_SetFont(&Font8);
		BSP_LCD_DisplayStringAtLine(2, (uint8_t*) message);
		return 0;
}
void checkState( TS_StateTypeDef * State )
{
	//BSP_TS_ITConfig();
	//BSP_TS_GetState(State);
}
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_USART1_UART_Init();
  MX_LWIP_Init();

  /* USER CODE BEGIN 2 */
  //DISPLAY INIT MET BSP
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

  BSP_LCD_SelectLayer(1);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_RED);
  uint32_t usX = 0;
  uint32_t usY = 0;
  usX = BSP_LCD_GetXSize();
  usY = BSP_LCD_GetYSize();
  BSP_TS_Init( usX , usY );
  TS_StateTypeDef  State;
  uint8_t ucMenu = 3; //Menu staat bijhouden

  //char *host = "api.openweathermap.org";
  struct ip4_addr serverIp;
  IP4_ADDR(&serverIp, 178,62,207,82);  	//ip openweather server
  //IP4_ADDR(&serverIp, 192,168,0,148); //ip thuis van computer

  /*struct hostent *server;
  struct sockaddr_in serv_addr;
  int sockfd, bytes, sent, received, total;*/

  /*server = dns_gethostbyname(host);
  if (server == NULL) error("ERROR, no such host");*/

 /* //starting LWIP network interface
  struct ip4_addr ipaddr;
  IP4_ADDR(&ipaddr, 192,168,137,20);
  struct ip4_addr netmask;
  IP4_ADDR(&netmask, 255,255,255,0);
  struct ip4_addr gw;
  IP4_ADDR(&gw, 192,168,137,1);

  //DHCP start
  struct netif * netif;
  netif_add(netif, (ip4_addr_t*)ipaddr, (ip4_addr_t*)netmask, (ip4_addr_t*)gw, NULL, (netif_init_fn)(netif), trick());
  Netif_Config();
  dhcp_start(netif);
  sys_check_timeouts();*/

  u16_t port = 80;
  struct tcp_pcb *tcpconnection;
  tcpconnection = tcp_new();
  char *errorval;
  int count = 1;
  errorval = tcp_connect(tcpconnection, &serverIp, port, connected);
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAtLine(10, errorval);


  BSP_LCD_SetFont(&Font8);
  BSP_LCD_DisplayStringAtLine(8, server_reply);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  MX_LWIP_Process();
	  if(ucConnectie > 2)
	  {
		  //tcp_close(tcpconnection);
		errorval = "Got In IF";
		BSP_LCD_SetFont(&Font12);
		BSP_LCD_DisplayStringAtLine(15, errorval);
		BSP_TS_ResetTouchData( &State );
		checkState( &State );
		errorval = "Got Past State";
		BSP_LCD_SetFont(&Font12);
		BSP_LCD_DisplayStringAtLine(16, errorval);
		//State.touchDetected = 1;
		HAL_Delay(1500);
		  if( State.touchDetected )
		  {
				errorval = "Got in Menu";
				BSP_LCD_SetFont(&Font12);
				BSP_LCD_DisplayStringAtLine(17, errorval);
			  ucMenu++;
			  ucMenu = ucScreenSwitch( ucMenu );
		  }
	  }
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 10;
  RCC_OscInitStruct.PLL.PLLN = 210;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_I2C3;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* DMA2D init function */
static void MX_DMA2D_Init(void)
{

  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* I2C3 init function */
static void MX_I2C3_Init(void)
{

  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00303D5B;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

}

/* LTDC init function */
static void MX_LTDC_Init(void)
{

  LTDC_LayerCfgTypeDef pLayerCfg;
  LTDC_LayerCfgTypeDef pLayerCfg1;

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 7;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 14;
  hltdc.Init.AccumulatedVBP = 5;
  hltdc.Init.AccumulatedActiveW = 654;
  hltdc.Init.AccumulatedActiveH = 485;
  hltdc.Init.TotalWidth = 660;
  hltdc.Init.TotalHeigh = 487;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }

  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 0;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 0;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }

  pLayerCfg1.WindowX0 = 0;
  pLayerCfg1.WindowX1 = 0;
  pLayerCfg1.WindowY0 = 0;
  pLayerCfg1.WindowY1 = 0;
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg1.Alpha = 0;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg1.FBStartAdress = 0;
  pLayerCfg1.ImageWidth = 0;
  pLayerCfg1.ImageHeight = 0;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* FMC initialization function */
static void MX_FMC_Init(void)
{
  FMC_SDRAM_TimingTypeDef SdramTiming;

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_11;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_2;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_1;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_DISABLE;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 16;
  SdramTiming.ExitSelfRefreshDelay = 16;
  SdramTiming.SelfRefreshTime = 16;
  SdramTiming.RowCycleDelay = 16;
  SdramTiming.WriteRecoveryTime = 16;
  SdramTiming.RPDelay = 16;
  SdramTiming.RCDDelay = 16;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler();
  }

}

/** Pinout Configuration
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
