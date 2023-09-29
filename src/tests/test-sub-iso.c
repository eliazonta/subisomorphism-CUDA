#include "../match/sub-iso.h"

int main() {
    struct CSRGraph target, pattern;
    // init missing since are missing CSR utilities
    
    if (findSubgraphIsomorphism(target, pattern)) 
    {
        fprintf(stdout, "Subgraph isomorphism FOUND!.\n");
        fprintf(stdout, "Mapping of pattern vertices to target vertices:\n");
        for (size_t i = 0; i < pattern.num_vertices; ++i) 
        {
            fprintf(stdout, "Pattern vertex %zu -> Target vertex %d\n", i, mapping[i]);
        }
    } else {
        fprintf(stdout, "Subgraph isomorphism NOT FOUND.\n");
    }

    return 0;
}