#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_V 100

// CSR representation of a graph
struct CSR {
    int* row_ptr; // Array of row pointers
    int* col_idx; // Array of column indices
    int num_vertices;
    int num_edges;
};

// Function to check if a vertex in the pattern can be mapped to a vertex in the target
bool isSafe(struct CSR target, struct CSR pattern, int target_vertex, int pattern_vertex, int mapping[]) {
    // Check if the vertex is adjacent to previously mapped vertices
    for (int i = target.row_ptr[target_vertex]; i < target.row_ptr[target_vertex + 1]; i++) {
        int neighbor = target.col_idx[i];
        if (mapping[neighbor] == -1) continue; // Unmapped vertices are safe
        if (!pattern.row_ptr[pattern_vertex]) continue; // Ensure the pattern vertex has neighbors
        if (!pattern.row_ptr[pattern_vertex + 1]) continue; // Ensure the pattern vertex has neighbors
        if (!pattern.row_ptr[pattern_vertex + 1] - pattern.row_ptr[pattern_vertex]) continue; // Ensure the pattern vertex has neighbors
        if (!pattern.row_ptr[pattern_vertex]) continue; // Ensure the pattern vertex has neighbors

        // Check if the mapped vertex in the target is adjacent to the current vertex in the pattern
        bool is_adjacent = false;
        for (int j = pattern.row_ptr[pattern_vertex]; j < pattern.row_ptr[pattern_vertex + 1]; j++) {
            if (pattern.col_idx[j] == mapping[neighbor]) {
                is_adjacent = true;
                break;
            }
        }
        if (!is_adjacent) return false;
    }

    return true;
}

// Backtracking function to find subgraph isomorphism
bool subgraphIsomorphism(struct CSR target, struct CSR pattern, int mapping[], int pattern_vertex) {
    if (pattern_vertex == pattern.num_vertices) {
        // All vertices in the pattern graph have been mapped successfully
        return true;
    }

    for (int target_vertex = 0; target_vertex < target.num_vertices; target_vertex++) {
        if (mapping[pattern_vertex] == -1 && isSafe(target, pattern, target_vertex, pattern_vertex, mapping)) {
            mapping[pattern_vertex] = target_vertex;

            // Recursively try to map the next vertex in the pattern
            if (subgraphIsomorphism(target, pattern, mapping, pattern_vertex + 1))
                return true;

            // If mapping the current vertex didn't lead to a solution, backtrack
            mapping[pattern_vertex] = -1;
        }
    }

    return false;
}

// Function to find subgraph isomorphism
bool findSubgraphIsomorphism(struct CSR target, struct CSR pattern) {
    int mapping[MAX_V];
    for (int i = 0; i < pattern.num_vertices; i++)
        mapping[i] = -1;

    return subgraphIsomorphism(target, pattern, mapping, 0);
}

int main() {
    // Initialize the target and pattern graphs in CSR format
    struct CSR target, pattern;
    // Set the values of num_vertices, num_edges, row_ptr, and col_idx for both target and pattern

    if (findSubgraphIsomorphism(target, pattern)) {
        printf("Subgraph isomorphism found.\n");

        // Print the mapping
        printf("Mapping of pattern vertices to target vertices:\n");
        for (int i = 0; i < pattern.num_vertices; i++) {
            printf("Pattern vertex %d -> Target vertex %d\n", i, mapping[i]);
        }
    } else {
        printf("Subgraph isomorphism not found.\n");
    }

    return 0;
}
