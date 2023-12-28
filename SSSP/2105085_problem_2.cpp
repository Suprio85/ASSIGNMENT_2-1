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

    edge() {}
};

int bellmenford(vector<edge> edges, int src, int des, int V, int E,bool& is_used)
{

        vector<int> parent(V + 1, -1);
        vector<int> dist(V + 1, INT_MAX);

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
                    is_updating = true;
                }
            }
        }
        bool is_negative_cycle = false;

        if (is_updating)
        {
            for (int j = 0; j < E; j++)
            {
                int u = edges[j].src;
                int v = edges[j].dest;
                int w = edges[j].weight;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                {
                  
                    is_negative_cycle = true;
                    return -1;
                    
                }
            }
        }

        edge e1 = edges[edges.size() - 1];
        if(parent[e1.src] == e1.dest or parent[e1.dest] == e1.src){
            is_used = true;
        }
        else{
            is_used = false;
        }

        return dist[des];
    }




int main()
{

    int ver, e;
    cin >> ver >> e;

    vector<edge> edges(e);

    for (int i = 0; i < e; i++)
    {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        edges[i] = edge(src, dest, weight);
    }

    int u, v;
    cin >> u >> v;
    int l, r;
    cin >> l >> r;

    int src, dest;
    cin >> src >> dest;

    bool is_possible = false,is_used=false; 
    int wt,ans;  

    for(int i=l; i<=r; i++){
        edges.push_back(edge(u, v, i));
         ans = bellmenford(edges, src, dest, ver, edges.size(),is_used);
        if(ans != -1 and ans!=INT_MAX and is_used){
            wt = i;
            is_possible = true;
            break;
        }

        edges.pop_back();
    }

    if(is_possible){

     cout<< wt << " " << ans << endl;
    }
    else{
        cout << "IMPOSSIBLE" << endl;
    }

}