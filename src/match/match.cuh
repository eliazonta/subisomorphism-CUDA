#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <cublas_v2.h> // -lcublas
#include <cub/cub.cuh> 
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <cub/cub.cuh> 

#include "utils/utils.cuh"
// below is for smid, detecting running on which SM.
#define DEVICE_INTRINSIC_QUALIFIERS   __device__ __forceinline__

void initGPU(int dev);

DEVICE_INTRINSIC_QUALIFIERS
unsigned int
smid();

void exclusive_sum(unsigned* d_array, unsigned size);