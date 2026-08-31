#include <bits/stdc++.h>
using namespace std;

void dijkstra(int source, vector<vector<pair<int, int>>> &graph,
              vector<int> &dist)
{
    int V = graph.size();

    dist.assign(V, INT_MAX);
    dist[source] = 0;

    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    pq.push({0, source});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main()
{
    int V, E;

    cout << "Enter number of intersections (vertices): ";
    cin >> V;

    cout << "Enter number of roads (edges): ";
    cin >> E;

    vector<vector<pair<int, int>>> graph(V);

    cout << "Enter edges (u v w):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        // Check whether vertices are valid
        if (u >= 0 && u < V && v >= 0 && v < V && w >= 0)
        {
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        else
        {
            cout << "Invalid edge. Please enter valid values.\n";
            i--;
        }
    }

    int source;

    cout << "Enter ambulance start location (source): ";
    cin >> source;

    if (source < 0 || source >= V)
    {
        cout << "Invalid source vertex.\n";
        return 0;
    }

    int H;

    cout << "Enter number of hospitals: ";
    cin >> H;

    if (H <= 0)
    {
        cout << "No hospitals entered.\n";
        return 0;
    }

    vector<int> hospitals(H);

    cout << "Enter hospital nodes: ";

    for (int i = 0; i < H; i++)
    {
        cin >> hospitals[i];

        if (hospitals[i] < 0 || hospitals[i] >= V)
        {
            cout << "Invalid hospital node.\n";
            return 0;
        }
    }

    vector<int> dist;

    dijkstra(source, graph, dist);

    int minTime = INT_MAX;
    int nearestHospital = -1;

    for (int h : hospitals)
    {
        if (dist[h] != INT_MAX && dist[h] < minTime)
        {
            minTime = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital == -1)
    {
        cout << "No hospital is reachable from the ambulance location.\n";
    }
    else
    {
        cout << "\nNearest hospital is at node "
             << nearestHospital
             << " with travel time "
             << minTime
             << " minutes.\n";
    }

    return 0;
}
