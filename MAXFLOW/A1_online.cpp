#include<bits/stdc++.h>
using namespace std;

struct cndtn{
  int height;
  int age;
  bool status;
};


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

void maxFlow(vector<vector<int>> &graph, int v, int source, int sink){

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

}

int main(){

    int n,m;
    cin>>n>>m;

    int v=n+m+2;

    vector<vector<int>> graph(v,vector<int>(v,0));

    for(int i=1; i<=n; i++) graph[0][i]=1;
    for(int i=n+1; i<=n+m; i++) graph[i][v-1]=1;

    for(int i=0; i<m; i++){
        
        int a,t ;
        cin>>a>>t;
        for(int i=1; i<=t; i++){
            int v;
            cin>>v;
            graph[v][n+a]=1;
            //graph[n+1][v]=1;
        }
    }

    maxFlow(graph,v,0,v-1);

}