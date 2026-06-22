#include <bits/stdc++.h>
using namespace std;

const int N = 500;
vector<pair<int,int>> adj[N];

vector<int> bfs(int start, bool visited[]) {
    vector<int> comp;
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int city = q.front(); q.pop();
        comp.push_back(city);
        for (auto& p : adj[city])
            if (!visited[p.first]) { visited[p.first] = true; q.push(p.first); }
    }
    return comp;
}

vector<int> dijkstra(int src) {
    vector<int> dist(N, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : adj[u])
            if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; pq.push({dist[v], v}); }
    }
    return dist;
}

int main() {
    srand(time(0));
    int totalEdges = 0;

    for (int i = 0; i < N; i++) {
        if (i > 0) {
            int nb = rand() % i, dist = rand() % 46 + 5;
            adj[i].push_back({nb, dist});
            adj[nb].push_back({i, dist});
            totalEdges++;
        }
        for (int e = 0; e < 2; e++) {
            int u = rand() % N, v = rand() % N;
            if (u == v) continue;
            bool exists = false;
            for (auto& p : adj[u])
                if (p.first == v) { exists = true; break; }
            if (!exists) {
                int dist = rand() % 46 + 5;
                adj[u].push_back({v, dist});
                adj[v].push_back({u, dist});
                totalEdges++;
            }
        }
    }

    // Task A
    cout << "TASK A: Network Summary" << endl;
    cout << "Total Cities (Nodes)      : " << N << endl;
    cout << "Total Connections (Edges) : " << totalEdges << endl;

    // Task B + C: BFS
    bool visited[N] = {false};
    vector<vector<int>> components;
    for (int i = 0; i < N; i++)
        if (!visited[i])
            components.push_back(bfs(i, visited));

    int largestIdx = 0, smallestIdx = 0;
    for (int i = 1; i < components.size(); i++) {
        if (components[i].size() > components[largestIdx].size()) largestIdx = i;
        if (components[i].size() < components[smallestIdx].size()) smallestIdx = i;
    }

    cout << "\nTASK B: Largest Connected Component" << endl;
    cout << "Total Cities in Largest Component : " << components[largestIdx].size() << endl;
    cout << "Cities : [";
    for (int i = 0; i < components[largestIdx].size(); i++)
        cout << components[largestIdx][i] << (i != components[largestIdx].size()-1 ? ", " : "");
    cout << "]" << endl;

    cout << "\nTASK C: Cluster Detection" << endl;
    cout << "Total Connected Components : " << components.size() << endl;
    for (int i = 0; i < components.size(); i++)
        cout << "Component " << i+1 << " : " << components[i].size() << " cities" << endl;
    cout << "Largest Cluster  : Component " << largestIdx+1 << " with " << components[largestIdx].size() << " cities" << endl;
    cout << "Smallest Cluster : Component " << smallestIdx+1 << " with " << components[smallestIdx].size() << " cities" << endl;

    // Task D
    int src;
    cout << "Enter source city: ";
    cin >> src;

    vector<int> dist = dijkstra(src);

    cout << "\nTASK D: Dijkstra's Shortest Path from City " << src << endl;

    cout << "\nShortest Distance Table:" << endl;
    for (int i = 0; i < N; i++)
        if (dist[i] != INT_MAX)
            cout << "City " << src << " -> City " << i << " : " << dist[i] << " km" << endl;

    cout << "\nUnreachable Cities : ";
    bool any = false;
    for (int i = 0; i < N; i++)
        if (dist[i] == INT_MAX) { cout << i << " "; any = true; }
    if (!any) cout << "None";
    cout << endl;

    int maxCity = 0;
    for (int i = 1; i < N; i++)
        if (dist[i] != INT_MAX && dist[i] > dist[maxCity]) maxCity = i;
    cout << "\nFarthest City from City " << src << " : City " << maxCity << " at " << dist[maxCity] << " km" << endl;

    return 0;
}