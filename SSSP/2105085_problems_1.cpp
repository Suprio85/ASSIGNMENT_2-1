#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

struct edge
{
    int vertex;
    int distance;

    edge()
    {
    }

    edge(int vertex, int distance)
    {
        this->vertex = vertex;
        this->distance = distance;
    }
};


struct node{
    int vertex;
    int fuel_left;
    int cost;

    node()
    {
    }

    node(int vertex, int fuel_left, int cost)
    {
        this->vertex = vertex;
        this->cost = cost;
        this->fuel_left=fuel_left;
    }

    bool operator < (const node& o)const {
        return this->cost>o.cost;
    }
};

int min_cost(int cities, int roads, int capacity, vector<int> price, vector<vector<edge>> adj, int src, int dest){
    int key[cities][capacity];

    for(int i=1; i<=cities; i++){
        for(int j=0; j<=capacity; j++){
            key[i][j]=INF;
        }
    }

    key[src][0]=0;

    priority_queue<node> pq;
    pq.push(node(src,0,0));
    while(!pq.empty()){

        node x =pq.top();
        pq.pop();
        
        int u= x.vertex;
        int cost = x.cost;
        int fuel_left =x.fuel_left;
       
        if(u==dest) {
            return cost;
        }
        if(fuel_left+1<=capacity and key[u][fuel_left+1]>key[u][fuel_left]+price[u]){
            key[u][fuel_left+1]=key[u][fuel_left]+price[u];
            pq.push(node(u,fuel_left+1,key[u][fuel_left]+price[u]));
        }

        for(auto v : adj[u]){
            
            if(fuel_left>=v.distance and key[v.vertex][fuel_left-v.distance]>cost)
            {   
                key[v.vertex][fuel_left-v.distance]=cost;
                pq.push(node(v.vertex,fuel_left-v.distance,cost));
            }
        }       
    }
    return INF;
   

}

int main(){
    int n,m,c;
    cin>>n>>m>>c;
    vector<int> price(n+1);

    for(int i=1; i<=n; i++){

        cin>>price[i];
    }
    vector<vector<edge>> adj(n+1);

    for(int i=0; i<m; i++){
     int u,v,w;
     cin>>u>>v>>w;
     adj[u].push_back(edge(v,w));
     adj[v].push_back(edge(u,w));
    }
    int src, dest;
    cin>>src>>dest;

    int ans = min_cost(n,m,c,price,adj,src,dest);
    if(ans==INF) cout<<"impossible"<<endl;
    else cout<<ans<<endl;    
}

