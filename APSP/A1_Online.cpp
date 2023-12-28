#include<bits/stdc++.h>
using namespace std;

#define INF 1e7 + 5


int main(){
 int v,e;
    cin>>v>>e;

    vector<vector<int>> graph(v+1,vector<int>(v+1,INF));

   for(int i=1; i<=v; i++) graph[i][i]=0;

    for(int i=0; i<e; i++){
        int a,b,c;
        cin>>a>>b>>c;
        graph[a][b]=c;
        graph[b][a]=c;
    }

      int node_1, node_2;
    cin>>node_1>>node_2;

    for(int i=1 ; i<=v ; i++)
    {
        if(graph[node_1][i] != INF and node_2!=i and node_1!=i){
            for(int j=1; j<=v; j++){
                if(node_1!=j and i!=j and graph[i][j]!=INF){
                    cout<<i<<" "<<j<<endl;
                    cout<<graph[i][j]<<endl;
                    graph[i][j]=INF;
                 
                }

            }
        }
    }

     for(int i=1 ; i<=v ; i++)
    {
        if(graph[node_2][i] != INF and node_2!=i and node_1!=i){
            for(int j=1; j<=v; j++){
                if(node_2!=j and i!=j and graph[i][j]!=INF){
                     cout<<i<<" "<<j<<endl;
                    cout<<graph[i][j]<<endl;
                    graph[i][j]=INF;
                   

                }
            }
        }
    }



    

    int next[v+1][v+1]; 

    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            next[i][j]=j;
        }
    }

    for(int k=1; k<=v; k++){
        for(int i=1; i<=v; i++){
            for(int j=1; j<=v; j++){

                if(graph[i][j] > graph[i][k] + graph[k][j]  ){
                    graph[i][j]=graph[i][k] + graph[k][j];
                    next[i][j]=next[i][k];
                }
            }
        }
    }


    int src,dest;

    do{
        cin>>src>>dest;
        vector<int> path;
        cout<<"Shortest path is: "<<endl;

        cout<<graph[src][dest]<<endl;


       int curr=src;
    while(curr != dest)
    {   
        cout<<curr<<" ->";
        path.push_back(curr);
        curr = next[curr][dest];
    }
    cout<<dest<<endl;



    }while(src!=-1 and dest!=-1);







}