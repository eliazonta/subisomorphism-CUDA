#include "../include/time.cuh"
// #include <cuda_runtime.h>

struct GpuTime
{
    cudaEvent_t sstart, sstop;

    GpuTime()
    {
        cudaEventCreate(&sstart);
        cudaEventCreate(&sstop);
    }

    ~GpuTime()
    {
        cudaEventDestroy(sstart);
        cudaEventDestroy(sstop);
    }

    void start(int stream = 0)
    {
        cudaEventRecord(sstart, stream);
    }

    void stop(int stream = 0)
    {
        cudaEventRecord(sstop, stream);
    }

    double elapsed()
    {
        double elapsed;
        cudaEventSynchronize(sstop);
        cudaEventElapsedTime(&elapsed, sstart, sstop);
        return elapsed;
    }
};