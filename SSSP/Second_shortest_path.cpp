#include<bits/stdc++.h>
using namespace std;

#define INF INT_MAX



struct edge{
    int src, dest, weight;

    edge(int src, int dest, int weight){
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }
    edge(){

    }  
};

void dijsktra(int v, int e, vector<vector<pair<int,int>>>adj, vector<edge> edges){
   vector<vector<int>> dist(v+1,vector<int>(2,INT_MAX));
    vector<vector<int>> parent(v+1,vector<int>(2,-1));  
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<bool> visited(v+1,false);
    dist[1][0] = 0;
    pq.push({0,1});
    while(!pq.empty()){
        int u =pq.top().second;
        int wt=pq.top().first;
        pq.pop();

        for(auto it: adj[u]){
            int v = it.first;
            int weight = it.second;
        
            //  if(dist[v][0] > dist[u][0] + weight){
            //     dist[v][1] = dist[v][0];
            //     dist[v][0] = dist[u][0] + weight;
            //     pq.push({dist[v][0],v});
            //     parent[v][1] = parent[v][0];
            //     parent[v][0] = u;
            // }
            // else if(dist[v][1] > dist[u][0] + weight && parent[v][0] != u){
            //     dist[v][1] = dist[u][0] + weight;
            //     pq.push({dist[v][1],v});
            //     parent[v][1] = u;
            // }

            
        }

        //cout<<"hi"<<endl; 
    }

    if(dist[v][1] == INT_MAX){
        cout<<-1<<endl;
        return;
    }

    cout<<dist[v][1]<<endl;

       
           
    
}



int main(){
    int v,e;
    cin>>v>>e;
    vector<vector<pair<int,int>>>adj(v+1);
    vector<edge> edges(e);

    for(int i=0; i<e; i++){
        int src, dest, weight;
        cin>>src>>dest>>weight;
        adj[src].push_back({dest,weight});
        adj[dest].push_back({src,weight});
        edges[i] = edge(src,dest,weight);
    }


    
    
    dijsktra(v,e,adj,edges);



}