#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{ 
    fprintf(stdout, "===============================================\n");
    fprintf(stdout, "******** Sequential Graph Isomorphism  ********\n");
    fprintf(stdout, "-----------------------------------------------\n");
    fprintf(stdout, "***** Authors: Zonta Elia, Tessari Michele ****\n");
    fprintf(stdout, "-----------------------------------------------\n");
    fprintf(stdout, "===============================================\n");
    
    if (argc != 4) {
        fprintf(stdout, "Usage : \n <./bin/SGI-SEQ> <num of iterations> <print mode [1 default, 2 view data info]> <file path>\n");
        exit(-1);
    }  
    
    const char *filename = argv[2];
    int *row_ptr, *col_ind, num_rows, num_cols, num_vals, numSMs;
    float* values;
    read_matrix(&row_ptr, &col_ind, &values, filename, &num_rows, &num_cols, &num_vals);
    return 0;
}