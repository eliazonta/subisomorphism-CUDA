#include <stdio.h>
#include <stdlib.h>
#include <cublas_v2.h> // -lcublas
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include "utils/utils.cuh"
#include "parsing/parser.h"
#include "timer/time.cuh"

// thrust would be interesting asf but getting some allocation problems
// 
// #define USE_STRUCT
// #define THRUST

// idea
// kernel for subgraph isomorphism (backtracking)
// device func called by the kernel for isomorphism on a restriction of the graph 


#define BLK_SIZE 256 
#define DBG_CHECK { printf("DBG_CHECK: file %s at line %d\n", __FILE__, __LINE__ ); }
#define DEBUG

// __device__
// void isomorphism(int* g1_num_rows, int* g1_num_cols, int* g1_nnz, int* g1_rowidx, int* g1_colidx, int* g1_weights)
// {

// }

// __global__ 
// void subgraphIsomorphismKernel(struct* COOGraph g1, struct* COOGraph g2, int* mapping, bool* found, int patternVertices, int targetVertices) 
// {
//     unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;

//     if (tid >= patternVertices) {
//         return;  // not enough threads for all pattern vertices
//     }

//     if (*found) {
//         return;  // solution already found by another thread
//     }

//     // implement the backtracking logic for this thread!!
//     // explore different branches of the search space and update the mapping

//     // if a valid solution is found, set *found = true
// }

int main(int argc, char** argv) {
    dim3 block_size(BLK_SIZE, 1, 1);
    dim3 grid_size(1, 1, 1);
    char* file = "../toy/g2.mtx";

    #ifdef USE_STRUCT
    struct COOGraph g1, g2;
    struct COOGraph d_g1, d_g2;
    readCOO_struct(file, &g1);
    readCOO_struct(file, &g2);
    #endif

    #ifndef USE_STRUCT
        int g1_num_edges, g2_num_edges;
        // g1 - noTHRUST
        #ifndef THRUST
        int* g1_rowidx, g1_colidx, d_g1_rowidx, d_g1_colidx;
        dtype* g1_weights, d_g1_weights;
        #endif

        // g1 - THRUST 
        #ifdef THRUST
        thrust::host_vector<int> g1_rowidx, g1_colidx;
        thrust::host_vector<dtype> g1_weights;
        #endif


        // g2 - noTHRUST
        #ifndef THRUST
        int* g2_rowidx, g2_colidx, d_g2_rowidx, d_g2_colidx;
        dtype* g2_weights, d_g2_weights;
        #endif

        // g2 - THRUST 
        #ifdef THRUST
        thrust::host_vector<int> g2_rowidx, g2_colidx;
        thrust::host_vector<dtype> g2_weights;
        #endif

        // readCOO(file, g1_num_edges, &g1_rowidx, &g1_colidx, &g1_weights);
        // readCOO(file, g2_num_edges, &g2_rowidx, &g2_colidx, &g2_weights);
    #endif

    
    // #ifdef USE_STRUCT //fix
    // readCOO_struct("../../toy/g2.mtx", &g1);
    // readCOO_struct("../../toy/g2.mtx", &g2);
    // // copy of stack data for g1
    // d_g1.num_edges = g1.num_edges;
    // d_g1.num_rows = g1.num_rows;
    // d_g1.num_cols = g1.num_cols;
    // // d_g1.rowidx = malloc_device<int>(d_g1.num_rows + 1);
    // // d_g1.colidx = malloc_device<int>(d_g1.num_cols + 1);

    // // copy of stack data for g2
    // d_g2.nnz = g2.nnz;
    // d_g2.num_rows = g2.num_rows;
    // d_g2.num_cols = g2.num_cols;
    // // d_g2.rowidx = malloc_device<int>(d_g2.num_rows + 1);
    // // d_g2.colidx = malloc_device<int>(d_g2.num_cols + 1);
    // #endif

    
    // GpuTime time_H2D;
    // time_H2D.start();

    // #ifdef USE_STRUCT
    // // copy to device for g1
    // copy_to_device(d_g1.rowidx, g1.rowidx, (g1.num_edges + 1) * sizeof(int));
    // copy_to_device(d_g1.colidx, g1.colidx, (g1.num_edges + 1) * sizeof(int));
    // // thrust::device_vector<int> d_g1.rowidx = g1.rowidx; // has to be fixed, even just for fun :)
    // // thrust::device_vector<int> d_g1.colidx = g1.colidx;

    // // copy to device for g2
    // copy_to_device(d_g2.rowidx, g2.rowidx, (g2.num_edges + 1) * sizeof(int));
    // copy_to_device(d_g2.colidx, g2.colidx, (g2.num_edges + 1) * sizeof(int));
    // // thrust::device_vector<int> d_g2.rowidx = g2.rowidx;
    // // thrust::device_vector<int> d_g2.colidx = g2.colidx;
    // #endif

    // #ifndef USE_STRUCT
    // // copy to device for g1
    // GpuTime timeH2D_g1;
    // timeH2D_g1.start();
    // thrust::device_vector<int> d_g1_rowidx = g1_rowidx;
    // thrust::device_vector<int> d_g1_colidx = g1_colidx;
    // thrust::device_vector<dtype> d_g1_weights = g1_weights;
    // timeH2D_g1.stop();
    // printf("G1 H2D elapsed time: %f ms", time_H2D_g1.elapsed());
    
    // // copy to device for g2
    // GpuTime timeH2D_g2;
    // timeH2D_g2.start();
    // thrust::device_vector<int> d_g2_rowidx = g2_rowidx;
    // thrust::device_vector<int> d_g2_colidx = g2_colidx;
    // thrust::device_vector<dtype> d_g2_weights = g2_weights;
    // timeH2D_g2.stop();
    // printf("G2 H2D elapsed time: %f ms", time_H2D_g2.elapsed());
    // #endif
    // // elapsed
    // timeH2D.stop();
    // printf("Complete H2D elapsed time: %f ms", time_H2D.elapsed());

    // // CUDA kernel 
    // // Call subgraphIsomorphismKernel<<<gridSize, blockSize>>>(targetGraph, patternGraph, mapping, found, patternVertices, targetVertices);
    // // coolSubgraphIsomorhismKernel<<<grid_size, block_size>>>(targetG, patternG, mapping, ....);
    
    // // Wait for the kernel to finish
    // // cuda_check_status(cudaDeviceSyncronize());

    // // Copy the results (e.g., valid mappings) from GPU to CPU
    // #ifdef USE_STRUCT
    // #endif

    // #ifndef USE_STRUCT
    // copy_to_host(d_g1_rowidx, g1_rowidx);
    // copy_to_host(d_g1_colidx, g1_colidx);
    // copy_to_host(d_g1_weights, g1_weights);

    // copy_to_host(d_g2_rowidx, g2_rowidx);
    // copy_to_host(d_g2_colidx, g2_colidx);
    // copy_to_host(d_g2_weights, g2_weights);

    // #endif

    // #ifdef USE_STRUCT
    // // host
    // freeCOO_struct(&g1);
    // freeCOO_struct(&g2);
    
    // // device
    // cudaFree(d_g1.rowidx);
    // cudaFree(d_g1.colidx);
    // cudaFree(d_g1.weights);

    // cudaFree(d_g2.rowidx);
    // cudaFree(d_g2.colidx);
    // cudaFree(d_g2.weights);
    // #endif

    // #ifndef USE_STRUCT
    // // host
    // free(g1_rowidx);
    // free(g1_colidx);
    // free(g1_weights);

    // free(g2_rowidx);
    // free(g2_colidx);
    // free(g2_weights);

    // // device
    // cudaFree(d_g1_rowidx);
    // cudaFree(d_g1_colidx);
    // cudaFree(d_g1_weights);

    // cudaFree(d_g2_rowidx);
    // cudaFree(d_g2_colidx);
    // cudaFree(d_g2_weights);
    // #endif

    return 0;
}
