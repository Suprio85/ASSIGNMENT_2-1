#include<bits/stdc++.h>
using namespace std;



bool bfs(vector<vector<int>>& rgraph, int s, int t, vector<int>& parent, int v){

    vector<bool> visited(v+1, false);

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


void dfs(vector<vector<int>>& rgraph, int s, vector<bool>& visited, int v){
    visited[s]=true;
    for(int i=0; i<v; i++){
        if(visited[i]==false && rgraph[s][i]>0){
            dfs(rgraph, i, visited, v);
        }
    }
}

void maxFlow(vector<vector<int>> &graph, int v, int source, int sink){

    vector<vector<int>> residualGraph=graph;
    vector<int> max_node_flow(v+1,0);
    
    int max_flow=0;   
    vector<int> parent(v+1, -1);

    while(bfs(residualGraph, source, sink, parent, v)){
        int path_flow=INT_MAX;
       // cout<<"path: "<<endl;
        for(int i=sink; i!=source; i=parent[i]){
            //cout<<i<<" ";
            int u=parent[i];
            path_flow=min(path_flow, residualGraph[u][i]);
        }
        // cout<<source<<endl;
        // cout<<"path_flow: ";
        // cout<<path_flow<<endl;

        for(int i=sink; i!=source; i=parent[i]){
            int u=parent[i];
            residualGraph[u][i]-=path_flow;
            residualGraph[i][u]+=path_flow;
            max_node_flow[u]+=path_flow;    
        }

        max_flow+=path_flow;
    }
     
    int node, max_node=INT_MIN;

    for(int i=0; i<v; i++){
        if(i!=source && i!=sink){
            if(max_node_flow[i]>max_node){
                max_node=max_node_flow[i];
                node=i;
            }
            
        }
    }
cout<<"a)"<<endl;   
    cout<<node<<" "<<max_node<<endl;



cout<<"b)"<<endl;

  cout << max_flow << endl;
vector<bool> visited(v + 1, false);
dfs(residualGraph, source, visited, v);

for (int i = 0; i < v; i++)
{
    if (visited[i] == true)
    {
        for (int j = 0; j < v; j++)
        {
            if (visited[j] == false && graph[i][j] > 0)
            {
                cout << (char)(i+'a') << " " << (char)(j+'a') << endl;
            }
        }
    }
}
}

int main(){

    int vertices=26;
    int edges;
    //cin>>vertices>>edges;

    cin>>edges;

    vector<vector<int>> graph(vertices+1, vector<int>(vertices+1, 0));

    for(int i=0; i<edges; i++){
        char u, v;
        int w;;
        cin>>u>>v>>w;
        graph[u-'a'][v-'a'] = w;
    }

    char source, sink;
    cin>>source>>sink;

    maxFlow(graph, vertices, source-'a', sink-'a');
}