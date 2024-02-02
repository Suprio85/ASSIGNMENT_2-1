#include<bits/stdc++.h>
using namespace std;

struct cndtn{
  int height;
  int age;
  bool status;
};
void dfs(vector<vector<int>>& rgraph, int s, vector<bool>& visited, int v){
    visited[s]=true;
    for(int i=0; i<v; i++){
        if(visited[i]==false && rgraph[s][i]>0){
            dfs(rgraph, i, visited, v);
        }
    }
}

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

void maxFlow(vector<vector<int>> &graph, int v, int source, int sink,int n, int m){

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
    vector<bool> visited(v,false);
    dfs(residualGraph,0,visited,v);

    cout<<"after dfs"<<endl;

    for(int i=0; i<v;i++){
        cout<<i<<" ";
        cout<<visited[i]<<endl;
    }

    for(int i=0; i<v; i++){

        if(visited[i]){
            for(int j=0; j<v; j++)
            {
                if(visited[j]==false  and graph[i][j]>0){

                    cout<<"man "<<i<<" "<<"woman "<<j-n<<endl;
                }
            }

        }


    }






}

int main(){
  int n,m;
  cin>>n>>m;

  int v=n+m+2;
  vector<vector<int>> graph(v,vector<int>(v,0));

  for(int i=1; i<=n; i++) graph[0][i]=1;
  for(int i=n+1; i<=n+m; i++) graph[i][v-1]=1;

  vector<cndtn> conditions(v);

  for(int i=1; i<=n+m; i++){
  cin>>conditions[i].height>>conditions[i].age>>conditions[i].status;
  }
  for(int i=1; i<=n; i++){
    for(int j=n+1; j<=n+m;j++){
       if((abs(conditions[i].height-conditions[j].height)<=10) and (abs(conditions[i].age-conditions[j].age)<=5) and conditions[i].status==conditions[j].status){
        
        graph[i][j]=1;
       
       }
    }
  }




  maxFlow(graph,v,0,v-1,n,m);

}