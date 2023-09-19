#include <stdio.h>
#include <stdlib.h>

// Structure to represent a graph in CSR format
struct CSRGraph {
    int num_vertices;
    int num_edges;
    int* row_ptr;
    int* col_idx;
};

// Function to convert an edge list to CSR format
void edgeListToCSR(FILE* file, struct CSRGraph* graph) {
    int num_rows, num_cols, nnz;

    // Read the number of vertices and edges from the file
    fscanf(file, "%d %d %d", &num_rows, &num_cols, &nnz);
    graph->num_vertices = nnz;
    // graph->num_edges = num_edges;

    // Allocate memory for CSR arrays
    graph->row_ptr = (int*)malloc((num_rows + 1) * sizeof(int));
    graph->col_idx = (int*)malloc((nnz + 1) * sizeof(int));

    // Initialize the row_ptr array with zeros
    for (int i = 0; i < num_rows; ++i) {
        graph->row_ptr[i] = 0;
    }

    // Read edge data and count neighbors for each vertex
    for (int i = 0; i < num_edges; i++) {
        int source, target;
        fscanf(file, "%d %d %lf", &source, &target);
        graph->row_ptr[source + 1]++;
        graph->row_ptr[target + 1]++;
    }

    // Calculate row_ptr values (cumulative sum)
    for (int i = 1; i <= num_vertices; i++) {
        graph->row_ptr[i] += graph->row_ptr[i - 1];
    }

    // Read edge data again and fill col_idx
    rewind(file); // Reset file pointer to the beginning
    fscanf(file, "%d %d", &num_vertices, &num_edges); // Skip the first line
    for (int i = 0; i < num_edges; i++) {
        int source, target;
        fscanf(file, "%d %d", &source, &target);
        graph->col_idx[graph->row_ptr[source]] = target;
        graph->col_idx[graph->row_ptr[target]] = source;
        graph->row_ptr[source]++;
        graph->row_ptr[target]++;
    }

    // Reset row_ptr values to their original state
    for (int i = num_vertices; i > 0; i--) {
        graph->row_ptr[i] = graph->row_ptr[i - 1];
    }
    graph->row_ptr[0] = 0;
}

// Function to free memory used by CSR graph
void freeCSR(struct CSRGraph* graph) {
    free(graph->row_ptr);
    free(graph->col_idx);
}

int main() {
    FILE* file = fopen("edge_list.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    struct CSRGraph graph;
    edgeListToCSR(file, &graph);

    // Print CSR graph (for demonstration)
    printf("CSR Graph:\n");
    printf("Num Vertices: %d\n", graph.num_vertices);
    printf("Num Edges: %d\n", graph.num_edges);
    printf("Row Pointer Array:\n");
    for (int i = 0; i <= graph.num_vertices; i++) {
        printf("%d ", graph.row_ptr[i]);
    }
    printf("\n");
    printf("Column Index Array:\n");
    for (int i = 0; i < graph.num_edges * 2; i++) {
        printf("%d ", graph.col_idx[i]);
    }
    printf("\n");

    fclose(file);
    freeCSR(&graph);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    int num_edges, source, target;
    float weight; // Assuming the weight is a float; change to int if necessary

    file = fopen("edge_list.txt", "r"); // Replace with your file name

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Count the number of edges in the file
    num_edges = 0;
    while (fscanf(file, "%d %d %f", &source, &target, &weight) == 3) {
        num_edges++;
    }

    // Allocate memory for COO arrays
    int *rowidx = (int *)malloc(num_edges * sizeof(int));
    int *colidx = (int *)malloc(num_edges * sizeof(int));
    float *vals = (float *)malloc(num_edges * sizeof(float));

    if (rowidx == NULL || colidx == NULL || vals == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    // Reset file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    int edge_count = 0;
    while (fscanf(file, "%d %d %f", &source, &target, &weight) == 3) {
        // Store edge information in COO arrays
        rowidx[edge_count] = source;
        colidx[edge_count] = target;
        vals[edge_count] = weight; // Change to 1.0 if no weights are provided
        edge_count++;
    }

    fclose(file);

    // Print the COO arrays (for demonstration)
    printf("COO Arrays:\n");
    for (int i = 0; i < num_edges; i++) {
        printf("(%d, %d, %.2f)\n", rowidx[i], colidx[i], vals[i]);
    }

    // Free allocated memory
    free(rowidx);
    free(colidx);
    free(vals);

    return 0;
}
