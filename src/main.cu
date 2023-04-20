#include "../include/dep.h"

__global__ void kernel(void){
    printf("Hello from the kernel! \n");
}

__global__ void gpu_print(void){
    printf("Hello from thread [%d, %d]\n", threadIdx.x, blockIdx.x);
}

int main(void){
    dtype a = 10;
    printf("Hello [from host], a w/ dtype  = %d\n", a);

    kernel<<<1, 1>>>();
    cudaDeviceSynchronize();

    gpu_print<<<2, 1>>>();
    cudaDeviceSynchronize();
}