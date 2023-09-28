#ifndef __iso_h__
#define __iso_h__
#include <stdbool.h>
#include <string.h>
#include "../parsing/parser.h"

// Function to check if two graphs are isomorphic
bool iso(struct COOGraph g1, struct COOGraph g2, int* map, int v, int n); 

// Function to check if two graphs are isomorphic
bool are_iso(struct COOGraph g1, struct COOGraph g2); 

#endif // eof