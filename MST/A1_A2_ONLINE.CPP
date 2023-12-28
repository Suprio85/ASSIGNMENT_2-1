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

    edge()
    {
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

int main()
{
    int v, e;
    cin >> v >> e;
    vector<int> parent(v+1, -1);
    vector<int> node_weight(v + 1);
    vector<edge> Edge(e);
    vector<bool> visited(v + 1, false);

    for (int i = 1; i <= v; i++)
    {

        cin >> node_weight[i];
    }

    for (int i = 0; i < e; i++)
    {

        int src, des, wt;
        cin >> src >> des >> wt;
        Edge[i] = edge(src, des, wt);
    

    }

    for(int i=1; i<=v; i++)
    {
        Edge.push_back(edge(0,i,node_weight[i]));
    }

    int wt = 0;
    int i = 0;
    int j=0;
    int count = 0;

    sort(Edge.begin(), Edge.end(), compare);

    for(int i=0; i<Edge.size(); i++)
    {
        cout<<Edge[i].src<<" "<<Edge[i].des<<" "<<Edge[i].wt<<endl;
    }


    while (i < Edge.size() and j<=v-1)
    {

        int from = find(Edge[i].src, parent);
        int to = find(Edge[i].des, parent);

        if (from != to)
        {
            _union(from, to, parent);
            wt += Edge[i].wt;
            j++;
            
        }
        i++;
    }
     cout<<wt<<endl;

    
}

// find_minimum()
