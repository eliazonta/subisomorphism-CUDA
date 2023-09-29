#include "graph.h"

int getVertexNum(int* arr, int s)
{
    int uVals[s], uc = 0;
    memset(uVals, 0, s * sizeof(uVals[0])); // cool init indeed
    for (size_t i = 0; i < s; ++i) 
    {
        int isU = 1; // assume is unique 
        for (size_t j = 0; j < uc; ++j) 
        {
            if (arr[i] == uVals[j]) 
            {
                isU = 0; // Not unique
                break;
            }
        }
        if (isU) 
        {
            uVals[uc++] = arr[i];
        }
    }
    return uc;
}

void removeSelfLoops(struct COOGraph* g) 
{
    int k = 0;
    int* nr = malloc(g->num_edges * sizeof(int));
    int* nc = malloc(g->num_edges * sizeof(int));

    for (size_t i = 0; i < g->num_edges; ++i) {
        if (g->rowidx[i] != g->colidx[i]) {
            nr[k] = g->rowidx[i];
            nr[k] = g->colidx[i];
            k++;
        }
    }

    free(g->rowidx);
    free(g->colidx);

    g->rowidx = nr;
    g->colidx = nc;
    g->num_edges = k;
}
