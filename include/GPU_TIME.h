#ifndef __GPU_TIME_H__
#define __GPU_TIME_H__

struct GpuTime
{
    cudaEvent_t start;
    cudaEvent_t stop;

    GpuTimer()
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
    }

    ~GpuTimer()
    {
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }

    void start()
    {
        cudaEventRecord(start, 0);
    }

    void stop()
    {
        cudaEventRecord(stop, 0);
    }

    float elapsed()
    {
        float elapsed;
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&elapsed, start, stop);
        return elapsed;
    }
};

#endif