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

 vector<vector<int>> dist(100,vector<int>(100,1e6));
 vector<vector<int>> parent(100,vector<int>(100,-1));

void print_shortest_path(int src, int v, int e , vector<vector<pair<int,int>>>adj, vector<edge> edges){

    
    vector<bool> visited(v+1,false);
    priority_queue<pair<int,int>,vector<pair<int,int>> ,greater<pair<int,int>>> pq;
    dist[src][src] = 0;
    pq.push({0,src});
      
    while(!pq.empty()){

        int u =pq.top().second;
        int wt = pq.top().first;
        cout<<"u "<<u<<" "<<"wt: "<<wt<<endl;
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(auto it: adj[u]){
           
            int v = it.first;
            cout<<"v "<<v<<endl;
            if(visited[v]) continue;
            int weight = it.second;
            if(dist[src][v] > dist[src][u] + weight){

                dist[src][v] = dist[src][u] + weight;
                cout<<"weight"<<weight<<endl;
                cout<<"dist[src][v] "<<dist[src][v]<<endl;  
                pq.push({dist[src][v],v});
              
                parent[src][v] = u;

                //cout<<path[v]<<" ";
            }
        }
    }    
}


int main(){
    int v, e;
    cin >> v >> e;

    vector<vector<pair<int,int>>> adj(v);
    vector<edge> edges(e);

    for(int i=0; i<e; i++){
        int src, dest, weight;
        cin >> src >> dest >> weight;
        adj[src].push_back({dest, weight});
       // adj[dest].push_back({src, weight});
        edges[i] = edge(src, dest, weight);
    }
    
   for(int i=0; i<adj.size(); i++){
    cout<<i<<" ->";
       for(int j=0; j<adj[i].size(); j++){
           cout<<adj[i][j].first<<" "<<adj[i][j].second<<", ";
       }
         cout<<endl;
       }

    int src;
    cin>>src;

   // print_shortest_path(src,v,e,adj,edges);

    // for(int i=0; i<v ; i++){
    //     print_shortest_path(i,v,e,adj,edges);
    // }

    print_shortest_path(0,v,e,adj,edges);
    print_shortest_path(1,v,e,adj,edges);
    cout<<"src to dest"<<endl;
    cout<<dist[0][1]<<endl;
    cout<<"dest to src"<<endl;
    cout<<dist[1][0]<<endl;
    
    int min = INT_MAX;
    int min_index = -1;

    for(int i=1; i<v; i++){
        if(i==src) continue;
      if(dist[src][i]+dist[i][src] < min){
          min = dist[src][i]+dist[i][src];
            min_index = i;
      }

    }
     cout<<min<<endl;

     stack<int> src_path;
     stack<int> dest_path;

        int temp = min_index;
        while(temp != -1){
            src_path.push(temp);
            temp = parent[src][temp];
        }

        while(!src_path.empty()){
            cout<<src_path.top()<<" ";
            src_path.pop();
        }
        cout<<endl;
        temp = src;
         cout<<temp<<" ";        
        
        while(temp != min_index){
            temp = parent[min_index][temp];
            cout<<temp<<" ";
        }
        while(!dest_path.empty()){
            cout<<dest_path.top()<<" ";
            dest_path.pop();
        }
}


