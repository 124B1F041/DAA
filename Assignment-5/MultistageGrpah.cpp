#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 999999

int main() {
    int N = 8; // Total cities/nodes (0 to 7)

    // Cost matrix between cities (INF means no direct road)
    vector<vector<int>> cost(N, vector<int>(N, INF));

    // Stage 0 -> Stage 1 (Warehouse to Hubs)
    cost[0][1] = 2;
    cost[0][2] = 1;
    cost[0][3] = 5;

    // Stage 1 -> Stage 2 (Hubs to Regional Centers)
    cost[1][4] = 4;  cost[1][5] = 11;
    cost[2][4] = 9;  cost[2][5] = 5;   cost[2][6] = 16;
    cost[3][6] = 2;

    // Stage 2 -> Stage 3 (Regional Centers to Destination)
    cost[4][7] = 18;
    cost[5][7] = 13;
    cost[6][7] = 2;

    // DP Array to store minimum cost from each city to destination (Node 7)
    vector<int> minCost(N, INF);
    vector<int> nextCity(N, -1);

    // Destination node cost to itself is 0
    minCost[7] = 0;

    // Work backwards from Node 6 down to Node 0
    for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (cost[i][j] != INF) { // If a road exists
                if (cost[i][j] + minCost[j] < minCost[i]) {
                    minCost[i] = cost[i][j] + minCost[j];
                    nextCity[i] = j; // Store next step in optimal path
                }
            }
        }
    }

    // Print Total Cheapest Cost
    cout << "Cheapest Delivery Cost: " << minCost[0] << endl;

    // Print Route
    cout << "Optimal Route: ";
    int current = 0;
    while (current != -1) {
        cout << current << (nextCity[current] != -1 ? " -> " : "");
        current = nextCity[current];
    }
    cout << endl;

    return 0;
}
