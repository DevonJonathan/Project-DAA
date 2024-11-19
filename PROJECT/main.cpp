#include <bits/stdc++.h>
using namespace std;

const double INF = numeric_limits<double>::infinity();
const int INTERSECTION_COST = 2; // Cost per intersection in minutes

struct Node {
    int id;
    string location;
    double Longtitude;
    double Latitude;
};

class Graph {
private:
    unordered_map<int, list<pair<int, double>>> adj;

public:
    void addEdge(int u, int v, double weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // For undirected graph
    }

    pair<double, vector<int>> dijkstra(int start, int end) {
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
        unordered_map<int, double> dist;
        unordered_map<int, int> prev;
        vector<int> path;

        for (const auto& node : adj) dist[node.first] = INF;
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int curr = pq.top().second;
            pq.pop();

            if (curr == end) break;

            for (const auto& [neighbor, weight] : adj[curr]) {
                double new_dist = dist[curr] + weight + INTERSECTION_COST / 60.0;
                if (new_dist < dist[neighbor]) {
                    dist[neighbor] = new_dist;
                    prev[neighbor] = curr;
                    pq.push({new_dist, neighbor});
                }
            }
        }

        for (int at = end; prev.find(at) != prev.end(); at = prev[at])
            path.push_back(at);
        path.push_back(start);
        reverse(path.begin(), path.end());

        return {dist[end], path};
    }

    void printPath(const vector<int>& path, const unordered_map<int, string>& location_map) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << "Node " << path[i] << " (" << location_map.at(path[i]) << ")";
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
};

double calculateDistance(double lon1, double lat1, double lon2, double lat2) {
    return sqrt(pow(lon2 - lon1, 2) + pow(lat2 - lat1, 2)) / 1000.0; // Distance in km
}

int getNodeByLocation(const string& location, const vector<Node>& nodes) {
    for (const auto& node : nodes)
        if (node.location == location) return node.id;
    return -1; // Not found
}

void loadDataset(const string& filename, vector<Node>& nodes, unordered_map<int, string>& location_map, Graph& graph) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Failed to open dataset file." << endl;
        exit(1);
    }

    string line;
    getline(infile, line); // Skip header
    int node_id = 0;

    while (getline(infile, line)) {
        stringstream ss(line);
        string objectid, location, longtitude_str, latitude_str, intid;

        getline(ss, objectid, ',');
        getline(ss, location, ',');
        getline(ss, longtitude_str, ',');
        getline(ss, latitude_str, ',');
        getline(ss, intid, ',');

        try {
            double Longtitude = stod(longtitude_str);
            double Latitude = stod(latitude_str);
            nodes.push_back({node_id, location, Longtitude, Latitude});
            location_map[node_id] = location;
            ++node_id;
        } catch (const exception&) {
            continue; // Skip invalid rows
        }
    }

    // Add edges based on distance
    for (const auto& node : nodes) {
        for (const auto& neighbor : nodes) {
            if (node.id != neighbor.id) {
                double distance = calculateDistance(node.Longtitude, node.Latitude, neighbor.Longtitude, neighbor.Latitude);
                if (distance <= 2.0) graph.addEdge(node.id, neighbor.id, distance);
            }
        }
    }
}

int main() {
    Graph graph;
    vector<Node> nodes;
    unordered_map<int, string> location_map;

    // Load dataset
    loadDataset("Intersection_Points_Final.csv", nodes, location_map, graph);

    // Input starting and destination locations
    string start_location, end_location;
    cout << "Enter starting location: ";
    getline(cin, start_location);
    cout << "Enter destination location: ";
    getline(cin, end_location);

    int start_node = getNodeByLocation(start_location, nodes);
    int end_node = getNodeByLocation(end_location, nodes);

    if (start_node == -1 || end_node == -1) {
        cout << "Invalid location entered!" << endl;
        return 1;
    }

    // Find shortest path
    auto [shortest_distance_km, path] = graph.dijkstra(start_node, end_node);

    // Output results
    cout << "Starting Location: " << start_location << endl;
    cout << "Destination Location: " << end_location << endl;
    cout << "Jarak terpendek: " << fixed << setprecision(2) << shortest_distance_km << " km" << endl;

    int num_intersections = path.size() - 2;
    cout << "Jumlah intersection yang dilewati: " << max(0, num_intersections) << endl;

    cout << "Waktu tempuh: " << fixed << setprecision(0)
         << round(((shortest_distance_km / 60.0) * 60) + (INTERSECTION_COST * path.size())) << " menit" << endl;

    cout << "Rute: ";
    graph.printPath(path, location_map);

    return 0;
}
