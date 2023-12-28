#include<bits/stdc++.h>
using namespace std;

struct edge {
    int src, dest, weight;

    edge(int src, int dest, int weight) {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }
};

struct Result {
    int parent;
    int weight;
};

struct Compare {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.first > p2.first;
    }
};

class Graph {
public:
    int V;
    vector<vector<edge>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int src, int dest, int weight) {
        edge e1(src, dest, weight);
        adj[src].push_back(e1);

        edge e2(dest, src, weight);
        adj[dest].push_back(e2);
    }

    void print() {
        for (int i = 0; i < V; i++) {
            cout << i << "->";
            for (auto j : adj[i]) {
                cout << j.dest << " ";
            }
            cout << endl;
        }
    }

    void Dijkstra(int src) {
        print();
        vector<bool> sssp(V, false);
        vector<Result> res(V); //
        vector<int> key(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

        key[src] = 0;
        res[src].parent = -1;
        res[src].weight = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto x = pq.top();
            pq.pop();
            int current = x.second;

            if (!sssp[current]) {
                sssp[current] = true;

                for (auto i : adj[current]) {
                    int dest = i.dest;
                    if (!sssp[dest]) {
                        if (key[dest] > key[current] + i.weight) {
                            key[dest] = key[current] + i.weight;
                            res[dest].parent = current;
                            res[dest].weight = key[dest];
                            pq.push({key[dest], dest});
                        }
                    }
                }
            }
        }

        print_result(res);
    }

    void print_result(vector<Result>& res) {
        for (int i = 1; i < res.size(); i++) {
            cout << i << " " << res[i].parent << " " << res[i].weight << endl;
        }
    }
};

int main() {
    Graph g(9);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.Dijkstra(0);

    return 0;
}
