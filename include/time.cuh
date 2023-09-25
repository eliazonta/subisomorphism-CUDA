#ifndef GPU_TIME_H
#define GPU_TIME_H

struct GpuTime
{
    cudaEvent_t start, stop;

    GpuTime();
    ~GpuTime();

    void start();
    void stop();
    double elapsed();
};

#endif // GPU_TIME_H