#include "dijkstras.h"

void verify_dijkstras() {
    cout << "Running Dijkstra's algorithm verification tests...\n" << endl;
    
    vector<string> test_files = {
        "../src/small.txt",      
        "../small.txt",
        "src/small.txt"
    };
    
    Graph G;
    bool found_file = false;
    string used_path;
    
    for (const auto& path : test_files) {
        try {
            file_to_graph(path, G);
            found_file = true;
            used_path = path;
            cout << "Successfully loaded graph from: " << path << endl;
            break;
        } catch (const runtime_error&) {
            continue;
        }
    }
    
    if (!found_file) {
        cerr << "Error: Could not find test graph file in any of the expected locations" << endl;
        throw runtime_error("Graph file not found");
    }
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    cout << "\nTesting shortest paths from vertex 0:\n" << endl;
    
    for (int i = 0; i < G.numVertices; i++) {
        cout << "Path from 0 to " << i << ":" << endl;
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
        cout << endl;
    }
    
    vector<pair<string, string>> additional_files = {
        {"../src/medium.txt", "medium"},
        {"../src/large.txt", "large"},
        {"../src/largest.txt", "largest"}
    };
    
    for (const auto& [file, name] : additional_files) {
        try {
            Graph test_G;
            file_to_graph(file, test_G);
            cout << "\nTesting with " << name << " graph:" << endl;
            
            vector<int> test_previous;
            vector<int> test_distances = dijkstra_shortest_path(test_G, 0, test_previous);
            
            cout << "Successfully computed shortest paths" << endl;
            cout << "Number of vertices: " << test_G.numVertices << endl;
            cout << "Distance to last vertex: " << test_distances[test_G.numVertices-1] << endl;
            cout << endl;
        } catch (const runtime_error&) {
            cout << "Skipping " << name << " graph (file not found)" << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            verify_dijkstras();
            return 0;
        }
        
        if (argc != 2) {
            cerr << "Usage: " << argv[0] << " [graph_file]" << endl;
            cerr << "Or run without arguments to execute verification tests" << endl;
            return 1;
        }

        Graph G;
        file_to_graph(argv[1], G);
        
        vector<int> previous;
        vector<int> distances = dijkstra_shortest_path(G, 0, previous);
        
        cout << "Shortest paths from vertex 0:" << endl;
        for (int i = 0; i < G.numVertices; i++) {
            cout << "\nPath from 0 to " << i << ":" << endl;
            vector<int> path = extract_shortest_path(distances, previous, i);
            print_path(path, distances[i]);
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}