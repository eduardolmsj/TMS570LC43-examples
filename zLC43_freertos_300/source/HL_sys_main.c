/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "FreeRTOS.h"
#include "os_task.h"
#include "HL_esm.h"
#include "HL_adc.h"
#include "HL_sci.h"
#include "HL_gio.h"
#include "stdio.h"
#include "teste.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

adcData_t adc_data[16];
uint32 ch_count=0;
uint32 id    =0;
uint32 value =0;
uint32_t i;

volatile uint16 ADCBuf[16];

int adc_buffer_size = 16;
int idx;
int adc_value;
unsigned long int mean_adc_value=0;
double pid_output;

xTaskHandle xTask1Handle;
xTaskHandle xTask2Handle;

/* Task1 */
void vTask1(void *pvParameters)
{
    static uint32_t period_ms = 100;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = period_ms / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();

    int n =10;
//    int *insertion_arr = (int *)malloc(n * sizeof(int));
    int insertion_arr[10];

   for(;;)
   {
       gioSetBit(gioPORTA, 6, 1);
       insertion_rotine(n, insertion_arr);
//       vTaskDelay(500);
       gioSetBit(gioPORTA, 6, 0);
       vTaskDelayUntil(&xLastWakeTime, xFrequency);
   }
}
/* Task2 */
void vTask2(void *pvParameters)
{

    static uint32_t period_ms = 100;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = period_ms / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();

    double kp = 1.0;
    double ki = 0.1;
    double kd = 0.01;
    double setpoint = 10.0;
    PIDController pid;

    for(;;)
   {
       gioSetBit(gioPORTA, 7, 1);
       adcGetData(adcREG1, adcGROUP1,&adc_data[0]);
       PID_routine(&pid_output, &pid, kp, ki, kd, setpoint, adc_buffer_size, adc_data, &mean_adc_value);
       gioSetBit(gioPORTA, 7, 0);
//       vTaskDelay(1000);
       vTaskDelayUntil(&xLastWakeTime, xFrequency);
   }
}

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    gioInit();
    gioSetDirection(gioPORTA, 0xFFFFFFFF);
    adcInit();                                                      // Initialize ADC: 12bit Resolution, Enable Channel Id in result
    adcStartConversion(adcREG1,adcGROUP1);

    if (xTaskCreate(vTask1,"Task1", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle) != pdTRUE)
          {
              /* Task could not be created */
              while(1);
          }
          /* Create Task 2 */
      if (xTaskCreate(vTask2,"Task2", configMINIMAL_STACK_SIZE, NULL, 1, &xTask2Handle) != pdTRUE)
      {
          /* Task could not be created */
          while(1);
      }
      /* Start Scheduler */
      vTaskStartScheduler();
      /* Run forever */
      while(1);
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
