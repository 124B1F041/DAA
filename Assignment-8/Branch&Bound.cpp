
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX / 4;

struct Node
{
    vector<int> path;
    vector<bool> visited;
    int city;
    int level;
    int cost;
    int bound;
};

struct Compare
{
    bool operator()(const Node &a, const Node &b)
    {
        return a.bound > b.bound;
    }
};

// Calculate a lower bound for the remaining route
int calculateBound(const Node &node, vector<vector<int>> &cost, int n)
{
    int bound = node.cost;

    // Minimum outgoing edge for each unvisited city
    for (int i = 0; i < n; i++)
    {
        if (!node.visited[i] || i == node.city)
        {
            int minimum = INF;

            for (int j = 0; j < n; j++)
            {
                if (i != j && cost[i][j] < minimum)
                    minimum = cost[i][j];
            }

            if (minimum == INF)
                return INF;

            bound += minimum;
        }
    }

    return bound;
}

// LC Branch and Bound for Travelling Salesman Problem
void tsp(vector<vector<int>> &cost, int n)
{
    priority_queue<Node, vector<Node>, Compare> pq;

    Node root;
    root.path.push_back(0);
    root.visited.assign(n, false);
    root.visited[0] = true;
    root.city = 0;
    root.level = 1;
    root.cost = 0;
    root.bound = calculateBound(root, cost, n);

    pq.push(root);

    int bestCost = INF;
    vector<int> bestPath;

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        // Prune if this route cannot improve the best route
        if (current.bound >= bestCost)
            continue;

        // All cities visited: return to starting city
        if (current.level == n)
        {
            int returnCost = cost[current.city][0];

            if (returnCost != INF)
            {
                int totalCost = current.cost + returnCost;

                if (totalCost < bestCost)
                {
                    bestCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
                }
            }

            continue;
        }

        // Expand to each unvisited city
        for (int next = 0; next < n; next++)
        {
            if (!current.visited[next] &&
                cost[current.city][next] != INF)
            {
                Node child = current;

                child.city = next;
                child.level = current.level + 1;
                child.cost = current.cost + cost[current.city][next];
                child.visited[next] = true;
                child.path.push_back(next);

                child.bound = calculateBound(child, cost, n);

                if (child.bound < bestCost)
                    pq.push(child);
            }
        }
    }

    if (bestPath.empty())
    {
        cout << "\nNo complete delivery route exists.\n";
        return;
    }

    cout << "\nOptimal Delivery Route: ";

    for (int city : bestPath)
        cout << city + 1 << " ";

    cout << "\nMinimum Total Cost: " << bestCost << "\n";
}

int main()
{
    int n;

    cout << "DELIVERY ROUTE OPTIMIZATION\n";
    cout << "Enter number of cities: ";
    cin >> n;

    if (n < 2)
    {
        cout << "Enter at least 2 cities.\n";
        return 0;
    }

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "Enter cost matrix (0 for no road, diagonal 0):\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;

            if (i == j)
                cost[i][j] = 0;
            else if (x == 0)
                cost[i][j] = INF;
            else if (x < 0)
            {
                cout << "Costs must be non-negative.\n";
                return 0;
            }
            else
                cost[i][j] = x;
        }
    }

    tsp(cost, n);

    return 0;
}

