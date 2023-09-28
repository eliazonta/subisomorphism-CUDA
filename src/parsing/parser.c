#include "parser.h"

#define DEBUG

// From edgelist to COO
// Further updates will target CSR format 

void readCOO(const char* filepath, int num_edges, int* rowidx, int* colidx, dtype* weights) 
{
    int source, target;
    dtype weight; 
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
    int row, col, val;
    // Count the number of edges in the file
    fscanf(file, "%d %d %d", &row, &col, &val);
    printf("nr, nc, nnz : %d %d %d\n", row, col, val);

    // Allocate memory for COO arrays
    rowidx = (int *)malloc(val * sizeof(int));
    colidx = (int *)malloc(val * sizeof(int));
    weights = (dtype *)malloc(val * sizeof(dtype));

    if (rowidx == NULL || colidx == NULL || weights == NULL) {
        perror("Memory allocation error");
        // return 1;
    }

    for(size_t i = 0; i < val; ++i){
        fscanf(file, "%d %d %lf", &source, &target, &weight);
        // Store edge information in COO arrays
        rowidx[i] = source;
        colidx[i] = target;
        weights[i] = weight; //  1.0 if no weights 
    }

    fclose(file);

    // DEBUG
    #ifdef DEBUG
    printf("COO Arrays:\n");
    printf("row idx:\n");
    for (size_t i = 0; i < val; ++i) {
        printf("%d\t", rowidx[i]);
    }
    printf("\ncol idx:\n");
    for (size_t i = 0; i < val; ++i) {
        printf("%d\t", colidx[i]);
    }
    printf("\nweights:\n");
    for (size_t i = 0; i < val; ++i) {
        printf("%.2lf\t", weights[i]);
    }
    printf("\n\n");
    #endif
}

void readCOO_struct(const char* filepath, struct COOGraph* g) 
{
    int source, target;
    dtype weight; // Assuming the weight is a float; change to int if necessary
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
    int row, col;
    // Count the number of edges in the file
    fscanf(file, "%d %d %d", &row, &col, &g->num_edges);
    printf("nr, nc, nnz : %d %d %d\n", row, col, g->num_edges);

    // Allocate memory for COO arrays
    g->rowidx = (int *)malloc(g->num_edges * sizeof(int));
    g->colidx = (int *)malloc(g->num_edges * sizeof(int));
    g->weights = (dtype *)malloc(g->num_edges * sizeof(dtype));

    if (g->rowidx == NULL || g->colidx == NULL || g->weights == NULL) {
        perror("Memory allocation error");
        // return 1;
    }

    for(size_t i = 0; i < g->num_edges; ++i){
        fscanf(file, "%d %d %lf", &source, &target, &weight);
        // Store edge information in COO arrays
        g->rowidx[i] = source;
        g->colidx[i] = target;
        g->weights[i] = weight; // Change to 1.0 if no weights are provided
    }

    fclose(file);

    // DEBUG
    #ifdef DEBUG
    printf("COO Arrays:\n");
    printf("row idx:\n");
    for (size_t i = 0; i < g->num_edges; ++i) 
    {
        printf("%d\t", g->rowidx[i]);
    }
    printf("\ncol idx:\n");
    for (size_t i = 0; i < g->num_edges; ++i) 
    {
        printf("%d\t", g->colidx[i]);
    }
    printf("\nweights:\n");
    for (size_t i = 0; i < g->num_edges; ++i) 
    {
        printf("%.2lf\t", g->weights[i]);
    }
    printf("\n\n");
    #endif
}

void freeCOO_struct(struct COOGraph* g) 
{
    if (g != NULL) 
    {
        free(g->rowidx);
        free(g->colidx);
        free(g->weights);
        free(g);
    }
}

void freeCSR_struct(struct CSRGraph* g) {
    if (g != NULL) {
        free(g->rowptr);
        free(g->colidx);
        free(g->weights);
        free(g);
    }
}