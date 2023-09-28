#include <stdio.h>
#include <stdlib.h>
#include "../parsing/parser.h"


int main(int argc, char** argv) 
{
    struct COOGraph g1;
    int num_edges;
    int* rowidx, colidx;
    dtype* weights;

    char* filepath = "../../toy/g2.mtx";
    if(argc == 2)filepath = argv[1];
    
    fprintf(stdout, "Parser with no struct\n");
    readCOO(filepath, num_edges, &rowidx, &colidx, &weights);
    fprintf(stdout, "Parser with struct\n");
    readCOO_struct(filepath, &g1);
    return 0;
}
