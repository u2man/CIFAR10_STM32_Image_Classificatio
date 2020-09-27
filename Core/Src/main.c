/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dma2d.h"
#include "fatfs.h"
#include "i2c.h"
#include "libjpeg.h"
#include "ltdc.h"
#include "spi.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "fmc.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
__attribute__((section(".ccmram"))) DIR dir;
__attribute__((section(".ccmram"))) FILINFO fno;

uint32_t offset = 0xD0000000;
RGB_typedef *RGB_matrix;
__attribute__((section(".ccmram"))) uint8_t _aucLine[2048] ;
//uint8_t _aucLine[2048];
uint8_t resize_image_buffr[32*32*3] __attribute__((section(".ccmram")));

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
static void LCD_Config(void);
static uint8_t Jpeg_CallbackFunction( uint32_t DataLength);
void Display_File_JPG_uSD(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  //MX_DMA2D_Init();
  //MX_FMC_Init();
  //MX_LTDC_Init();
  MX_SPI5_Init();
  MX_USART1_UART_Init();
  MX_USB_HOST_Init();
  MX_FATFS_Init();
  MX_LIBJPEG_Init();
  MX_I2C3_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */
  printf("LCD Config\r\n");
  LCD_Config();
  printf("LCD Config OK\r\n");
  BSP_LCD_DisplayStringAtLine(1,(uint8_t*)"CIFAR10 Image Classification");
  BSP_LCD_DisplayStringAtLine(2,(uint8_t*)"STM32Cube AI");
  BSP_LCD_DisplayStringAtLine(3,(uint8_t*)"STM32F429 Discovery");
  BSP_LCD_DisplayStringAtLine(4,(uint8_t*)"JPEG file from USB Flashdisk");
  BSP_LCD_DisplayStringAtLine(5,(uint8_t*)"JPEG file 256x256");
  BSP_LCD_DisplayStringAtLine(6,(uint8_t*)"BLOGNA KANG U-2MAN");
  BSP_LCD_DisplayStringAtLine(7,(uint8_t*)"www.karedox.com");

  HAL_Delay(2000);
  BSP_LCD_Clear(LCD_COLOR_BLACK);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

  //MX_X_CUBE_AI_Process();
    /* USER CODE BEGIN 3 */
  switch(Appli_state){
  case APPLICATION_READY:
  	printf("Open file\r\n");
      Display_File_JPG_uSD();
      //Appli_state = APPLICATION_IDLE;
  	break;
  case APPLICATION_IDLE:
	  printf("IDLE\r\n");
  default:
  	break;
  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 50;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void LCD_Config(void)
{
  /* Initialize the LCD */
  BSP_LCD_Init();

  /* Background Layer Initialization */
  BSP_LCD_LayerDefaultInit(0, LCD_BUFFER);

  /* Set Foreground Layer */
  BSP_LCD_SelectLayer(0);

  /* Enable the LCD */
  BSP_LCD_DisplayOn();

  /* Set the layer window */
  //BSP_LCD_SetLayerWindow(0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

  /* Clear the LCD Background layer */
  BSP_LCD_SetTransparency(0,255);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}

static uint8_t Jpeg_CallbackFunction( uint32_t DataLength)
{

//#ifdef DONT_USE_DMA2D
  RGB_matrix =  (RGB_typedef*)_aucLine;
  uint32_t  ARGB32Buffer[IMAGE_WIDTH];
  uint32_t counter = 0;

  for(counter = 0; counter < IMAGE_WIDTH; counter++)
  {
    ARGB32Buffer[counter]  = (uint32_t)
    (
     ((RGB_matrix[counter].B << 16)|
      (RGB_matrix[counter].G << 8)|
      (RGB_matrix[counter].R) | 0xFF000000)
    );

    *(__IO uint32_t *)(LCD_BUFFER + (counter*4) + (offset - LCD_BUFFER)) = ARGB32Buffer[counter];
  }
//#endif

#ifdef USE_DMA2D
  static DMA2D_HandleTypeDef DMA2DHandle;


/* Configure the DMA2D Mode, Color Mode and output offset */
  DMA2DHandle.Init.Mode         = DMA2D_M2M_PFC;
  DMA2DHandle.Init.ColorMode    = DMA2D_ARGB8888;
  DMA2DHandle.Init.OutputOffset = 0;

  /* Foreground Configuration */
  DMA2DHandle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  DMA2DHandle.LayerCfg[1].InputAlpha = 0xFF;
  DMA2DHandle.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB888;
  DMA2DHandle.LayerCfg[1].InputOffset = 0;

  DMA2DHandle.Instance = DMA2D;

  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&DMA2DHandle) == HAL_OK)
  {
    if(HAL_DMA2D_ConfigLayer(&DMA2DHandle, 1) == HAL_OK)
    {
      if (HAL_DMA2D_Start(&DMA2DHandle, (uint32_t)_aucLine, (uint32_t)offset, IMAGE_WIDTH, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */
        HAL_DMA2D_PollForTransfer(&DMA2DHandle, 10);
      }
    }
  }
#endif

#ifdef SWAP_RB
  uint32_t pixel = 0, width_counter, result = 0, result1 = 0;

  for(width_counter = 0; width_counter < IMAGE_WIDTH; width_counter++)
  {
    pixel = *(__IO uint32_t *)(LCD_BUFFER + (width_counter*4) + (offset - LCD_BUFFER));
    result1 = (((pixel & 0x00FF0000) >> 16) | ((pixel & 0x000000FF) << 16));
    pixel = pixel & 0xFF00FF00;
    result = (result1 | pixel);
    *(__IO uint32_t *)(LCD_BUFFER + (width_counter*4) + (offset - LCD_BUFFER)) = result;

  }
#endif

  offset += (DataLength + IMAGE_WIDTH);
  return 0;
}

void Display_File_JPG_uSD(void){
	FRESULT res;
	int i,x=10;


	//BSP_LCD_Debug( (uint8_t*)"Chaneg directori to /Picture...");
	//Change directory to /Picture
	printf("Change Directory\r\n");

	if (f_chdir("/Media")==FR_OK){
		printf("Chaneg directori to /Picture...OK\r\n");
		//search file *.jpg
		//BSP_LCD_Debug( (uint8_t*)"Search .jpg and jpeg files...");
		res=f_findfirst(&dir, &fno, "","*.j*g");

		while((res == FR_OK) && (fno.fname[0])){
	     offset = 0xD0000000;
		 memset(_aucLine,'\0',sizeof(_aucLine));
		 printf("open file %s\r\n", fno.fname);
		 for(i=9;i<9+5;i++)
		   BSP_LCD_ClearStringLine(i);
	     jpeg_decode((uint8_t*)fno.fname, IMAGE_WIDTH, Jpeg_CallbackFunction);
	     resize_jpeg_to32x32((uint8_t*)fno.fname, IMAGE_WIDTH);
          printf("Jpeg decode finis\r\n");
          MX_X_CUBE_AI_Process();
	     res = f_findnext(&dir,&fno);
		 HAL_Delay(2000);
		}

		f_closedir(&dir);
		printf("Finish %d\r\n",res);


	}
	else{
	}



}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
