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
