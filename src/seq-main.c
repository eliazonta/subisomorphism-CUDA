#include <stdio.h>
#include <stdlib.h>

#include "parsing/parser.h"
#include "match/iso.h"

int main() {
    // int num_edges, source, target;
    // double weight; // Assuming the weight is a float; change to int if necessary
    // struct COOGraph g;
    char file[] = "../toy/g2.mtx";
    struct COOGraph g1, g2;
    readCOO_struct(file, &g1);
    readCOO_struct(file, &g2);
    
    if(are_iso(g1, g2)){
        printf("iso\n");
    }
    return 0;
}
