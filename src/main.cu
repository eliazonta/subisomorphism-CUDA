#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
// #include "../include/iso.h"
#include "../include/utils.cuh"
#include "../include/parser.h"

// #define USE_STRUCT
__device__
void isomorphism(struct COOGraph g1, struct COOGraph g2){

}

__global__ 
void subgraphIsomorphismKernel(int* targetGraph, int* patternGraph, int* mapping, bool* found, int patternVertices, int targetVertices) 
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid >= patternVertices) {
        return;  // Not enough threads for all pattern vertices
    }

    if (*found) {
        return;  // Solution already found by another thread
    }

    // Implement the backtracking logic for this thread
    // Explore different branches of the search space and update the mapping

    // If a valid solution is found, set *found = true
}

int main(int argc, char** argv) {
    char file[] = "../toy/g2.mtx";

    #ifdef USE_STRUCT
    struct COOGraph g1, g2;
    struct COOGraph d_g1, d_g2;
    readCOO_struct(file, &g1);
    readCOO_struct(file, &g2);
    #endif

    #ifdef NO_STRUCT
        int num_rows, num_cols, nnz;
        int* rowidx, colidx;
        double* weights;
    #endif
    // Initialize and allocate GPU memory for targetGraph, patternGraph, mapping, and other necessary data
    
    // copy of stack data for g1
    d_g1.nnz = g1.nnz;
    d_g1.num_rows = g1.num_rows;
    d_g1.num_cols = g1.num_cols;
    // d_g1.rowidx = malloc_device<int>(d_g1.num_rows + 1);
    // d_g1.colidx = malloc_device<int>(d_g1.num_cols + 1);

    // copy of stack data for g2
    d_g2.nnz = g2.nnz;
    d_g2.num_rows = g2.num_rows;
    d_g2.num_cols = g2.num_cols;
    // d_g2.rowidx = malloc_device<int>(d_g2.num_rows + 1);
    // d_g2.colidx = malloc_device<int>(d_g2.num_cols + 1);

    
    auto s = get_time();
    
    // copy to device for g1
    // copy_to_device(d_g1.rowidx, g1.rowidx, (g1.num_rows + 1) * sizeof(int));
    // copy_to_device(d_g1.colidx, g1.colidx, (g1.num_cols + 1) * sizeof(int));
    thrust::device_vector<int> d_g1.rowidx = g1.rowidx;
    thrust::device_vector<int> d_g1.colidx = g1.colidx;
    // copy to device for g2
    // copy_to_device(d_g2.rowidx, g2.rowidx, (g2.num_rows + 1) * sizeof(int));
    // copy_to_device(d_g2.colidx, g2.colidx, (g2.num_cols + 1) * sizeof(int));
    thrust::device_vector<int> d_g2.rowidx = g2.rowidx;
    thrust::device_vector<int> d_g2.colidx = g2.colidx;
    
    // elapsed
    auto time_H2D = get_time() - s;

    // Launch the CUDA kernel with appropriate grid and block sizes
    // Call subgraphIsomorphismKernel<<<gridSize, blockSize>>>(targetGraph, patternGraph, mapping, found, patternVertices, targetVertices);

    // Wait for the kernel to finish

    // Copy the results (e.g., valid mappings) from GPU to CPU
    

    // Free GPU memory and clean up
    cudaFree(d_g1.rowidx);
    cudaFree(d_g1.colidx);

    cudaFree(d_g2.rowidx);
    cudaFree(d_g2.colidx);

    return 0;
}
