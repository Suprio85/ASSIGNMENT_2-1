#include<bits/stdc++.h>
using namespace std;

#define INF 1e8+10
#define vvi vector<vector<int>>
#define vi vector<int>






void dijsktra(int src,  vector<vi> adj[], int v , int e,int d){

    vector<vector<int>> dist(v+1,vector<int>(v+1,INF));
    dist[src][0]=0;

    priority_queue<vi,vector<vi>,greater<vi>> pq;

    pq.push({0,0,src});

    while(!pq.empty()){

        int parent = pq.top()[2];
        int wt =pq.top()[0];
        int cnt = pq.top()[1];
         
        pq.pop();

        for(auto x : adj[parent]){

            int child =x[0];
            int wt =x[1];
            int type=x[2];

            if((type+cnt<=d) and dist[cnt+type][child]>dist[cnt][parent]+wt){
                dist[cnt+type][child]=dist[cnt][parent]+wt;
                pq.push({dist[cnt][parent]+wt,cnt+type,child});

            }

        }
    }

    int ans =INF;
    for(int i =0; i<v; i++){

        ans=min(ans,dist[i][v-1]);
    }

    
    cout<<ans<<endl;



}







int main(){
    int v, e;
    cin >> v >> e;

    int k,d;
    cin>>k>>d;

    vector<vi> adj[v];

    for(int i=0; i<e; i++){
        int src, dest,weight;
        cin >> src >> dest >>weight;
        adj[src].push_back({dest,weight,0});
    }

   for(int i=0; i<k; i++){
      int src,dest,weight;
      cin>> src>>dest>>weight;

      adj[src].push_back({dest,weight,1});
   }

   


   dijsktra(0,adj,v,e,d);


}

















