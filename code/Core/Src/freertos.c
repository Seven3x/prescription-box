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
#include "gps.h"
#include "usart.h"
#include "sdmmc_sd.h"
#include "stdio.h"
#include "string.h"
#include "ff.h"
#include "sd_diskio.h"
#include "sdcard.h"

#include "sdram.h"  
#include "lcd_rgb.h"
#include "lcd_pwm.h"
#include "touch_800x480.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "lv_demo_widgets.h"
#include "gui.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticQueue_t osStaticMessageQDef_t;
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
/* Definitions for ledtoggle */
osThreadId_t ledtoggleHandle;
const osThreadAttr_t ledtoggle_attributes = {
  .name = "ledtoggle",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for printmsgu2 */
osThreadId_t printmsgu2Handle;
const osThreadAttr_t printmsgu2_attributes = {
  .name = "printmsgu2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for lvgl_task */
osThreadId_t lvgl_taskHandle;
const osThreadAttr_t lvgl_task_attributes = {
  .name = "lvgl_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for gpshuart_flagq */
osMessageQueueId_t gpshuart_flagqHandle;
uint8_t gpshuart_msgqBuffer[ 8 * sizeof( uint8_t ) ];
osStaticMessageQDef_t gpshuart_msgqControlBlock;
const osMessageQueueAttr_t gpshuart_flagq_attributes = {
  .name = "gpshuart_flagq",
  .cb_mem = &gpshuart_msgqControlBlock,
  .cb_size = sizeof(gpshuart_msgqControlBlock),
  .mq_mem = &gpshuart_msgqBuffer,
  .mq_size = sizeof(gpshuart_msgqBuffer)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void lvgl_task_handler(void *argument);

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

  /* Create the queue(s) */
  /* creation of gpshuart_flagq */
  gpshuart_flagqHandle = osMessageQueueNew (8, sizeof(uint8_t), &gpshuart_flagq_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of ledtoggle */
  ledtoggleHandle = osThreadNew(StartTask02, NULL, &ledtoggle_attributes);

  /* creation of printmsgu2 */
  printmsgu2Handle = osThreadNew(StartTask03, NULL, &printmsgu2_attributes);

  /* creation of lvgl_task */
  lvgl_taskHandle = osThreadNew(lvgl_task_handler, NULL, &lvgl_task_attributes);

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
  FatFs_Check();			//判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
  FatFs_GetVolume();	// 计算设备容量
  osDelay(1000);
  
  printf("main task*: run my gui\r\n");
	// lv_demo_benchmark();   // 运行官方例程 lv_demo_benchmark ，进行基准性能测试
  my_gui();
  printf("main task*: uart2 start receive\r\n");
  // 开始gps数据收发
  HAL_UART_Receive_IT(&huart2,(uint8_t *)RxTemp, REC_LENGTH);	//重新使能中断

  printf("main task*: all init done\r\n");
  // FatFs_FileTest();		//文件创建和写入测试
  /* Infinite loop */
  for(;;)
  {
    // osDelay(1);
    // printf("main task*: lv_task_handler\r\n");
    lv_task_handler();
    // printf("main task*: Touch_Scan\r\n");
    Touch_Scan();
    // printf("main task*: vTaskDelay 1000\r\n");
    vTaskDelay(pdMS_TO_TICKS(100));
    // printf("main task*: osDelay(1000)\r\n");
    // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the ledtoggle thread.
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
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    printf("led task*: TogglePin\r\n");
    osDelay(500);
    // osDelay(500);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the print thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  uint8_t msg[] = "gpgga 2\r\n";
  static uint8_t pgpsh_flag;
  static GPS_msgTypeDef GPSH_msgStructure;

  osDelay(3000);
  printf("try %s\n\r", msg);
  // HAL_UART_Transmit(&huart2,(uint8_t *)"unlogall\r\n", 11, 0xFFFF);
  // HAL_UART_Transmit(&huart2,(uint8_t *)"mode base time 60 1.5 2.5\r\n", 11, 0xFFFF);
  // HAL_UART_Transmit(&huart2,(uint8_t *)"config 115200\r\n", 21, 0xFFFF);
  HAL_UART_Transmit(&huart2,msg, sizeof(msg), 0xFFFF);
  HAL_UART_Transmit(&huart2,msg, sizeof(msg), 0xFFFF);
  HAL_UART_Transmit(&huart2,msg, sizeof(msg), 0xFFFF);
  HAL_UART_Transmit(&huart2,msg, sizeof(msg), 0xFFFF);
  /* Infinite loop */
  for(;;)
  {
    if (osOK == osMessageQueueGet(gpshuart_flagqHandle, &pgpsh_flag, 0U, 0)) {
      // printf("msg:%s\r\n", RxBuffer);
      GPSH_msgStructure = read_msg(RxBuffer);
      printmsg(GPSH_msgStructure);
    }
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_lvgl_task_handler */
/**
* @brief Function implementing the lvgl_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_lvgl_task_handler */
void lvgl_task_handler(void *argument)
{
  /* USER CODE BEGIN lvgl_task_handler */
  TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS( 200);
	

  osDelay(2000);
  // printf("lvgl task*: lvgl benchmark\r\n");
	// lv_demo_benchmark();   // 运行官方例程 lv_demo_benchmark ，进行基准性能测试
	// 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同 
	// xLastWakeTime = xTaskGetTickCount();  
  osDelay(500);

  /* Infinite loop */
  for(;;)
  {
  osDelay(100);
    // vTaskDelayUntil( &xLastWakeTime,xPeriod );
    // printf("lvgl task*: lv_task_handler\r\n");
    // lv_task_handler();
    // printf("lvgl task*: Touch_Scan\r\n");
    // Touch_Scan();
    // printf("lvgl task*: vTaskDelay 1000\r\n");
    // vTaskDelay(pdMS_TO_TICKS(20));
  }
  /* USER CODE END lvgl_task_handler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

