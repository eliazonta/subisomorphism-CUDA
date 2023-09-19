#ifndef __parser_h__
#define __parser_h__

#include <stdio.h>
#include <stdlib.h>

struct COOGraph {
    int num_rows;
    int num_cols;
    int nnz;
    int* rowidx;
    int* colidx;
    double* vals;
};

void readCOO(char filepath[], struct COOGraph* g) {
    int source, target;
    double weight; // Assuming the weight is a float; change to int if necessary
    FILE* file = fopen(filepath, "r");     
    if (file == NULL) {
        perror("Error opening file");
        // return 1;
    }
    // Matrix Market header skip
    // while(fgetc(file) == '%')
    // {
    //     char c;
    //     while((c = fgetc(file)) != '\n');
    // }

    // Count the number of edges in the file
    fscanf(file, "%d %d %d", &g->num_rows, &g->num_cols, &g->nnz);
    printf("nr, nc, nnz : %d %d %d\n", g->num_rows, g->num_cols, g->nnz);

    // Allocate memory for COO arrays
    g->rowidx = (int *)malloc(++g->num_rows * sizeof(int));
    g->colidx = (int *)malloc(++g->num_cols * sizeof(int));
    g->vals = (double *)malloc(g->nnz * sizeof(double));

    if (g->rowidx == NULL || g->colidx == NULL || g->vals == NULL) {
        perror("Memory allocation error");
        // return 1;
    }

    for(size_t i = 0; i < g->nnz; ++i){
        fscanf(file, "%d %d %lf", &source, &target, &weight);
        // Store edge information in COO arrays
        g->rowidx[i] = source;
        g->colidx[i] = target;
        g->vals[i] = weight; // Change to 1.0 if no weights are provided
    }

    fclose(file);

    // Print the COO arrays (for demonstration)
    printf("COO Arrays:\n");
    printf("row idx:\n");
    for (size_t i = 0; i < g->num_rows; i++) {
        printf("%d ", g->rowidx[i]);
    }
    printf("\ncol idx:\n");
    for (size_t i = 0; i < g->num_cols; i++) {
        printf("%d ", g->colidx[i]);
    }
    printf("\nvals:\n");
    for (size_t i = 0; i < g->nnz; i++) {
        printf("%.2lf ", g->vals[i]);
    }
    printf("\n\n");
}

#endif