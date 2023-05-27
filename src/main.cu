#include "../include/dep.h"

__global__ 
void gpu_print(void){
    printf("Hello from thread [%d, %d]\n", threadIdx.x, blockIdx.x);
}
__global__ 
void VecAdd(float* a, float* b, float* c, int N){
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i < N){
        c[i] = a[i] + b[i];
    }
}

int main(int argc, char** argv)
{
    GpuTime time();
    // parse data from the data file -> create a parser
    // CSR ? COO ? what's better ? 
    // alg {pain}
    // external check {py / networkx}
    // benckmarking [gpu timer content is sufficient ?]

    int N = 5;
    size_t size = sizeof(float) * N;

    float* a = (float*)malloc(size);
    float* b = (float*)malloc(size);
    float* c = (float*)malloc(size);

    for(int i = 0; i < N; ++i){
        *(a + i) = (float)i;
        *(b + i) = (float)i * 2;
    }

    float* d_a;cudaMalloc(&d_a, size);
    float* d_b;cudaMalloc(&d_b, size);
    float* d_c;cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1)/ threadsPerBlock;
    VecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, N);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("A : ");
    for (int i = 0; i < N; ++i)
    {
        printf("%f - ", *(a + i));
    }
    printf("\n");
    printf("B : ");
    for (int i = 0; i < N; ++i)
    {
        printf("%f - ", *(b + i));
    }
    printf("\n");
    
    printf("C : ");
    for (int i = 0; i < N; ++i)
    {
        printf("%f - ", *(c + i));
    }
    printf("\n");
    
   cudaFree(d_a);
   cudaFree(d_b);
   cudaFree(d_c);
    free(a);free(b);free(c);

    return 0;
}