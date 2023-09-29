#pragma once
#ifndef __parser_h__
#define __parser_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../graph/graph.h"
// #define HEADER_SIZE 128



void readCOO(const char* filepath, int num_edges, int* rowidx, int* colidx, dtype* weights);
void readCOO_struct(const char* filepath, struct COOGraph* g); 
void freeCOO_struct(struct COOGraph* g);

void edgeListToCSR(FILE* file, struct CSRGraph* g);
void freeCSR_struct(struct CSRGraph* g);

// // Function to create a new COO graph
// struct COOGraph* createCOO(int num_edges); 

// void freeCOO(struct COOGraph* graph);

// // Matrix Market to COO 
// struct COOGraph* getCOO(const char* filename);
// // printing graph
// void printCOO(struct COOGraph* graph);

#endif // eof