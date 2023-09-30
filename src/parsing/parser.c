#include "parser.h"
#include "../graph/graph.h"
#define DEBUG

// From edgelist to COO
// Further updates will target CSR format 

void readCOO(const char* filepath, int num_edges, int* rowidx, int* colidx, dtype* weights) 
{
    int source, target;
    dtype weight; 
    FILE* file = fopen(filepath, "r");     
    if (file == NULL) {
        fprintf(stderr, "Error opening file");
        assert(file == NULL);
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
    num_edges = val;

    // Allocate memory for COO arrays
    rowidx = (int *)malloc(val * sizeof(int));
    colidx = (int *)malloc(val * sizeof(int));
    weights = (dtype *)malloc(val * sizeof(dtype));

    if (rowidx == NULL || colidx == NULL || weights == NULL) {
        fprintf(stderr, "Memory allocation error");
        assert(rowidx == NULL || colidx == NULL || weights == NULL);
    }

    for(size_t i = 0; i < val; ++i){
        fscanf(file, "%d %d %lf", &source, &target, &weight);
        // Store edge information in COO arrays
        if(weight != 0.0){
            rowidx[i] = source;
            colidx[i] = target;
            weights[i] = weight; //  1.0 if no weights
        } 
    }
    int num_vertex = getVertexNum(&weights, val);

    fclose(file);

    // DEBUG
    #ifdef DEBUG
    fprintf(stdout, "COO Arrays:\n");
    fprintf(stdout, "NUM vertex [%d] \t NUM edges [%d]\n", num_vertex, num_edges);
    fprintf(stdout, "\nrow idx:\n");
    for (size_t i = 0; i < val; ++i) {
        fprintf(stdout, "%d\t", rowidx[i]);
    }
    fprintf(stdout, "\n\ncol idx:\n");
    for (size_t i = 0; i < val; ++i) {
        printf("%d\t", colidx[i]);
    }
    fprintf(stdout, "\n\nweights:\n");
    for (size_t i = 0; i < val; ++i) {
        fprintf(stdout, "%.2lf\t", weights[i]);
    }
    fprintf(stdout, "\n\n");
    #endif
}

void readCOO_struct(const char* filepath, struct COOGraph* g) 
{
    int source, target;
    dtype weight; // Assuming the weight is a float; change to int if necessary
    FILE* file = fopen(filepath, "r");     
    if (file == NULL) {
        fprintf(stderr, "Error opening file");
        assert(file == NULL);
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
        if(weight != 0.0){
            g->rowidx[i] = source;
            g->colidx[i] = target;
            g->weights[i] = weight; // Change to 1.0 if no weights are provided
        }
    }
    g->num_vertices = getVertexNum(&g->weights, g->num_edges);
    fclose(file);

    // DEBUG
    #ifdef DEBUG
    fprintf(stdout, "COO Arrays:\n");
    fprintf(stdout, "NUM vertex [%d] \t NUM edges [%d]\n", g->num_vertices, g->num_edges);
    fprintf(stdout, "\nrow idx:\n");
    for (size_t i = 0; i < g->num_edges; ++i) 
    {
        fprintf(stdout, "%d\t", g->rowidx[i]);
    }
    printf("\n\ncol idx:\n");
    for (size_t i = 0; i < g->num_edges; ++i) 
    {
        fprintf(stdout, "%d\t", g->colidx[i]);
    }
    printf("\n\nweights:\n");
    for (size_t i = 0; i < g->num_edges; ++i) 
    {
        fprintf(stdout, "%.2lf\t", g->weights[i]);
    }
    fprintf(stdout, "\n\n");
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

void edgeListToCSR(const char* filepath, struct CSRGraph* g) 
{
    int num_rows, num_cols, nnz;
    int num_vertices, num_edges; // TBD
    FILE* file = fopen(filepath, "r");     
    if (file == NULL) {
        fprintf(stderr, "Error opening file");
        assert(file==NULL);
    }
    fscanf(file, "%d %d %d", &num_rows, &num_cols, &nnz);
    g->num_vertices = nnz;
    // graph->num_edges = num_edges;
    g->rowptr = (int*)malloc((num_rows + 1) * sizeof(int));
    g->colidx = (int*)malloc((nnz + 1) * sizeof(int));

    // init
    memset(g->rowptr, 0, sizeof(int));

    // Read edge data and count neighbors for each vertex
    for (int i = 0; i < g->num_edges; ++i) 
    {
        int source, target;
        fscanf(file, "%d %d %lf", &source, &target);
        g->rowptr[source + 1]++;
        g->rowptr[target + 1]++;
    }

    // Calculate row_ptr vals (cumulative sum)
    for (int i = 1; i <= g->num_vertices; ++i) 
    {
        g->rowptr[i] += g->rowptr[i - 1];
    }

    // Read edge data again and fill col_idx
    rewind(file); // Reset file pointer to the beginning
    fscanf(file, "%d %d", &num_vertices, &num_edges); // Skip the first line
    for (int i = 0; i < num_edges; ++i) 
    {
        int source, target;
        fscanf(file, "%d %d", &source, &target);
        g->colidx[g->rowptr[source]] = target;
        g->colidx[g->rowptr[target]] = source;
        g->rowptr[source]++;
        g->rowptr[target]++;
    }

    // Reset row_ptr values to their original state
    for (int i = num_vertices; i > 0; --i) 
    {
        g->rowptr[i] = g->rowptr[i - 1];
    }
    g->rowptr[0] = 0;
}


void freeCSR_struct(struct CSRGraph* g) 
{
    if (g != NULL) {
        free(g->rowptr);
        free(g->colidx);
        free(g->weights);
        free(g);
    }
}