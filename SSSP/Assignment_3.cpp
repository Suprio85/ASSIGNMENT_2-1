#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int src, dest, weight;

    edge(int src, int dest, int weight)
    {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }

    edge()
    {
    }
};

void min_path_util(int u, int v, vector<bool> visited, vector<int> path, int path_index, vector<vector<edge>>& adj, vector<vector<int>> &paths, vector<int>& wt, int& w, priority_queue<int, vector<int>, greater<int>>& pq)
{
    cout<<"u "<<u<<" v "<<v<<endl;
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    cout<<"path_index "<<path_index<<endl;
    if (u == v)
    {   cout<<"terminating"<<endl;
        vector<int> temp;
        for (int i = 0; i < path_index; i++)
        {
            temp.push_back(path[i]);
            cout<<path[i]<<" ";
        }
        cout<<endl;
        cout<<"w "<<w<<endl;
        pq.push(w);
        paths.push_back(temp);
        wt.push_back(w);
        pq.push(w);
        w=0;
    }
    else
    {   cout<<"adj[u].size()"<<adj[u].size()<<endl;
        for (auto i : adj[u])
        {
            cout<<i.src<<" "<<i.dest<<" "<<i.weight<<endl;
            if (!visited[i.dest])
            {   w+=i.weight;
                min_path_util(i.dest, v, visited, path, path_index, adj, paths, wt, w, pq);
                w-=i.weight;
            }
        }
    }

    path_index--;
    visited[u] = false;
}


int bellmenford(vector<edge> edges, int src, int des, int V, int E, bool &is_used, int l, int r, int U, int Ve, vector<vector<edge>> adj)
{
  
    vector<int> parent(V + 1, -1);
    vector<int> dist(V + 1, INT_MAX);
    vector<int> parent_value(V + 1);

    dist[src] = 0;
    bool is_updating = false;

    for (int k = 0; k < V - 1; k++)
    {
        is_updating = false;
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                parent_value[v] = w;
                is_updating = true;
            }
        }
    }

    if (is_updating)
    {
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])

            {

                vector<bool> visited(V + 1, false);
                vector<vector<int>> paths(V + 1);
                vector<int> path(v);
                int path_index = 0;
                vector<int> paths_wt;
                int path_w = 0;
                priority_queue<int, vector<int>, greater<int>> pq;
                cout<<"YES"<<endl;  
                min_path_util(Ve, U, visited, path, path_index, adj, paths, paths_wt, path_w, pq);
                //cout<<"YES"<<endl;
                int min_wt = pq.top();
                 if(-1*min_wt>=l and -1*min_wt<=r){
                }
            }
        }
    }
    
    edge e1 = edges[edges.size() - 1];
    if (parent[e1.src] == e1.dest or parent[e1.dest] == e1.src)
    {
        is_used = true;
    }
    else
    {
        is_used = false;
    }

    return dist[des];
}

int main()
{

    int ver, e;
    cin >> ver >> e;
    vector<edge> edges(e);
    vector<vector<edge>> adj(ver + 1);

    for (int i = 0; i < e; i++)
    {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        edges[i] = edge(src, dest, weight);
        adj[src].push_back(edge(src, dest, weight));
    }

    int u, v;
    cin >> u >> v;
    int l, r;
    cin >> l >> r;

    int src, dest;
    cin >> src >> dest;

    bool is_possible = false, is_used = false;
    int wt, ans;

    edges.push_back(edge(u, v, l));
    bellmenford(edges, src, dest, ver, edges.size(), is_used, l, r, u, v, adj);

    if (is_possible)
    {

        cout << wt << " " << ans << endl;
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }
}