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
#include "proc.h"
#include "stdlib.h"
#include "sdram.h"  
#include "lcd_rgb.h"
#include "lcd_pwm.h"
#include "touch_800x480.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "lv_demo_widgets.h"
#include "gui.h"
#include "imu.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */
char test_buf[1024] = {"0000\r\n"};
UINT br,bw;			//读写变量
double average[360] = {0};
GPS_msgTypeDef precise_point = {
  32.136002525,
  0,
  118.696729652,
  0
};
extern char SDPath[4];	
extern FATFS 	SD_FatFs; 		// 文件系统对象
extern FRESULT 	MyFile_Res;    // 操作结果 
//计算过average的flag
uint8_t average_flag = 0;
uint8_t imu_save_flag = 0;
uint8_t gps_save_flag = 0;

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
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ledtoggle */
osThreadId_t ledtoggleHandle;
const osThreadAttr_t ledtoggle_attributes = {
  .name = "ledtoggle",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for printmsgu2 */
osThreadId_t printmsgu2Handle;
const osThreadAttr_t printmsgu2_attributes = {
  .name = "printmsgu2",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for gps_task */
osThreadId_t gps_taskHandle;
const osThreadAttr_t gps_task_attributes = {
  .name = "gps_task",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for msgwrite_task */
osThreadId_t msgwrite_taskHandle;
const osThreadAttr_t msgwrite_task_attributes = {
  .name = "msgwrite_task",
  .stack_size = 1792 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for imu_task */
osThreadId_t imu_taskHandle;
const osThreadAttr_t imu_task_attributes = {
  .name = "imu_task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for gpshuart_flagq */
osMessageQueueId_t gpshuart_flagqHandle;
uint8_t gpshuart_flagqBuffer[ 8 * sizeof( uint8_t ) ];
osStaticMessageQDef_t gpshuart_flagqControlBlock;
const osMessageQueueAttr_t gpshuart_flagq_attributes = {
  .name = "gpshuart_flagq",
  .cb_mem = &gpshuart_flagqControlBlock,
  .cb_size = sizeof(gpshuart_flagqControlBlock),
  .mq_mem = &gpshuart_flagqBuffer,
  .mq_size = sizeof(gpshuart_flagqBuffer)
};
/* Definitions for gpsmsgq */
osMessageQueueId_t gpsmsgqHandle;
uint8_t gpsmsgqBuffer[ 64 * sizeof( GPS_msgTypeDef ) ];
osStaticMessageQDef_t gpsmsgqControlBlock;
const osMessageQueueAttr_t gpsmsgq_attributes = {
  .name = "gpsmsgq",
  .cb_mem = &gpsmsgqControlBlock,
  .cb_size = sizeof(gpsmsgqControlBlock),
  .mq_mem = &gpsmsgqBuffer,
  .mq_size = sizeof(gpsmsgqBuffer)
};
/* Definitions for gpswriteq */
osMessageQueueId_t gpswriteqHandle;
uint8_t gpswriteqBuffer[ 4 * sizeof( uint16_t ) ];
osStaticMessageQDef_t gpswriteqControlBlock;
const osMessageQueueAttr_t gpswriteq_attributes = {
  .name = "gpswriteq",
  .cb_mem = &gpswriteqControlBlock,
  .cb_size = sizeof(gpswriteqControlBlock),
  .mq_mem = &gpswriteqBuffer,
  .mq_size = sizeof(gpswriteqBuffer)
};
/* Definitions for imu_msg */
osMessageQueueId_t imu_msgHandle;
uint8_t imu_msgBuffer[ 4 * sizeof( GEOData_Packet_t ) ];
osStaticMessageQDef_t imu_msgControlBlock;
const osMessageQueueAttr_t imu_msg_attributes = {
  .name = "imu_msg",
  .cb_mem = &imu_msgControlBlock,
  .cb_size = sizeof(imu_msgControlBlock),
  .mq_mem = &imu_msgBuffer,
  .mq_size = sizeof(imu_msgBuffer)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void gps_task_handler(void *argument);
void msgwrite_task_handler(void *argument);
void imu_task_handler(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
  // 告诉lvgl已经过去了1毫秒
	lv_tick_inc(1);
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

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

  /* creation of gpsmsgq */
  gpsmsgqHandle = osMessageQueueNew (64, sizeof(GPS_msgTypeDef), &gpsmsgq_attributes);

  /* creation of gpswriteq */
  gpswriteqHandle = osMessageQueueNew (4, sizeof(uint16_t), &gpswriteq_attributes);

  /* creation of imu_msg */
  imu_msgHandle = osMessageQueueNew (4, sizeof(GEOData_Packet_t), &imu_msg_attributes);

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

  /* creation of gps_task */
  gps_taskHandle = osThreadNew(gps_task_handler, NULL, &gps_task_attributes);

  /* creation of msgwrite_task */
  msgwrite_taskHandle = osThreadNew(msgwrite_task_handler, NULL, &msgwrite_task_attributes);

  /* creation of imu_task */
  imu_taskHandle = osThreadNew(imu_task_handler, NULL, &imu_task_attributes);

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
  osDelay(100);
  // printf("main task*: fs check\r\n");
  // FatFs_Check();			//判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
  // printf("main task*: fs getvolme\r\n");
  // FatFs_GetVolume();	// 计算设备容量
  
  printf("main task*: run my gui\r\n");
  my_gui();
	// lv_demo_benchmark();   // 运行官方例程 lv_demo_benchmark ，进行基准性能测试



  printf("main task*: all init done\r\n");
  // osDelay(500);
  // FatFs_FileTest();		//文件创建和写入测试
  /* Infinite loop */
  for(;;)
  {
    // osDelay(1);
    // printf("main task*: lv_task_handler\r\n");
    // vTaskDelay(pdMS_TO_TICKS(200));
    osDelay(100);
    lv_task_handler();
    // printf("main task*: Touch_Scan\r\n");
    Touch_Scan();
    // printf("main task*: vTaskDelay 1000\r\n");
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
  // LED 任务
  /* Infinite loop */

  for(;;)
  {
    // HAL_Delay(1000);
    osDelay(500);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    // printf("led task*: TogglePin\r\n");
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
  
  /* Infinite loop */
  for(;;)
  {
  //  printf("print task*: print\r\n");
   osDelay(10);
    // osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_gps_task_handler */
/**
* @brief Function implementing the gps_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_gps_task_handler */
void gps_task_handler(void *argument)
{
  /* USER CODE BEGIN gps_task_handler */
  static uint32_t counter = 0;
  uint16_t i = 0;
  uint8_t msg1[] = "gpgga 0.5\r\n";
  uint8_t msg2[] = "HEADINGA 0.5\r\n";
  uint8_t msg3[] = "unlog\r\n";
  static uint8_t pgpsh_flag;
  static GPS_msgTypeDef GPSH_msgStructure;
  int val;
  printf("gps task*: enter gps task\r\n");


    // 开始usart1数据接受
  // osDelay(200);
  printf("gps task*: uart1 start receive\r\n");
  HAL_UART_Receive_IT(&huart1,(uint8_t *)Rx1Temp, REC_LENGTH);	//重新使能中断
  // osDelay(200);
  // 开始gps数据收发
  printf("gps task*: uart2 start receive\r\n");
  HAL_UART_Receive_IT(&huart2,(uint8_t *)RxTemp, REC_LENGTH);	//重新使能中断
  osDelay(1000);
  printf("try %s\n\r", msg1);

  HAL_UART_Transmit(&huart2,msg1, sizeof(msg1), 0xFFFF);
  osDelay(10);
  HAL_UART_Transmit(&huart2,msg1, sizeof(msg1), 0xFFFF);
  osDelay(10);
  HAL_UART_Transmit(&huart2,msg1, sizeof(msg1), 0xFFFF);
  osDelay(1000);
  HAL_UART_Transmit(&huart2,msg2, sizeof(msg2), 0xFFFF);
  osDelay(10);
  HAL_UART_Transmit(&huart2,msg2, sizeof(msg2), 0xFFFF);
  osDelay(10);
  HAL_UART_Transmit(&huart2,msg2, sizeof(msg2), 0xFFFF);
  osDelay(10);

  /* Infinite loop */
  for(;;)
  {
    // osDelay(20);
    if (osOK == osMessageQueueGet(gpshuart_flagqHandle, &pgpsh_flag, 0U, 0)) {
      // printf("msg:%s\r\n", RxBuffer);

      // 如果是1，说明是数据
      if(pgpsh_flag == 1) {
        val =read_msg(RxBuffer, &GPSH_msgStructure);
        // printmsg(GPSH_msgStructure);
        if(val == 0) {
          for (i = 0; i < 360; i ++) {
            average[i] += to_distance_angle_structure(precise_point, (double)i, GPSH_msgStructure);
          }
          counter += 1;
          printf("gps task*: counter= %d\r\n", counter);
          osMessageQueuePut(gpsmsgqHandle, &GPSH_msgStructure, 1U, 0U); //
        } else if (val == 1) {
          printf("gps task*: dir:%lf\r\n ", dir);
          
        }

      } else if (pgpsh_flag == 2) {
        // 如果是2，说明是指令，计算所有average
        printf("gps task*: calculate average\r\n");
        for(i = 0; i < 360; i ++) {
          average[i] /= counter;
        }
        average_flag = 1;
        for(i = 0; i < 360; i ++) {
          printf("gps task*: average[%d] = %lf\r\n", i, average[i]);
        }
      // printmsg(GPSH_msgStructure);
      }
    }
    osDelay(20);
    // printf("gps task*: osDelay\r\n");
  }
  /* USER CODE END gps_task_handler */
}

/* USER CODE BEGIN Header_msgwrite_task_handler */
/**
* @brief Function implementing the msgwrite_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_msgwrite_task_handler */
void msgwrite_task_handler(void *argument)
{
  /* USER CODE BEGIN msgwrite_task_handler */
  static GPS_msgTypeDef msg;
  uint8_t lenth = 0;
  uint8_t i = 0;
  static int flag = 0;
	uint16_t BufferSize = 0;	
	FIL	MyFile;			// 文件对象
	UINT 	MyFile_Num;		//	数据长度
	BYTE 	MyFile_WriteBuffer[81] = "";	//要写入的数据
  GPS_msgTypeDef nlonlatpoint = {0,0,0,0};
	// BYTE 	MyFile_ReadBuffer[1024];	//要读出的数据

  // FatFs_Check();			//判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
	// MyFile_Res = f_mount(&SD_FatFs,"0:",1);	//	挂载SD卡
  
  // if (MyFile_Res == FR_OK)	//判断是否挂载成功
	// {
		// printf("msg writer*: SD文件系统挂载成功\r\n");
	// }
  printf("writer task*: fs check\r\n");
  FatFs_Check();			//判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
  printf("writer task*: fs getvolme\r\n");
  FatFs_GetVolume();	
  for (;;) {
    if (delete_flag == 1) {
      f_close(&MyFile);	  //关闭文件	
      delete_flag = 0;
      printf("writer*: save file\r\n");
      // vTaskDelete(NULL);
    }
    if (gps_save_flag  == 0 && imu_save_flag == 0) {  
      osDelay( 20);
      continue;
    }

    if (gps_save_flag == 1){
      f_unlink("0:GPS.txt");	  //删除文件
      osDelay(20);
      MyFile_Res = f_open(&MyFile,"0:GPS.txt",FA_CREATE_ALWAYS | FA_WRITE);
    }
      
    else if (imu_save_flag == 1){
      f_unlink("0:IMU.txt");	  //删除文件
      osDelay(20);
      MyFile_Res = f_open(&MyFile,"0:IMU.txt",FA_CREATE_ALWAYS | FA_WRITE);
    }
    // printf("writer*: file open success\r\n");

    if(MyFile_Res == FR_OK)
    {
      printf("writer*: file open success\r\n");
      // f_close(&MyFile);	  //关闭文件	

    }
    else
    {
      printf("writer*: cannot open file, %d\r\n", MyFile_Res);
      f_close(&MyFile);	  //关闭文件	
      FatFs_Check();
      // return ERROR;		
      // delete_flag = 1;
      gps_save_flag = 0;
      imu_save_flag = 0;
      delete_flag = 1;
      // vTaskDelete(NULL);
      // vTaskDelete(NULL);
    }
    /* Infinite loop */
    for(;!delete_flag;)
    {
      // printf("msgwrite task*: osDelay\r\n");
      if(osOK == osMessageQueueGet(gpsmsgqHandle, &msg, 0U, 0) && flag == 0){
        
        if(average_flag) {//计算过average 相当于可以修正了
          nlonlatpoint = structure_nlonlat(msg, average, dir);
        }

        // MyFile_Res = f_open(&MyFile,"0:Msg.txt",FA_CREATE_ALWAYS | FA_WRITE);

        if(MyFile_Res == FR_OK)
        {
          // f_lseek(&MyFile,f_size(&MyFile));	  //移动文件指针到文件末尾
          lenth = sprintf(MyFile_WriteBuffer, "%.9lf,%.9lf,%.2f,%.9lf,%.9lf\n", msg.latd, msg.lond, dir, nlonlatpoint.latd, nlonlatpoint.lond);
          printf("writer*: write: %s\r\n", MyFile_WriteBuffer);
          // printf("%s\r\n",MyFile_WriteBuffer)
          MyFile_Res = f_write(&MyFile,MyFile_WriteBuffer, lenth,&MyFile_Num);	//向文件写入数据
          printf("writer*: write length: %d\r\n", MyFile_Num);
          if (MyFile_Res == FR_OK)	
          {
            printf("writer*: write success\r\n");
            // printf("%s\r\n",MyFile_WriteBuffer);
          }
          else
          {
            printf("writer*: write failed, %d\r\n",MyFile_Res );
            f_close(&MyFile);	  //关闭w`文件	
                  gps_save_flag = 0;
              imu_save_flag = 0;
              delete_flag = 1;
            // vTaskDelete(NULL);
          }
        }
        else
        {
          printf("writer*: cannot open file, %d\r\n", MyFile_Res);
          f_close(&MyFile);	  //关闭文件	
          // return ERROR;		
                gps_save_flag = 0;
      imu_save_flag = 0;
      delete_flag = 1;
          // vTaskDelete(NULL);
        }
      

      }

     
      // osDelay(20);

      osDelay(20);
      // osDelay(1);
    }
  }
  /* USER CODE END msgwrite_task_handler */
}

/* USER CODE BEGIN Header_imu_task_handler */
/**
* @brief Function implementing the imu_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_imu_task_handler */
void imu_task_handler(void *argument)
{
  /* USER CODE BEGIN imu_task_handler */
  static GEOData_Packet_t imumsg;
  static GPS_msgTypeDef gpsmsg;
  // osDelay(1000);   
  HAL_UART_Receive_IT(&huart5,(uint8_t *)Rx5Temp, REC_LENGTH);	//重新使能中断
  /* Infinite loop */
  for(;;)
  {
    // 如果队列有消息
    if(osOK == osMessageQueueGet(imu_msgHandle, &imumsg, 0U, 0)){
      // print_imu_data(&imumsg);
      if (imu_save_flag == 1) {
        gpsmsg.latd = rad2deg(imumsg.latitude);
        gpsmsg.lond = rad2deg(imumsg.longitude);
          osMessageQueuePut(gpsmsgqHandle, &gpsmsg, 1U, 0U); //
        
      }
    }
    osDelay(10);
  }
  /* USER CODE END imu_task_handler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

