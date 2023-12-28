#include<bits/stdc++.h>
using namespace std;

struct edge {
    int src, dest, weight;

    edge(int src, int dest, int weight) {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }
    edge(){

    }  
};


void print_shortest_path(int v, int e , vector<vector<pair<int,int>>>adj, vector<edge> edges){
    vector<int> dist(v+1,INT_MAX);
    vector<bool> visited(v+1,false);
    vector<int> parent(v+1,-1);
    priority_queue<pair<int,int>,vector<pair<int,int>> ,greater<pair<int,int>>> pq;
    dist[1] = 0;
    pq.push({0,1});
  
    while(!pq.empty()){

        int u =pq.top().second;
        int wt = pq.top().first;
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(auto it: adj[u]){
            int v = it.first;
            if(visited[v]) continue;
            int weight = it.second;
            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.push({dist[v],v});
                parent[v] = u;
                //cout<<path[v]<<" ";
            }
        }
    }

    if(dist[v] == INT_MAX){
        cout << -1 << endl;
        return;
    }
   stack<int> path;
    while(v != -1){
        path.push(v);
        v = parent[v];
    }
    
    while(!path.empty()){
        cout<<path.top()<<" ";
        path.pop();
    }
    
    
}


int main(){
    int v, e;
    cin >> v >> e;

    vector<vector<pair<int,int>>> adj(v+1);
    vector<edge> edges(e);

    for(int i=0; i<e; i++){
        int src, dest, weight;
        cin >> src >> dest >> weight;
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight});
        edges[i] = edge(src, dest, weight);
    }

    print_shortest_path(v,e,adj,edges);




}

