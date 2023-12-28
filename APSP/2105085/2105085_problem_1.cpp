#include <bits/stdc++.h>
using namespace std;

#define INF 1e7 + 5

void floyed_warshall(vector<vector<int>> graph, int v, int threshold_cost)
{

    vector<int> count_min(v+1,0);
    vector<vector<bool>> visited(v+1,vector<bool>(v+1,false));

    for (int k = 1; k <= v; k++)
    {
        for (int i = 1; i <= v; i++)
        {
            for (int j = 1; j <= v; j++)
            {
                if (graph[i][j] > graph[i][k] + graph[k][j])    
                        graph[i][j] = graph[i][k] + graph[k][j];

                if(graph[i][j]<=threshold_cost and !visited[i][j]){
                    count_min[i]++;
                    visited[i][j]=true;
                }
            }
        }
    }


    int _min=INF;
    for(int i=1; i<=v; i++){
        _min=min(_min,count_min[i]);

    }

    for(int i=1; i<=v ; i++){
        if(count_min[i]==_min){
            cout<<i<<" ";
        }
    }
    cout<<endl;
}

int main()
{
    int v, e;
    cin >> v >> e;

    vector<vector<int>> graph(v + 1, vector<int>(v + 1));

    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {

            if (i == j)
                graph[i][j] = 0;
            else
            {
                graph[i][j] = INF;
                graph[j][i] = INF;
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

    int threshold_cost;

    cin >> threshold_cost;

    floyed_warshall(graph, v, threshold_cost);
}