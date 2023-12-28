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


void print_shortest_path(int v, int e ,int src, int dest, int k, vector<vector<pair<int,int>>>adj, vector<edge> edges){
    vector<int> dist(v+1,INT_MAX);
    vector<bool> visited(v+1,false);
    vector<int> parent(v+1,-1);
    vector<int> used(v+1,0);
    priority_queue<pair<int,int>,vector<pair<int,int>> ,greater<pair<int,int>>> pq;
    dist[src] = 0;
    used[src] = 0;
    pq.push({0,src});
  
    while(!pq.empty()){

        int u=pq.top().second;
        int wt =pq.top().first;
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
      



        for(auto it: adj[u]){
            int v = it.first;
            int weight = it.second;
            if(used[u] <= k ){

                used[v]=used[u]+1;
                dist[v] = dist[u] + weight;
            
               // cout<<"dist[v] :"<<endl;
               // cout<<v<<" "<<dist[v]<<endl;
                pq.push({dist[v],v});
                parent[v] = u;
               // cout<<parent[v]<<" ->" <<v<<endl;;
            }
        }
    }
    
    //cout<<"dist[dest] :"<<endl;
    cout<<dist[dest]<<endl;
    
  
    
    
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
       // adj[dest].push_back({src, weight});
        edges[i] = edge(src, dest, weight);
    }

    int src, dest;
    int k;
    cin >> src >> dest >> k;

    int used = 0;

    //print_shortest_path(v,e,adj,edges);
    print_shortest_path(v,e,src,dest,k,adj,edges);




}
/*

4 5
0 1 100
1 2 100
2 0 100
1 3 600
2 3 200
0 3 1

output : 700

3 3
0 1 100
1 2 100
0 2 500
0 2 1

output : 200

3 3
0 1 100
1 2 100
0 2 500
0 2 0


output 500



*/
