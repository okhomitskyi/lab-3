/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    31-July-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4x7_eth_bsp.h"
#include "netconf.h"
#include "main.h"
#include "tcp_echoserver.h"
#include "serial_debug.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SYSTEMTICK_PERIOD_MS  10
#define MESSAGE2   "  STM32F-4 Series   "
#define MESSAGE3   " TCP echoserver Demo"
#define MESSAGE4   "                    "

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
uint32_t timingdelay;

void LCD_LED_Init(void);


int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  ETH_BSP_Config();
  LwIP_Init();
  tcp_echoserver_init();
  while (1)
  {  
    if (ETH_CheckFrameReceived())
    { 
      LwIP_Pkt_Handle();
    }
    LwIP_Periodic_Handle(LocalTime);
  } 
}

void Delay(uint32_t nCount)
{
  /* Capture the current local time */
  timingdelay = LocalTime + nCount;  

  /* wait until the desired delay finish */  
  while(timingdelay > LocalTime)
  {     
  }
}


void Time_Update(void)
{
  LocalTime += SYSTEMTICK_PERIOD_MS;
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
