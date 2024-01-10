#include<bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>>& rgraph, int s, int t, vector<int>& parent, int v){

    vector<bool> visited(v, false);
    queue<int> q;
    q.push(s);
    visited[s]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0; i<v; i++){
            if(visited[i]==false && rgraph[u][i]>0){
                q.push(i);
                parent[i]=u;
                visited[i]=true;
            }
        }
    }
    return visited[t];
}

void maxFlow(vector<vector<int>> &graph, int v, int source, int sink, vector<pair<int,int>> pairs, int x, int y){

    vector<vector<int>> residualGraph=graph;
    
    int max_flow=0;   
    vector<int> parent(v, -1);

    while(bfs(residualGraph, source, sink, parent, v)){
        int path_flow=INT_MAX;
       cout<<"path: "<<endl;
        for(int i=sink; i!=source; i=parent[i]){
            cout<<i<<" ";
            int u=parent[i];
            path_flow=min(path_flow, residualGraph[u][i]);
        }
        cout<<source<<endl;
        cout<<"path_flow: ";
        cout<<path_flow<<endl;

        for(int i=sink; i!=source; i=parent[i]){
            int u=parent[i];
            residualGraph[u][i]-=path_flow;
            residualGraph[i][u]+=path_flow;  
        }

        max_flow+=path_flow;

    }
    cout<<max_flow<<endl;

    cout<<" Pairs :"<<endl;

    for(int i=0; i<pairs.size(); i++){
        cout<<pairs[i].first<<" "<<pairs[i].second-y+1<<endl;
        cout<<residualGraph[pairs[i].second][pairs[i].first]<<endl;
    }

}

int main(){
  int n,m;
  cin>>m>>n;

  int x,y;
  cin>>x>>y;

  int v=x+y+5;

  int edges;
  cin>>edges;

  vector<vector<int>> graph(v, vector<int>(v,0));
  vector<pair<int,int>> pairs;

  for(int i=0; i<edges; i++){
      int u,v;
      cin>>u>>v;
      graph[u][v+y-1]=m;
      pairs.push_back({u,v+y-1});
  }

  for(int i=0; i<x; i++){
      graph[v-1][i]=n;
  }

  for(int i=x; i<x+y; i++){
      graph[i][v-2]=n;
  }


 maxFlow(graph, v, v-1, v-2, pairs, x, y);

}