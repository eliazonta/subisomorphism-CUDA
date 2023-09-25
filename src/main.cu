#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
// #include "../include/iso.h"
#include "../include/utils.cuh"
#include "../include/parser.h"

// #define USE_STRUCT

// idea
// kernel for subgraph isomorphism (backtracking)
// device func called by the kernel for isomorphism on a restriction of the graph 

__device__
void isomorphism(int* g1_num_rows, int* g1_num_cols, int* g1_nnz, int* g1_rowidx, int* g1_colidx, int* g1_weights){

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

    #ifndef USE_STRUCT
        // g1
        int g1_num_rows, g1_num_cols, g1_nnz;
        int* g1_rowidx, g1_colidx, g1_d_row_idx, g1_d_rowidx, g1_d_colidx;
        double* g1_weights, g1_d_weights;

        // g1
        int g2_num_rows, g2_num_cols, g2_nnz;
        int* g2_rowidx, g2_colidx, g2_d_row_idx, g2_d_rowidx, g2_d_colidx;
        double* g2_weights, g2_d_weights;

        readCOO(file, &g1_num_rows, &g1_num_cols, &g1_nnz, &g1_rowidx, &g1_colidx, &g1_weights);
        readCOO(file, &g2_num_rows, &g2_num_cols, &g2_nnz, &g2_rowidx, &g2_colidx, &g2_weights);
    #endif
    // Initialize and allocate GPU memory for targetGraph, patternGraph, mapping, and other necessary data
    #ifdef USE_STRUCT
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
    #endif

    
    auto s = get_time();

    #ifdef USE_STRUCT
    // copy to device for g1
    copy_to_device(d_g1.rowidx, g1.rowidx, (g1.num_rows + 1) * sizeof(int));
    copy_to_device(d_g1.colidx, g1.colidx, (g1.num_cols + 1) * sizeof(int));
    // thrust::device_vector<int> d_g1.rowidx = g1.rowidx; // has to be fixed, even just for fun :)
    // thrust::device_vector<int> d_g1.colidx = g1.colidx;
    // copy to device for g2
    copy_to_device(d_g2.rowidx, g2.rowidx, (g2.num_rows + 1) * sizeof(int));
    copy_to_device(d_g2.colidx, g2.colidx, (g2.num_cols + 1) * sizeof(int));
    // thrust::device_vector<int> d_g2.rowidx = g2.rowidx;
    // thrust::device_vector<int> d_g2.colidx = g2.colidx;
    #endif

    #ifndef USE_STRUCT
    // copy to device for g1
    thrust::device_vector<int> g1_d_rowidx = g1_rowidx;
    thrust::device_vector<int> g1_d_colidx = g1_colidx;
    thrust::device_vector<double> g1_d_weights = g1_weights;

    // copy to device for g2
    thrust::device_vector<int> g2_d_rowidx = g2_rowidx;
    thrust::device_vector<int> g2_d_colidx = g2_colidx;
    thrust::device_vector<double> g2_d_weights = g2_weights;
        
    #endif
    // elapsed
    auto time_H2D = get_time() - s;

    // Launch the CUDA kernel with appropriate grid and block sizes
    // Call subgraphIsomorphismKernel<<<gridSize, blockSize>>>(targetGraph, patternGraph, mapping, found, patternVertices, targetVertices);

    // Wait for the kernel to finish

    // Copy the results (e.g., valid mappings) from GPU to CPU
    
    #ifdef USE_STRUCT
    // Free GPU memory and clean up
    cudaFree(d_g1.rowidx);
    cudaFree(d_g1.colidx);

    cudaFree(d_g2.rowidx);
    cudaFree(d_g2.colidx);
    #endif

    #ifndef USE_STRUCT
    cudaFree(g1_d_rowidx);
    cudaFree(g1_d_colidx);

    cudaFree(g2_d_rowidx);
    cudaFree(g2_d_colidx);
    #endif

    return 0;
}
