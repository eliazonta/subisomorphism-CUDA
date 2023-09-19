#include <stdio.h>
#include <stdlib.h>

#include "../include/iso.h"

int main() {
    // int num_edges, source, target;
    // double weight; // Assuming the weight is a float; change to int if necessary
    // struct COOGraph g;
    char file[] = "../toy/g2.mtx";
    struct COOGraph g1, g2;
    readCOO(file, &g1);
    readCOO(file, &g2);
    
    if(are_iso(g1, g2)){
        printf("iso\n");
    }
    return 0;
    // printf("COO Arrays:\n");
    // printf("row idx:\n");
    // for (size_t i = 0; i < g.num_rows; i++) {
    //     printf("%d ", g.rowidx[i]);
    // }
    // printf("\ncol idx:\n");
    // for (size_t i = 0; i < g.num_cols; i++) {
    //     printf("%d ", g.colidx[i]);
    // }
    // printf("\nvals:\n");
    // for (size_t i = 0; i < g.nnz; i++) {
    //     printf("%.2lf ", g.vals[i]);
    // }
    // printf("\n\n");

    

}
