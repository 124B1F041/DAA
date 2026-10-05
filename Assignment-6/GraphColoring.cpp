#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class GraphColoringBB {
private:
    int V;                         // Number of vertices
    vector<vector<int>> adj;       // Adjacency matrix
    vector<int> bestColoring;      // Stores the best valid coloring found
    int minColors;                 // Upper bound (best solution found so far)

    // Check if color 'c' is valid for vertex 'v'
    bool isSafe(int v, int c, const vector<int>& color) {
        for (int i = 0; i < V; ++i) {
            if (adj[v][i] && color[i] == c) {
                return false;
            }
        }
        return true;
    }

    // Branch and Bound recursive search
    void branchAndBound(int v, vector<int>& color, int currentMaxColor) {
        // Base Case: If all vertices are colored, update global minimum
        if (v == V) {
            if (currentMaxColor < minColors) {
                minColors = currentMaxColor;
                bestColoring = color;
            }
            return;
        }

        // Branching: Try colors from 1 up to minColors - 1 (Bounding)
        for (int c = 1; c < minColors; ++c) {
            if (isSafe(v, c, color)) {
                color[v] = c;
                int newMaxColor = max(currentMaxColor, c);

                // Bound condition: Only continue if current branch can yield a better solution
                if (newMaxColor < minColors) {
                    branchAndBound(v + 1, color, newMaxColor);
                }

                // Backtrack
                color[v] = 0;

                // Symmetry breaking pruning:
                // Do not try unused colors higher than (currentMaxColor + 1)
                if (c > currentMaxColor) {
                    break;
                }
            }
        }
    }

public:
    GraphColoringBB(int vertices) : V(vertices), minColors(vertices + 1) {
        adj.assign(V, vector<int>(V, 0));
        bestColoring.resize(V, 0);
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void solve() {
        vector<int> color(V, 0);

        // Start Branch and Bound search from vertex 0
        branchAndBound(0, color, 0);

        cout << "Chromatic Number (Minimum Colors): " << minColors << "\n";
        cout << "Vertex Color Assignment:\n";
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << " -> Color " << bestColoring[i] << "\n";
        }
    }
};

int main() {
    // Example Graph (5 Vertices)
    GraphColoringBB g(5);

    // Edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.solve();

    return 0;
}
