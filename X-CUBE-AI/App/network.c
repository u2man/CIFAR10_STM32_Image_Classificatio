/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Sat Sep 26 20:57:16 2020
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 1
#define AI_TOOLS_VERSION_MICRO 2


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "df5445d4a52c9015beb033aed4e4bda3"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.1.2)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Sat Sep 26 20:57:16 2020"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_4_scratch0_array;   /* Array #0 */
AI_STATIC ai_array conv2d_2_scratch0_array;   /* Array #1 */
AI_STATIC ai_array dense_2_bias_array;   /* Array #2 */
AI_STATIC ai_array dense_2_weights_array;   /* Array #3 */
AI_STATIC ai_array dense_1_bias_array;   /* Array #4 */
AI_STATIC ai_array dense_1_weights_array;   /* Array #5 */
AI_STATIC ai_array conv2d_4_bias_array;   /* Array #6 */
AI_STATIC ai_array conv2d_4_weights_array;   /* Array #7 */
AI_STATIC ai_array conv2d_3_bias_array;   /* Array #8 */
AI_STATIC ai_array conv2d_3_weights_array;   /* Array #9 */
AI_STATIC ai_array conv2d_2_bias_array;   /* Array #10 */
AI_STATIC ai_array conv2d_2_weights_array;   /* Array #11 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #12 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #13 */
AI_STATIC ai_array input_0_output_array;   /* Array #14 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #15 */
AI_STATIC ai_array conv2d_2_output_array;   /* Array #16 */
AI_STATIC ai_array conv2d_3_output_array;   /* Array #17 */
AI_STATIC ai_array conv2d_4_output_array;   /* Array #18 */
AI_STATIC ai_array dense_1_output_array;   /* Array #19 */
AI_STATIC ai_array activation_5_output_array;   /* Array #20 */
AI_STATIC ai_array dense_2_output_array;   /* Array #21 */
AI_STATIC ai_array activation_6_output_array;   /* Array #22 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_4_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_2_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor dense_2_bias;   /* Tensor #2 */
AI_STATIC ai_tensor dense_2_weights;   /* Tensor #3 */
AI_STATIC ai_tensor dense_1_bias;   /* Tensor #4 */
AI_STATIC ai_tensor dense_1_weights;   /* Tensor #5 */
AI_STATIC ai_tensor conv2d_4_bias;   /* Tensor #6 */
AI_STATIC ai_tensor conv2d_4_weights;   /* Tensor #7 */
AI_STATIC ai_tensor conv2d_3_bias;   /* Tensor #8 */
AI_STATIC ai_tensor conv2d_3_weights;   /* Tensor #9 */
AI_STATIC ai_tensor conv2d_2_bias;   /* Tensor #10 */
AI_STATIC ai_tensor conv2d_2_weights;   /* Tensor #11 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #12 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #13 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_2_output;   /* Tensor #16 */
AI_STATIC ai_tensor conv2d_3_output;   /* Tensor #17 */
AI_STATIC ai_tensor conv2d_4_output;   /* Tensor #18 */
AI_STATIC ai_tensor conv2d_4_output0;   /* Tensor #19 */
AI_STATIC ai_tensor dense_1_output;   /* Tensor #20 */
AI_STATIC ai_tensor activation_5_output;   /* Tensor #21 */
AI_STATIC ai_tensor dense_2_output;   /* Tensor #22 */
AI_STATIC ai_tensor activation_6_output;   /* Tensor #23 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_2_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_3_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain conv2d_4_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_1_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain activation_5_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain dense_2_chain;   /* Chain #6 */
AI_STATIC_CONST ai_tensor_chain activation_6_chain;   /* Chain #7 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d conv2d_1_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_2_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d conv2d_3_layer; /* Layer #2 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_4_layer; /* Layer #3 */
AI_STATIC ai_layer_dense dense_1_layer; /* Layer #4 */
AI_STATIC ai_layer_nl activation_5_layer; /* Layer #5 */
AI_STATIC ai_layer_dense dense_2_layer; /* Layer #6 */
AI_STATIC ai_layer_nl activation_6_layer; /* Layer #7 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1664, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1920, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  dense_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  dense_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5120, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_weights_array, AI_ARRAY_FORMAT_LUT4_FLOAT,
  NULL, NULL, 1179648, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 864, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 3072, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32768, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7200, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 14400, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2304, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  activation_5_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  dense_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  activation_6_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 13, 2), AI_STRIDE_INIT(4, 4, 4, 256, 3328),
  1, &conv2d_4_scratch0_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 30, 2), AI_STRIDE_INIT(4, 4, 4, 128, 3840),
  1, &conv2d_2_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  dense_2_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_2_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  dense_2_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 512, 10, 1, 1), AI_STRIDE_INIT(4, 4, 2048, 20480, 20480),
  1, &dense_2_weights_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 512, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2048, 2048),
  1, &dense_1_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 2304, 512, 1, 1), AI_STRIDE_INIT(4, 1, 1152, 589824, 589824),
  1, &dense_1_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_4_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 768, 2304),
  1, &conv2d_4_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_3_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 4, 128, 384, 1152),
  1, &conv2d_3_weights_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_2_bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 384, 1152),
  1, &conv2d_2_weights_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 3, 3, 3, 32), AI_STRIDE_INIT(4, 4, 12, 36, 108),
  1, &conv2d_1_weights_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 32, 32), AI_STRIDE_INIT(4, 4, 4, 12, 384),
  1, &input_0_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 32, 32), AI_STRIDE_INIT(4, 4, 4, 128, 4096),
  1, &conv2d_1_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 15, 15), AI_STRIDE_INIT(4, 4, 4, 128, 1920),
  1, &conv2d_2_output_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 15, 15), AI_STRIDE_INIT(4, 4, 4, 256, 3840),
  1, &conv2d_3_output_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 6, 6), AI_STRIDE_INIT(4, 4, 4, 256, 1536),
  1, &conv2d_4_output_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_output0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2304, 1, 1), AI_STRIDE_INIT(4, 4, 4, 9216, 9216),
  1, &conv2d_4_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 512, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2048, 2048),
  1, &dense_1_output_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  activation_5_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 512, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2048, 2048),
  1, &activation_5_output_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  dense_2_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_2_output_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  activation_6_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &activation_6_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 0,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_2_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_2_weights, &conv2d_2_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_layer, 2,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_3_layer, AI_STATIC,
  .tensors = &conv2d_2_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 6,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_4_layer, AI_STATIC,
  .tensors = &conv2d_3_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_4_weights, &conv2d_4_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_4_layer, 8,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &dense_1_layer, AI_STATIC,
  .tensors = &conv2d_4_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_1_weights, &dense_1_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_1_layer, 13,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &activation_5_layer, AI_STATIC,
  .tensors = &dense_1_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  activation_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &activation_5_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  activation_5_layer, 14,
  NL_TYPE,
  nl, forward_relu,
  &AI_NET_OBJ_INSTANCE, &dense_2_layer, AI_STATIC,
  .tensors = &activation_5_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &activation_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_2_weights, &dense_2_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_2_layer, 16,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &activation_6_layer, AI_STATIC,
  .tensors = &dense_2_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  activation_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &activation_6_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  activation_6_layer, 17,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &activation_6_layer, AI_STATIC,
  .tensors = &activation_6_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 874728, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 140800, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &activation_6_output),
  &conv2d_1_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_4_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_4_scratch0_array.data_start = AI_PTR(activations + 0);
    conv2d_2_scratch0_array.data = AI_PTR(activations + 133120);
    conv2d_2_scratch0_array.data_start = AI_PTR(activations + 133120);
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv2d_1_output_array.data = AI_PTR(activations + 2048);
    conv2d_1_output_array.data_start = AI_PTR(activations + 2048);
    conv2d_2_output_array.data = AI_PTR(activations + 0);
    conv2d_2_output_array.data_start = AI_PTR(activations + 0);
    conv2d_3_output_array.data = AI_PTR(activations + 28800);
    conv2d_3_output_array.data_start = AI_PTR(activations + 28800);
    conv2d_4_output_array.data = AI_PTR(activations + 6656);
    conv2d_4_output_array.data_start = AI_PTR(activations + 6656);
    dense_1_output_array.data = AI_PTR(activations + 0);
    dense_1_output_array.data_start = AI_PTR(activations + 0);
    activation_5_output_array.data = AI_PTR(activations + 2048);
    activation_5_output_array.data_start = AI_PTR(activations + 2048);
    dense_2_output_array.data = AI_PTR(activations + 0);
    dense_2_output_array.data_start = AI_PTR(activations + 0);
    activation_6_output_array.data = AI_PTR(NULL);
    activation_6_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_2_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_2_bias_array.data = AI_PTR(weights + 874688);
    dense_2_bias_array.data_start = AI_PTR(weights + 874688);
    dense_2_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_2_weights_array.data = AI_PTR(weights + 854208);
    dense_2_weights_array.data_start = AI_PTR(weights + 854208);
    dense_1_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_1_bias_array.data = AI_PTR(weights + 852160);
    dense_1_bias_array.data_start = AI_PTR(weights + 852160);
    dense_1_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_1_weights_array.data = AI_PTR(weights + 262336);
    dense_1_weights_array.data_start = AI_PTR(weights + 262272);
    conv2d_4_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_bias_array.data = AI_PTR(weights + 262016);
    conv2d_4_bias_array.data_start = AI_PTR(weights + 262016);
    conv2d_4_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_weights_array.data = AI_PTR(weights + 114560);
    conv2d_4_weights_array.data_start = AI_PTR(weights + 114560);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(weights + 114304);
    conv2d_3_bias_array.data_start = AI_PTR(weights + 114304);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(weights + 40576);
    conv2d_3_weights_array.data_start = AI_PTR(weights + 40576);
    conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_bias_array.data = AI_PTR(weights + 40448);
    conv2d_2_bias_array.data_start = AI_PTR(weights + 40448);
    conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_weights_array.data = AI_PTR(weights + 3584);
    conv2d_2_weights_array.data_start = AI_PTR(weights + 3584);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 3456);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 3456);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 0);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 20866774,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}


#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

