/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * File Name          : libjpeg.c
  * Description        : This file provides code for the configuration
  *                      of the libjpeg instances.
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
#include "libjpeg.h"

/* USER CODE BEGIN 0 */
#include "global.h"
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */

/* Global variables ---------------------------------------------------------*/

/* USER CODE BEGIN 2 */
__attribute__((section(".ccmram"))) struct jpeg_decompress_struct cinfo;
/* This struct represents a JPEG error handler */
__attribute__((section(".ccmram"))) struct jpeg_error_mgr jerr;
__attribute__((section(".ccmram"))) JSAMPROW buffer[1] = {0};
__attribute__((section(".ccmram"))) FIL file;
__attribute__((section(".ccmram"))) uint16_t resizedImageCounter=0;

/* USER CODE END 2 */

/* LIBJPEG init function */
void MX_LIBJPEG_Init(void)
{
/***************************************/
   /**
  */

  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */

}

/* USER CODE BEGIN 4 */
void resize_jpeg_to32x32(uint8_t *filename, uint32_t width){


	  /* Decode JPEG Image */
	  JSAMPROW buffer[2] = {0}; /* Output row buffer */
	  FIL file;


	  if(f_open(&file, (char*)filename, FA_READ) != FR_OK)
	  {
	 	 printf("open file error\r\n");
	 	 return;
	  }


	  buffer[0] = &_aucLine[0];

	  /* Step 1: allocate and initialize JPEG decompression object */
	  cinfo.err = jpeg_std_error(&jerr);

	  /* Initialize the JPEG decompression object */
	  jpeg_create_decompress(&cinfo);

	  jpeg_stdio_src (&cinfo, &file);

	  /* Step 3: read image parameters with jpeg_read_header() */
	  jpeg_read_header(&cinfo, TRUE);

	  /* Step 4: set parameters for decompression */
	  cinfo.dct_method = JDCT_FLOAT;

	  /* Step 5: start decompressor */
	  cinfo.scale_num=1;
	  cinfo.scale_denom=8;
	  jpeg_start_decompress(&cinfo);

	  printf("Jpeg Sie %dx%d\r\n",cinfo.output_width, cinfo.output_height);

	  //row_stride = width * 3;
	  resizedImageCounter=0;
	  while (cinfo.output_scanline < cinfo.output_height)
	  {
		  (void) jpeg_read_scanlines(&cinfo, buffer, 1);
		  SaveResizedImageToBuffer(buffer[0]);
	  }

	  //printf("rezide image counter %d\r\n",resizedImageCounter);

	  /* Step 6: Finish decompression */
	  jpeg_finish_decompress(&cinfo);

	  /* Step 7: Release JPEG decompression object */
	  jpeg_destroy_decompress(&cinfo);
	  f_close(&file);



}

void SaveResizedImageToBuffer(uint8_t* buffer){
	  uint32_t i = 0;
	  RGB_matrix =  (RGB_typedef*)_aucLine;
	  //uint16_t  ypos, xpos,x;
	  //uint32_t  ARGB32Buffer[128];


	RGB_matrix =  (RGB_typedef*)buffer;
	  for(i=0;i<32;i++){
		  resize_image_buffr[resizedImageCounter++]=RGB_matrix[i].R;
		  resize_image_buffr[resizedImageCounter++]=RGB_matrix[i].G;
		  resize_image_buffr[resizedImageCounter++]=RGB_matrix[i].B;

	  }

}


void jpeg_decode(uint8_t *filename, uint32_t width, uint8_t (*callback)( uint32_t))
{
	  /* Decode JPEG Image */
	 /* Output row buffer */
	  uint32_t row_stride = 0; /* physical row width in image buffer */




	 // BSP_LCD_Debug((uint8_t*)"jpeg decode");

   if(f_open(&file, (char*)filename, FA_READ) != FR_OK)
   {
  	 printf("open file error\r\n");
  	 return;
   }


	  buffer[0] = &_aucLine[0];

	  /* Step 1: allocate and initialize JPEG decompression object */
	  //BSP_LCD_Debug((uint8_t*)"init cinfo.err");
	  cinfo.err = jpeg_std_error(&jerr);

	  /* Initialize the JPEG decompression object */
	  //BSP_LCD_Debug((uint8_t*)"init cinfo");
	  jpeg_create_decompress(&cinfo);

      jpeg_stdio_src (&cinfo, &file);

	  /* Step 3: read image parameters with jpeg_read_header() */
      jpeg_read_header(&cinfo, TRUE);

	  /* Step 4: set parameters for decompression */
	  cinfo.dct_method = JDCT_IFAST;
	  cinfo.scale_num=1;
	  cinfo.scale_denom=2;

	  /* Step 5: start decompressor */
	  jpeg_start_decompress(&cinfo);

	  //printf("image size %d x %d\r\n",cinfo.image_width, cinfo.image_height);
	  printf("outpur %d x %d\r\n",cinfo.output_width, cinfo.output_height);

	  //if((cinfo.image_width==320)&&(cinfo.image_height==240)){
	  row_stride = width * 3;

    if((cinfo.output_height==128)&&(cinfo.output_width==128)){
	  while (cinfo.output_scanline < cinfo.output_height)
	  {
	    (void) jpeg_read_scanlines(&cinfo, buffer, 1);

	    if (callback(row_stride) != 0)
	    {
	      break;
	    }
	  }
    }

	  /* Step 6: Finish decompression */
	  jpeg_finish_decompress(&cinfo);

	  /* Step 7: Release JPEG decompression object */
	  jpeg_destroy_decompress(&cinfo);

	  f_close(&file);
}

/* USER CODE END 4 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
