#include <bits/stdc++.h>
using namespace std;

#define INF 1e7 + 5

void floyed_warshall(int v, vector<vector<int>> graph, int src, int dest)
{

      int next[v+1][v+1];

     for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {

             if(graph[i][j] == -1)
                graph[i][j] = INF;

                next[i][j]=j;
        }
    }

    for(int k=1; k<=v; k++)
    {
        for(int i=1; i<=v; i++)
        {
            for(int j=1; j<=v; j++){
                if(graph[i][j] > graph[i][k] + graph[k][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    cout<<graph[src][dest]<<endl;
    vector<int> path;
    int curr=src;
    while(curr != dest)
    {   
        cout<<curr<<" ->";
        path.push_back(curr);
        curr = next[curr][dest];
    }
    cout<<dest<<endl;
}


int main()
{
    int v, e;
    cin >> v>>e;
    
    vector<vector<int>> graph(v+1, vector<int>(v+1));

    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {

            if (i == j)
                graph[i][j] = 0;
            else
            {
                graph[i][j] = -1;
            }
    }
    }

    for (int i = 0; i < e; i++)
    {
        int src, dest, wt;
        cin >> src >> dest >> wt;
        graph[src][dest] = wt;
        graph[dest][src] = wt;
    }
    int src, dest;
    cin >> src >> dest;

    floyed_warshall(v, graph, src, dest);
}