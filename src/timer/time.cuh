#ifndef __time__
#define __time__

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