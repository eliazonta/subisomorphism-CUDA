#include "../include/dep.h"

__global__ void gpu_print(void){
    printf("Hello from thread [%d, %d]\n", threadIdx.x, blockIdx.x);
}

int main(int argc, char** argv)
{
    GpuTime time();
    // parse data from the data file -> create a parser
    // alg
    // external check
    // benckmarking (how)

//    printf("Hello [from host], a w/ dtype  = %d\n", a);


    gpu_print<<<2, 1>>>();
    cudaDeviceSynchronize();
    return 0;
}