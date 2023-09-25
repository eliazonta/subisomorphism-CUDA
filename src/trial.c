#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// #include "../include/parser.h"

// Structure to represent a COO-format graph
struct COOGraph {
    int* rowidx;
    int* colidx;
    int num_vertices;
    int num_edges;
};

// Function to check if two graphs are isomorphic using the VF2 algorithm
bool isIsomorphic(struct COOGraph* graph1, struct COOGraph* graph2, bool* mapping, int n, int m) {
    // Base case: If all vertices are mapped, the graphs are isomorphic
    if (n == graph1->num_vertices && m == graph2->num_vertices) {
        return true;
    }

    // Check if there is an unmapped vertex in graph1
    if (n < graph1->num_vertices) {
        for (int i = 0; i < graph2->num_vertices; i++) {
            if (!mapping[i] && graph1->num_vertices == graph2->num_vertices) {
                // Check if the vertices have the same degree
                int deg1 = 0, deg2 = 0;
                for (int j = graph1->rowidx[n]; j < graph1->rowidx[n + 1]; j++) {
                    int neighbor1 = graph1->colidx[j];
                    if (mapping[neighbor1]) {
                        deg1++;
                    }
                }
                for (int j = graph2->rowidx[i]; j < graph2->rowidx[i + 1]; j++) {
                    int neighbor2 = graph2->colidx[j];
                    if (mapping[neighbor2]) {
                        deg2++;
                    }
                }
                if (deg1 != deg2) {
                    continue;
                }

                // Try mapping the vertices
                mapping[i] = true;
                if (isIsomorphic(graph1, graph2, mapping, n + 1, m + 1)) {
                    return true;
                }
                mapping[i] = false; // Backtrack
            }
        }
    }

    return false;
}

int main() {
    // Example COO-format graphs (replace with your data)
    struct COOGraph graph1 = {
        .rowidx = (int[]){0, 2, 4, 6},
        .colidx = (int[]){1, 2, 0, 3, 1, 2},
        .num_vertices = 4,
        .num_edges = 6
    };

    struct COOGraph graph2 = {
        .rowidx = (int[]){0, 2, 4, 6},
        .colidx = (int[]){1, 2, 0, 3, 1, 2},
        .num_vertices = 4,
        .num_edges = 6
    };

    bool mapping[4] = {false};

    if (isIsomorphic(&graph1, &graph2, mapping, 0, 0)) {
        printf("The two graphs are isomorphic.\n");
    } else {
        printf("The two graphs are not isomorphic.\n");
    }

    return 0;
}
