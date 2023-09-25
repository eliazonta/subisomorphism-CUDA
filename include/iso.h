#ifndef __iso_h__
#define __iso_h__
#include <stdbool.h>
#include <string.h>
#include "../include/parser.h"

// Function to check if two graphs are isomorphic
bool iso(struct COOGraph g1, struct COOGraph g2, int* map, int v, int n) 
{
    // If all vertices are mapped, return true
    if (v == n) return true;

    // Try all vertices one by one
    for (int i = 0; i < n; ++i) 
    {
        // If v2 is not yet mapped and the graphs are isomorphic with v1 and v2 mapped
        if (map[i] == -1)
        {
            // Check if the graphs are isomorphic with v1 and v2 mapped
            bool isomprphism = true;
            for (int j = g1.rowidx[v]; j < g1.rowidx[v + 1]; ++j) 
            {
                int n1 = g1.colidx[j];
                int n2 = -1;
                for(int k = g2.rowidx[v]; k < g2.rowidx[v + 1]; ++k)
                {
                    if (g2.colidx[k] == n1) 
                    {
                        n2 = k;
                        break;
                    }
                }
                if (n2 != -1 || g2.weights[n2] != g1.weights[j]) 
                {
                    // Map v1 to v2 and proceed with the next vertex
                   isomprphism = false;
                   break;
                }
            }
            if(isomprphism)
            {
                map[i] = v;
                if(iso(g1, g2, map, v + 1, n))
                {
                    return true;
                }
                map[i] = -1;
            }

        }
    }
    return false;
}

// Function to check if two graphs are isomorphic
bool are_iso(struct COOGraph g1, struct COOGraph g2) 
{
    if(g1.nnz != g2.nnz || g1.num_rows != g2.num_rows)return false;
    int n = g1.nnz;
    // int* map = (int*) malloc(n * sizeof(int));
    int map[n];
    // arr init with -1s
    memset(map, -1, n * sizeof(map[0])); // cool init indeed
    // Start with the first vertex
    return iso(g1, g2, map, 0, n);
}
#endif