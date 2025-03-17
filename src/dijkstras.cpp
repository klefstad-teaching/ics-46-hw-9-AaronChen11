#include "dijkstras.h"
#include <queue>
#include <limits>
#include <algorithm>

void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) {
        cout << "No path exists" << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " ";
    }
    cout << " " << endl;
    cout << "Total cost is " << total_cost << endl;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int end_vertex) {
    vector<int> path;
    
    if (distances[end_vertex] == numeric_limits<int>::max()) {
        return path;
    }
    
    for (int v = end_vertex; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
    reverse(path.begin(), path.end());
    return path;
}

vector<int> dijkstra_shortest_path(const Graph& g, int start_vertex, vector<int>& previous) {
    int n = g.graph.size();
    vector<int> distances(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    previous.resize(n, -1);
    
    distances[start_vertex] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start_vertex});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (const auto& edge : g.graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (!visited[v] && distances[u] != numeric_limits<int>::max() && 
                distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    
    return distances;
}

void file_to_graph(const string& filename, Graph& g) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Cannot open file: " + filename);
    }
    
    int n;
    file >> n;
    g.graph.resize(n);
    
    int u, v, w;
    while (file >> u >> v >> w) {
        if (u >= n || v >= n || u < 0 || v < 0) {
            throw runtime_error("Invalid vertex in input file");
        }
        g.graph[u].push_back({v, w});
    }
}