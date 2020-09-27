/*
 * global.c
 *
 *  Created on: Sep 26, 2020
 *      Author: Kang Usman
 */


#include "global.h"

__attribute__((section(".ccmram"))) float predictionval[10];
 __attribute__((section(".ccmram"))) uint8_t class_name_index[10];

 static void Bubblesort(void);

 void RGB24_to_Float_Asym(uint8_t *pSrc, uint8_t *pDst, uint32_t pixels){
	  struct rgb
	  {
	    uint8_t r, g, b;
	  };
	  struct rgbf
	  {
	    float r, g, b;
	  };
	  struct rgb *pivot = (struct rgb *) pSrc;
	  //struct rgbf *dest = (struct rgbf *) pDst;
	  float dummy;
	  uint16_t j,x=0;


	  for (int i = 0; i < pixels; i++)
	  {
	    dummy = (((float)(pivot[i].b)) / 255.0F);
	    uint8_t* pr = (uint8_t*)(void*)&dummy;
	    for(j=0;j<4;j++){
	    //for(j=3;j>0;j--){
	    	pDst[x++]=pr[j];
	    }

	    dummy = (((float)(pivot[i].g)) / 255.0F);
	    uint8_t* pg = (uint8_t*)(void*)&dummy;
	    for(j=0;j<4;j++){
	    //for(j=3;j>0;j--){
	    	pDst[x++]=pg[j];
	    }

	    dummy = (((float)(pivot[i].r)) / 255.0F);
	    uint8_t* pb = (uint8_t*)(void*)&dummy;
	    for(j=0;j<4;j++){
	    //for(j=3;j>0;j--){
	    	pDst[x++]=pb[j];
	    }
	  }

 }


 void AI_Output_Display(uint8_t* AI_out_data){
	 uint16_t i,j,x=0;
	 float dummyfloat;
	 uint32_t u32dummy;


	 for(i=0;i<10;i++){
			uint8_t* p = (uint8_t*)(void*)&dummyfloat;
			u32dummy = (uint8_t)AI_out_data[x+3];
			u32dummy = (u32dummy << 8)|(uint8_t)AI_out_data[x+2];
			u32dummy = (u32dummy << 8)|(uint8_t)AI_out_data[x+1];
			u32dummy = (u32dummy << 8)|(uint8_t)AI_out_data[x];
			x+=4;
			for(j=0;j<4;j++){
				p[j]=u32dummy >> (8*j);
			}
	       predictionval[i]=dummyfloat*100;
	 }

	 Bubblesort();
}


 static void Bubblesort(void){
 	int total_count, counter, counter1,swap_rank;
 	float swap_var;
 	 total_count=10;

 	 for(counter=0;counter<10;counter++){
 		 class_name_index[counter]= counter;
 	 }

 	for (counter = 0 ; counter < total_count - 1; counter++){
 		for (counter1 = 0 ; counter1 < total_count - counter - 1; counter1++){
 			if(predictionval[counter1]>predictionval[ counter1+1]){
 				swap_var = predictionval[counter1];
 				predictionval[counter1]=predictionval[counter1+1];
 				predictionval[counter1+1]=swap_var;

 				swap_rank = class_name_index[counter1];
 				class_name_index[counter1]=class_name_index[counter1+1];
 				class_name_index[counter1+1]=swap_rank;
 			}
 		}
 	}

 }

