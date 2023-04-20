#include <stdlib.h>
#include <stdio.h>

__global__ void kernel(void){
    printf("hello ! [from device/ thread]\n");
}

__global__ void gpu_print(void){
    printf("Hello from thread [%d, %d]\n", threadIdx.x, blockIdx.x);
}
int main(void){
	kernel<<<1, 1>>>();
	printf("Hello World! [from host]\n");

    gpu_print<<<2, 1>>>();
    cudaDeviceSyncronize();
	return 0;
}
