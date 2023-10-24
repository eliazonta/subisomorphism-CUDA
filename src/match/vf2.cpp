// --------------------------------------------------------
// implementation of VF2 algorithm for graph isomorphism
//---------------------------------------------------------
#include <iostream>
#include <vector>
#include <cstring>

class VF2 {
private:
    int **graph1, **graph2;
    int size;
    bool *visited1, *visited2;
    std::vector<int> mapping;

    bool isFeasible(int node1, int node2) {
        if (visited1[node1] || visited2[node2])return false;

        for (int i = 0; i < size; ++i) {
            if (graph1[node1][i] != graph2[node2][i])return false;
        }

        return true;
    }

    bool vf2(int depth) {
        if (depth == size)return true;

        for (int i = 0; i < size; ++i) {
            if (isFeasible(depth, i)) {
                visited1[depth] = true;
                visited2[i] = true;
                mapping[depth] = i;

                if (vf2(depth + 1))return true;

                visited1[depth] = false;
                visited2[i] = false;
            }
        }

        return false;
    }

public:
    VF2(int **g1, int **g2, int n) {
        graph1 = g1;
        graph2 = g2;
        size = n;
        visited1 = new bool[size];
        visited2 = new bool[size];
        mapping.resize(size);
        memset(visited1, 0, sizeof(bool) * size);
        memset(visited2, 0, sizeof(bool) * size);
    }

    bool isIsomorphic() {
        return vf2(0);
    }
};
