#include "../include/iso.h"
#inclide "../include/utils.cuh"

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

int main() {
    char file[] = "../toy/g2.mtx";
    struct COOGraph g1, g2;
    struct COOGraph d_g1, d_g2;
    readCOO(file, &g1);
    readCOO(file, &g2);
    // Initialize and allocate GPU memory for targetGraph, patternGraph, mapping, and other necessary data
    d_g1.num_vertices = g1.num_vertices;
    d_g1.num_edges = g1.num_edges;
    d_g1.row_ptr = malloc_device<int>();
    d_g1.col_idx = malloc_device<int>();

    d_g2.num_vertices = g2.num_vertices;
    d_g2.num_edges = g2.num_edges;
    d_g2.row_ptr = malloc_device<int>();
    d_g2.col_idx = malloc_device<int>();
    // Launch the CUDA kernel with appropriate grid and block sizes
    // Call subgraphIsomorphismKernel<<<gridSize, blockSize>>>(targetGraph, patternGraph, mapping, found, patternVertices, targetVertices);

    // Wait for the kernel to finish

    // Copy the results (e.g., valid mappings) from GPU to CPU
    

    // Free GPU memory and clean up
    cudaFree(d_g1.row_ptr);
    cudaFree(d_g1.col_idx);

    cudaFree(d_g2.row_ptr);
    cudaFree(d_g2.col_idx);

    return 0;
}
