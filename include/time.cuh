#ifndef GPU_TIME_H
#define GPU_TIME_H

struct GpuTime
{
    cudaEvent_t sstart, sstop;

    GpuTime();
    ~GpuTime();

    void start(int stream = 0);
    void stop(int stream = 0);
    double elapsed();
};

#endif // GPU_TIME_H