#pragma once
#ifndef __utils__
#define __utils__
#include <chrono>
#include <cmath>
#include <mutex>
#include <iostream>

static int BLK_SIZE = 1024;
static int dsize = 1;
static int GRID_SIZE = (dsize+BLK_SIZE-1)/BLK_SIZE;

///////////////////////////////////////////////////////////////
// CUDA error check
//////////////////////////////////////////////////////////////
static void cuda_check_status(cudaError_t status);

//////////////////////////////////////////////////////////////
// memory allocation
//////////////////////////////////////////////////////////////
template <typename T>
T* malloc_device(size_t n);

template <typename T>
T* malloc_managed(size_t n, T value = T());

template <typename T>
T* malloc_pinned(size_t n, T value = T());


///////////////////////////////////////////////////////////////////
// CUDA memory copy
//////////////////////////////////////////////////////////////////
template <typename T>
void copy_to_device(T* from, T* to, size_t n);


template <typename T>
void copy_to_host(T* from, T* to, size_t n);


template <typename T>
void copy_to_device_async(const T* from, T* to, size_t n, cudaStream_t stream = NULL);


template <typename T>
void copy_to_host_async(const T* from, T* to, size_t n, cudaStream_t stream = NULL);


///////////////////////////////////////////////////////////////////
// others
//////////////////////////////////////////////////////////////////
static size_t read_arg(int argc, char** argv, size_t index, int default_value);


template <typename T>
T* malloc_host(size_t n, T value = T());

//aliases
using clock_type = std::chrono::high_resolution_clock;
using duration_type = std::chrono::duration<double>;

static  double get_time();


#endif // eof