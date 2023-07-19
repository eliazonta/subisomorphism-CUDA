#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <cuda_runtime.h>
#include <math.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include "../include/GPU_TIME.h"
#include "../include/parser.h"

/*
    IDEA:
        - CSR parser 
        - Sequential alg on CSR vectors
        - design a paralell GPU alg
        - benchmark and tests
*/
__global__ 
void gpu_print(void){
    printf("Hello from thread [%d, %d]\n", threadIdx.x, blockIdx.x);
}

int main(int argc, char** argv)
{ 
    fprintf(stdout, "===============================================\n");
    fprintf(stdout, "********* Parallel Graph Isomorphism  *********\n");
    fprintf(stdout, "-----------------------------------------------\n");
    fprintf(stdout, "***** Authors: Zonta Elia, Tessari Michele ****\n");
    fprintf(stdout, "-----------------------------------------------\n");
    fprintf(stdout, "===============================================\n");
    if (argc != 5) {
        fprintf(stdout, "Usage : \n");
        exit(-1);
    }  
    
    const char *filename = argv[2];
    int *row_ptr, *col_ind, num_rows, num_cols, num_vals, numSMs;
    float* values;
    
    read_matrix(&row_ptr, &col_ind, &values, filename, &num_rows, &num_cols, &num_vals);



    return 0;
}