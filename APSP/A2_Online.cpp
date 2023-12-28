#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

const double INF = 1e9;

bool arbitragePossible(vector<vector<double>>& graph, int n) {
    vector<vector<double>> dist(n, vector<double>(n, INF));

    // Initialize distances
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 1;
    }

    // Relax edges using Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], 1.0*abs(dist[i][k]  * dist[k][j]));
                }
            }
        }
    }

    // Check for negative cycle
    for (int i = 0; i < n; ++i) {
         cout << dist[i][i] << endl;
        if (dist[i][i] < 1) {
            return true;  // Negative cycle detected
        }
    }

    return false;  // No negative cycle found
}

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        int n;
        cin >> n;

        vector<string> currencies(n);
        map<string, int> currencyIndex;

        for (int i = 0; i < n; ++i) {
            cin >> currencies[i];
            currencyIndex[currencies[i]] = i;
        }

        int m;
        cin >> m;

        vector<vector<double>> graph(n, vector<double>(n, INF));

        for (int i = 0; i < m; ++i) {
            string ci, cj;
            double rij;
            cin >> ci >> rij >> cj;

            graph[currencyIndex[ci]][currencyIndex[cj]] = (rij);
        }

        if (arbitragePossible(graph, n)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
