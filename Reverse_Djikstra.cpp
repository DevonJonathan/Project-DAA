#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

void dijkstra(int nodes, int start, vector<vector<pii>>& graph) {
    vector<int> distances(nodes, INT_MAX);
    vector<int> previous(nodes, -1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_node])
            continue;

        for (auto& neighbor : graph[current_node]) {
            int next_node = neighbor.first;
            int weight = neighbor.second;
            int new_distance = current_distance + weight;

            if (new_distance < distances[next_node]) {
                distances[next_node] = new_distance;
                previous[next_node] = current_node;
                pq.push({new_distance, next_node});
            }
        }
    }

    // Output distances from start node
    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < nodes; ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Node " << i << ": Unreachable\n";
        } else {
            cout << "Node " << i << ": " << distances[i] << "\n";
        }
    }

    // Output paths to each node
    cout << "\nPaths from start node " << start << ":\n";
    for (int i = 0; i < nodes; ++i) {
        if (distances[i] != INT_MAX && i != start) {
            vector<int> path;
            for (int at = i; at != -1; at = previous[at]) {
                path.push_back(at);
            }
            cout << "Path to node " << i << ": ";
            for (int j = path.size() - 1; j >= 0; --j) {
                cout << path[j];
                if (j > 0) cout << " -> ";
            }
            cout << "\n";
        }
    }
}

int main() {
    int nodes, edges;
    
    // Input number of nodes and edges
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;

    // Create an adjacency list representation of the graph
    vector<vector<pii>> graph(nodes);

    // Input all edges
    cout << "Enter edges in the format: start_node end_node weight\n";
    for (int i = 0; i < edges; ++i) {
        int start, end, weight;
        cin >> start >> end >> weight;
        graph[start].push_back({end, weight});
        graph[end].push_back({start, weight});  // For undirected graph, add this line
    }

    int start_node;
    cout << "Enter the start node: ";
    cin >> start_node;

    // Run Dijkstra's algorithm from the start node
    dijkstra(nodes, start_node, graph);

    return 0;
}
