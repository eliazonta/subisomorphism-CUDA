#pragma once 
#ifndef __SUBISO__
#define __SUBISO__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../graph/graph.h"

#define MAX_V 100
static int mapping[MAX_V]; // ugly as hell 


bool isSafe(struct CSRGraph target, struct CSRGraph pattern, int target_vertex, int pattern_vertex, int mapping[]);
bool subgraphIsomorphism(struct CSRGraph target, struct CSRGraph pattern, int mapping[], int pattern_vertex);
bool findSubgraphIsomorphism(struct CSRGraph target, struct CSRGraph pattern); 

#endif // eof