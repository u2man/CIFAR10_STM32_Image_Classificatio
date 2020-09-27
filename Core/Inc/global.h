/*
 * global.h
 *
 *  Created on: Jan 31, 2020
 *      Author: Kang Usman
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "crc.h"
#include "dma2d.h"
#include "fatfs.h"
#include "i2c.h"
#include "libjpeg.h"
#include "ltdc.h"
#include "spi.h"
//+#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "fmc.h"
#include "app_x-cube-ai.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"


typedef struct RGB
{
  uint8_t B;
  uint8_t G;
  uint8_t R;
}RGB_typedef;

/* Exported constants --------------------------------------------------------*/
#define IMAGE_HEIGHT 320
#define IMAGE_WIDTH  240
#define LCD_BUFFER   0xD0000000

 //#define USE_DMA2D
 //#define SWAP_RB

extern uint32_t offset;
extern RGB_typedef *RGB_matrix;
extern uint8_t _aucLine[2048] __attribute__((section(".ccmram")));
//extern uint8_t _aucLine[2048];
extern ApplicationTypeDef Appli_state;
extern uint8_t resize_image_buffr[32*32*3] __attribute__((section(".ccmram")));
extern __attribute__((section(".ccmram"))) float predictionval[10];
extern __attribute__((section(".ccmram"))) uint8_t class_name_index[10];


void RGB24_to_Float_Asym(uint8_t *pSrc, uint8_t *pDst, uint32_t pixels);
void AI_Output_Display(uint8_t* AI_out_data);

#endif /* INC_GLOBAL_H_ */
