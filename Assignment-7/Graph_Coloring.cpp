
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Check whether two vertices are adjacent
bool isAdjacent(vector<vector<int>> &graph, int u, int v)
{
    for (int x : graph[u])
    {
        if (x == v)
            return true;
    }
    return false;
}

// Find the smallest available color
int getColor(int u, vector<vector<int>> &graph,
             vector<int> &color, int V)
{
    vector<bool> used(V, false);

    for (int v : graph[u])
    {
        if (color[v] != -1)
            used[color[v]] = true;
    }

    int c = 0;
    while (c < V && used[c])
        c++;

    return c;
}

// 1. Greedy Coloring
vector<int> greedyColoring(int V, vector<vector<int>> &graph)
{
    vector<int> color(V, -1);

    for (int u = 0; u < V; u++)
        color[u] = getColor(u, graph, color, V);

    return color;
}

// 2. Welsh-Powell Algorithm
vector<int> welshPowell(int V, vector<vector<int>> &graph)
{
    vector<int> order(V), color(V, -1);

    for (int i = 0; i < V; i++)
        order[i] = i;

    sort(order.begin(), order.end(), [&](int a, int b)
    {
        return graph[a].size() > graph[b].size();
    });

    int currentColor = 0;

    for (int u : order)
    {
        if (color[u] == -1)
        {
            color[u] = currentColor;

            for (int v : order)
            {
                if (color[v] == -1)
                {
                    bool conflict = false;

                    for (int x : graph[v])
                    {
                        if (color[x] == currentColor)
                        {
                            conflict = true;
                            break;
                        }
                    }

                    if (!conflict)
                        color[v] = currentColor;
                }
            }

            currentColor++;
        }
    }

    return color;
}

// Calculate saturation degree for DSATUR
int saturation(int u, vector<vector<int>> &graph,
               vector<int> &color)
{
    vector<int> used;

    for (int v : graph[u])
    {
        if (color[v] != -1)
            used.push_back(color[v]);
    }

    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());

    return used.size();
}

// 3. DSATUR Algorithm
vector<int> dsatur(int V, vector<vector<int>> &graph)
{
    vector<int> color(V, -1);

    for (int count = 0; count < V; count++)
    {
        int u = -1;
        int bestSat = -1;
        int bestDegree = -1;

        for (int v = 0; v < V; v++)
        {
            if (color[v] == -1)
            {
                int sat = saturation(v, graph, color);
                int degree = graph[v].size();

                if (sat > bestSat ||
                   (sat == bestSat && degree > bestDegree))
                {
                    bestSat = sat;
                    bestDegree = degree;
                    u = v;
                }
            }
        }

        color[u] = getColor(u, graph, color, V);
    }

    return color;
}

// Count colors used
int countColors(vector<int> &color)
{
    int maximum = -1;

    for (int c : color)
        maximum = max(maximum, c);

    return maximum + 1;
}

// Display schedule
void displaySchedule(string name, vector<int> &color, int V)
{
    cout << "\n" << name << "\n";
    cout << "Course\tExam Slot\n";

    for (int i = 0; i < V; i++)
        cout << i + 1 << "\t" << color[i] + 1 << "\n";

    cout << "Total exam slots: " << countColors(color) << "\n";
}

// Check classroom capacity per time slot
void roomAllocation(vector<int> &color, int V)
{
    int rooms;
    cout << "\nEnter available classrooms per time slot: ";
    cin >> rooms;

    if (rooms <= 0)
    {
        cout << "Invalid number of classrooms.\n";
        return;
    }

    int slots = countColors(color);
    vector<int> roomCount(slots, 0);

    for (int i = 0; i < V; i++)
        roomCount[color[i]]++;

    cout << "\nRoom Allocation Check\n";

    for (int i = 0; i < slots; i++)
    {
        cout << "Slot " << i + 1 << ": "
             << roomCount[i] << " exams, "
             << rooms << " rooms available - ";

        if (roomCount[i] <= rooms)
            cout << "Valid\n";
        else
            cout << "Insufficient rooms\n";
    }
}

int main()
{
    int V, E;

    cout << "UNIVERSITY TIMETABLE SCHEDULING\n";

    cout << "Enter number of courses: ";
    cin >> V;

    if (V <= 0)
    {
        cout << "Invalid number of courses.\n";
        return 0;
    }

    cout << "Enter number of conflicts: ";
    cin >> E;

    if (E < 0)
    {
        cout << "Invalid number of conflicts.\n";
        return 0;
    }

    vector<vector<int>> graph(V);

    cout << "Enter conflicting course pairs:\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;

        if (u < 1 || u > V || v < 1 || v > V || u == v)
        {
            cout << "Invalid edge. Enter valid course numbers.\n";
            return 0;
        }

        u--;
        v--;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> greedy = greedyColoring(V, graph);
    vector<int> wp = welshPowell(V, graph);
    vector<int> ds = dsatur(V, graph);

    displaySchedule("1. GREEDY COLORING", greedy, V);
    displaySchedule("2. WELSH-POWELL", wp, V);
    displaySchedule("3. DSATUR", ds, V);

    cout << "\nALGORITHM COMPARISON\n";
    cout << "Greedy slots: " << countColors(greedy) << "\n";
    cout << "Welsh-Powell slots: " << countColors(wp) << "\n";
    cout << "DSATUR slots: " << countColors(ds) << "\n";

    // Select the schedule with the fewest slots
    vector<int> best = greedy;

    if (countColors(wp) < countColors(best))
        best = wp;

    if (countColors(ds) < countColors(best))
        best = ds;

    cout << "\nSelected schedule uses "
         << countColors(best) << " exam slots.\n";

    roomAllocation(best, V);

    return 0;
}

