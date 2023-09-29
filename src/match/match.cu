
#include "match.cuh"

// gpu warmup needs to be done otherwise first malloc will be slower
void initGPU(int dev)
{
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);
    if (deviceCount == 0) {
        fprintf(stderr, "error: no devices supporting CUDA.\n");
        exit(EXIT_FAILURE);
    }
    cudaSetDevice(dev);
    cudaDeviceProp devProps;
    if (cudaGetDeviceProperties(&devProps, dev) == 0)
    {
        printf("Using device %d:\n", dev);
        printf("%s; global mem: %luB; compute v%d.%d; clock: %d kHz; shared mem: %dB; block threads: %d; SM count: %d\n",
               devProps.name, devProps.totalGlobalMem, 
               (int)devProps.major, (int)devProps.minor, 
               (int)devProps.clockRate,
			   devProps.sharedMemPerBlock, devProps.maxThreadsPerBlock, devProps.multiProcessorCount);
    }
	fprintf(stdout, "on GPU!\n");
	// GPU init
	int* warmup = NULL;
	cudaMalloc(&warmup, sizeof(int));
	cudaFree(warmup);
	fprintf(stdout, "GPU warmup done\n");
    size_t size = 0x7fffffff;   //ulong , appr 2G
    size *= 4;
	cudaDeviceGetLimit(&size, cudaLimitMallocHeapSize);
	fprintf(stdout, "check heap limit: %ul\n", size);
}




DEVICE_INTRINSIC_QUALIFIERS
unsigned int
smid()
{
  unsigned int r;
  asm("mov.u32 %0, %%smid;" : "=r"(r));
  return r;
}

DEVICE_INTRINSIC_QUALIFIERS
unsigned int
nsmid()
{
#if (__CUDA_ARCH__ >= 200)
  unsigned int r;
  asm("mov.u32 %0, %%nsmid;" : "=r"(r));
  return r;
#else
  return 30;
#endif
}

void exclusive_sum(unsigned* d_array, unsigned size)
{
    // Determine temporary device storage requirements
    void* d_temp_storage = NULL; //must be set to distinguish two phase
    size_t temp_storage_bytes = 0;
    cub::DeviceScan::ExclusiveSum(d_temp_storage, temp_storage_bytes, d_array, d_array, size);
    // Allocate temporary storage
    cudaMalloc(&d_temp_storage, temp_storage_bytes);
    // Run exclusive prefix sum
    cub::DeviceScan::ExclusiveSum(d_temp_storage, temp_storage_bytes, d_array, d_array, size);
    cudaFree(d_temp_storage);
}