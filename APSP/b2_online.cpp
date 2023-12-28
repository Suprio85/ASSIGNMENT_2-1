#include<bits/stdc++.h>
using namespace std;

#define INF 1e7 + 5









int main(){
    int v,e;
    cin>>v>>e;
    vector<vector<int>> graph(v+1,vector<int>(v+1,INF));
    for(int i=0; i<v; i++) graph[i][i]=0;

    for(int i=0; i<e; i++){
        int a,b,c;
        cin>>a>>b>>c;
        graph[a][b]=c;
    }

    for(int k=0; k<v; k++)
    {
        for(int i=0; i<v; i++)
        {
            for(int j=0; j<v; j++){
                if(graph[i][j] > graph[i][k] + graph[k][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

    for(int i=0; i<v; i++){
        if(graph[i][i]<0){
            cout<<"NEGATIVE CYCLE"<<endl;
            return 0;
        }
    }

    cout<<"NEGATIVE CYCLE NOT FOUND"<<endl;

      
}