#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    previous.resize(G.numVertices, -1);
    vector<bool> visited(G.numVertices, false);
    
    distances[source] = 0;

    for (int count = 0; count < G.numVertices - 1; count++) {
        int min = INF, min_index = -1;
        for (int v = 0; v < G.numVertices; v++) {
            if (!visited[v] && distances[v] <= min) {
                min = distances[v];
                min_index = v;
            }
        }
        
        if (min_index == -1) break;  
        
        visited[min_index] = true;
        
        for (const Edge& edge : G[min_index]) {
            int v = edge.dst;
            if (!visited[v] && distances[min_index] != INF && 
                distances[min_index] + edge.weight < distances[v]) {
                distances[v] = distances[min_index] + edge.weight;
                previous[v] = min_index;
            }
        }
    }
    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;
    
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path exists" << endl;
        return;
    }
    
    cout << "Path (cost " << total << "): ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}