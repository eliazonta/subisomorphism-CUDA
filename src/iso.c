#define MAX_V 100

// Function to check if two graphs are isomorphic
bool areIsomorphic(int graph1[MAX_V][MAX_V], int graph2[MAX_V][MAX_V], int v1, int v2,
                   int mappings[MAX_V], int n) {
    // If all vertices are mapped, return true
    if (v1 == n) return true;

    // Try all vertices one by one
    for (int i = 0; i < n; i++) {
        // If v2 is not yet mapped and the graphs are isomorphic with v1 and v2 mapped
        if (mappings[i] == -1) {
            // Check if the graphs are isomorphic with v1 and v2 mapped
            bool isIsomorphic = true;
            for (int j = 0; j < n && isIsomorphic; j++) {
                if (graph1[v1][j] && graph2[i][j] != 1) {
                    isIsomorphic = false;
                    break;
                }
            }

            if (isIsomorphic) {
                // Map v1 to v2 and proceed with the next vertex
                mappings[i] = v1;
                if (areIsomorphic(graph1, graph2, v1 + 1, v2, mappings, n)) return true;
                mappings[i] = -1; // Backtrack
            }
        }
    }

    return false;
}

// Function to check if two graphs are isomorphic
bool isGraphIsomorphic(int graph1[MAX_V][MAX_V], int graph2[MAX_V][MAX_V], int n) {
    // Initialize mapping array with -1 indicating no mapping
    int mappings[MAX_V];
    for (int i = 0; i < n; i++) mappings[i] = -1;

    // Start with the first vertex
    return areIsomorphic(graph1, graph2, 0, 0, mappings, n);
}