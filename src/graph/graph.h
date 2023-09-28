#ifndef __graph__
#define __graph__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dtype double
// graph structures, currently working on COO, willing to use CSR
// structure to convert COO to CSR

struct COOGraph 
{
    int num_edges;
    int num_vertices;
    int* rowidx;
    int* colidx;
    dtype* weights;
};

struct CSRGraph {
    int num_edges;     
    int num_vertices; 
    int* rowptr;      
    int* colidx;       
    dtype* weights;
};


#endif