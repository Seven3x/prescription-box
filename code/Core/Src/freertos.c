/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "sdcard.h"
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char test_buf[1024] = {"0000\r\n"};
UINT br,bw;			//读写变量
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for printmsg */
osThreadId_t printmsgHandle;
const osThreadAttr_t printmsg_attributes = {
  .name = "printmsg",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for led_toggle */
osThreadId_t led_toggleHandle;
const osThreadAttr_t led_toggle_attributes = {
  .name = "led_toggle",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of printmsg */
  printmsgHandle = osThreadNew(StartTask02, NULL, &printmsg_attributes);

  /* creation of led_toggle */
  led_toggleHandle = osThreadNew(StartTask03, NULL, &led_toggle_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  unsigned char buffer[2048];
  // osDelay(10000);
  /* Infinite loop */
	uint32_t time=0;
	uint32_t time2=0;
	char i;
  osDelay(10);
  printf("SDPath: %s\n\r", SDPath);
  printf("size of FATFS: %d\n\r", sizeof(FATFS));
  printf("size of dir: %d\n\r", sizeof(DIR));
  retSD = f_mount(&SDFatFS,"0:",1);		
  if (retSD == FR_OK)	//判断是否挂载成功
	{
		printf("\r\nSD文件系统挂载成功\r\n");
	}
	while(retSD)
	{
    printf("mount sd failed, error code:%d\n\r", retSD);
    f_mkfs("0:",FM_FAT32,2048,buffer,2048);  
		osDelay(500);
    retSD = f_mount(&SDFatFS,"0:",1);
	}
  printf("mount sd success, retSD:%d\n\r", retSD);

  /* Infinite loop */
  for(;;)
  {
	  
	 
	 
	retSD = f_open(&SDFile, "time.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	f_lseek(&SDFile,time2*5);
	retSD = f_write(&SDFile,&test_buf,strlen(test_buf),&bw) ;

	retSD = f_close(&SDFile);

	time2++;	
	osDelay(1000);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the printmsg thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
    // HAL_Delay(1000);
    printf("Hello World\n");
    osDelay(500);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the led_toggle thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    osDelay(500);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

