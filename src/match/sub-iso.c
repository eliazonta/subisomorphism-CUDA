#include "sub-iso.h"

bool isSafe(struct CSRGraph target, struct CSRGraph pattern, int target_vertex, int pattern_vertex, int mapping[])
{
    // Check if the vertex is adjacent to previously mapped vertices
    for (int i = target.rowptr[target_vertex]; i < target.rowptr[target_vertex + 1]; i++) {
        int neighbor = target.colidx[i];
        if (mapping[neighbor] == -1) continue; // Unmapped vertices are safe
        if (!pattern.rowptr[pattern_vertex]) continue; // Ensure the pattern vertex has neighbors
        if (!pattern.rowptr[pattern_vertex + 1]) continue; // Ensure the pattern vertex has neighbors
        if (!pattern.rowptr[pattern_vertex + 1] - pattern.rowptr[pattern_vertex]) continue; // Ensure the pattern vertex has neighbors
        if (!pattern.rowptr[pattern_vertex]) continue; // Ensure the pattern vertex has neighbors

        // Check if the mapped vertex in the target is adjacent to the current vertex in the pattern
        bool is_adjacent = false;
        for (int j = pattern.rowptr[pattern_vertex]; j < pattern.rowptr[pattern_vertex + 1]; j++) {
            if (pattern.colidx[j] == mapping[neighbor]) {
                is_adjacent = true;
                break;
            }
        }
        if (!is_adjacent) return false;
    }

    return true;
}

bool subgraphIsomorphism(struct CSRGraph target, struct CSRGraph pattern, int mapping[], int pattern_vertex)
{
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

bool findSubgraphIsomorphism(struct CSRGraph target, struct CSRGraph pattern)
{
    for (int i = 0; i < pattern.num_vertices; i++)
        mapping[i] = -1;

    return subgraphIsomorphism(target, pattern, mapping, 0);
}