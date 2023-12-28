#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class PrimAlgorithmPQBetter {
public:
    struct Edge {
        int source;
        int destination;
        int weight;

        Edge(int source, int destination, int weight) : source(source), destination(destination), weight(weight) {}
    };

    struct ResultSet {
        int parent;
        int weight;
    };

    struct Compare {
        bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
            return p1.first > p2.first;
        }
    };

    int vertices;
    vector<vector<Edge>> adjacencylist;

    PrimAlgorithmPQBetter(int vertices) : vertices(vertices), adjacencylist(vertices) {}

    void addEdge(int source, int destination, int weight) {
        Edge edge(source, destination, weight);
        adjacencylist[source].push_back(edge);

        edge = Edge(destination, source, weight);
        adjacencylist[destination].push_back(edge); // for undirected graph
    }

    void primMST() {
        vector<bool> mst(vertices, false);
        vector<ResultSet> resultSet(vertices);
        vector<int> key(vertices, numeric_limits<int>::max());

        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

        // Initialize starting vertex
        key[0] = 0;
        pq.push({0, 0});
        resultSet[0].parent = -1;

        // Main loop
        while (!pq.empty()) {
            // Extract the min
            pair<int, int> extractedPair = pq.top();
            pq.pop();

            // Extracted vertex
            int extractedVertex = extractedPair.second;
            mst[extractedVertex] = true;

            // Iterate through all the adjacent vertices and update the keys
            for (const Edge& edge : adjacencylist[extractedVertex]) {
                // Only if edge destination is not present in mst
                if (!mst[edge.destination]) {
                    int destination = edge.destination;
                    int newKey = edge.weight;

                    // Check if updated key < existing key, if yes, update it
                    if (key[destination] > newKey) {
                        // Add it to the priority queue
                        pq.push({newKey, destination});
                        // Update the resultSet for destination vertex
                        resultSet[destination].parent = extractedVertex;
                        resultSet[destination].weight = newKey;
                        // Update the key[]
                        key[destination] = newKey;
                    }
                }
            }
        }

        // Print MST
        printMST(resultSet);
    }

    void printMST(const vector<ResultSet>& resultSet) {
        int totalMinWeight = 0;
        cout << "Minimum Spanning Tree: " << endl;
        for (int i = 1; i < vertices; i++) {
            cout << "Edge: " << i << " - " << resultSet[i].parent << " key: " << resultSet[i].weight << endl;
            totalMinWeight += resultSet[i].weight;
        }
        cout << "Total minimum key: " << totalMinWeight << endl;
    }
};

int main() {
    int vertices = 4;
    PrimAlgorithmPQBetter graph(vertices);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 8);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 4);
    graph.primMST();

    return 0;
}
