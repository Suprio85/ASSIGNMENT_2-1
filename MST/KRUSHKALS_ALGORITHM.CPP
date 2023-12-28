#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int src;
    int des;
    int wt;

    edge(int src, int des, int wt)
    {
        this->src = src;
        this->des = des;
        this->wt = wt;
    }
};

int find(int v, vector<int> &parent)
{
    if (parent[v] <= -1)
        return v;
    else
        return parent[v] = find(parent[v], parent);
}

void _union(int from, int to, vector<int> &parent)
{

    if (parent[from] < parent[to])
        parent[to] = from;
    else if (parent[from] > parent[to])
        parent[from] = to;

    else
    {
        parent[to] = from;
        parent[from]--;
    }
}

bool compare(edge a, edge b)
{
    return a.wt < b.wt;
}

void krushkal(int v, int e, vector<edge> Edge,long long int& max_weight)
{
    sort(Edge.begin(), Edge.end(), compare);
    vector<int> parent(v+1, -1);
    vector<edge> mst_set;
    int i = 0, j = 0;

    while (i < v - 1 and j < e)
    {
        int from_parent = find(Edge[j].src, parent);
        int to_parent = find(Edge[j].des, parent);

        if (from_parent != to_parent)
        {
            _union(from_parent, to_parent, parent);

            mst_set.push_back(Edge[j]);
            max_weight+=Edge[j].wt;
            i++;
        }

        j++;
    }

    for (auto ans : mst_set)
    {

        cout << "MST :" << endl;
        cout << ans.src << "    " << ans.des << "wet :" << ans.wt << endl;
    }

    cout << "max weight :" << max_weight << endl;
}

int main()
{

    int V, E;
    cin >> V >> E;
    vector<edge> edges;

    for (int i = 0; i < E; i++)
    {
        int s, d, w;
        cin >> s >> d >> w;
        edge Edge(s, d, w);
        edges.push_back(Edge);
    }

    long long int max_weight = 0;

    krushkal(V, E, edges, max_weight);
}