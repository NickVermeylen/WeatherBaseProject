/**
 ******************************************************************************
  * File Name          : LWIP.c
  * Description        : This file provides initialization code for LWIP
  *                      middleWare.
  ******************************************************************************
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
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "lwip.h"
#include "lwip/init.h"
#include "lwip/netif.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* ETH Variables initialization ----------------------------------------------*/
void Error_Handler(void);

 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* Variables Initialization */
struct netif gnetif;
ip4_addr_t ipaddr;
ip4_addr_t netmask;
ip4_addr_t gw;
uint8_t IP_ADDRESS[4];
uint8_t NETMASK_ADDRESS[4];
uint8_t GATEWAY_ADDRESS[4];
#n/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
#n
/**
#t* LwIP initialization function
#t*/
void MX_LWIP_Init(void)
{
#t/* IP addresses initialization */
#tIP_ADDRESS[0] = 192;
#tIP_ADDRESS[1] = 168;
#tIP_ADDRESS[2] = 0;
#tIP_ADDRESS[3] = 50;
#tNETMASK_ADDRESS[0] = 255;
#tNETMASK_ADDRESS[1] = 255;
#tNETMASK_ADDRESS[2] = 255;
#tNETMASK_ADDRESS[3] = 0;
#tGATEWAY_ADDRESS[0] = 192;
#tGATEWAY_ADDRESS[1] = 168;
#tGATEWAY_ADDRESS[2] = 0;
#tGATEWAY_ADDRESS[3] = 1;
#t
#t/* Initilialize the LwIP stack without RTOS */
#tlwip_init();
#n#t/* IP addresses initialization without DHCP (IPv4) */
#tIP4_ADDR(&ipaddr, IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
#tIP4_ADDR(&netmask, NETMASK_ADDRESS[0], NETMASK_ADDRESS[1] , NETMASK_ADDRESS[2], NETMASK_ADDRESS[3]);
#tIP4_ADDR(&gw, GATEWAY_ADDRESS[0], GATEWAY_ADDRESS[1], GATEWAY_ADDRESS[2], GATEWAY_ADDRESS[3]);
#n#t/* add the network interface (IPv4/IPv6) without RTOS */
#tnetif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);
#n
#t/* Registers the default network interface */
#tnetif_set_default(&gnetif);
#n
#tif (netif_is_link_up(&gnetif))
#t{
#t#t/* When the netif is fully configured this function must be called */
#t#tnetif_set_up(&gnetif);
#t}
#telse
#t{
#t#t/* When the netif link is down this function must be called */
#t#tnetif_set_down(&gnetif);
#t}
#n
#n
#n
#n/* USER CODE BEGIN 3 */
#n
/* USER CODE END 3 */
}
/* USER CODE BEGIN 4 */
#n
/**
 * ----------------------------------------------------------------------
 * Function given to help user to continue LwIP Initialization
 * Up to user to complete or change this function ...
 * Up to user to call this function in main.c in while (1) of main(void) 
 *-----------------------------------------------------------------------
 * Read a received packet from the Ethernet buffers 
 * Send it to the lwIP stack for handling
 * Handle timeouts if NO_SYS_NO_TIMERS not set and without RTOS
 */
void MX_LWIP_Process(void)
{
  ethernetif_input(&gnetif);
       
  /* Handle timeouts */
  #if !NO_SYS_NO_TIMERS && NO_SYS
    sys_check_timeouts();
  #endif
    
}
/* USER CODE END 4 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
