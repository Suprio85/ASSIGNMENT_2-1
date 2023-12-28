#include<bits/stdc++.h> 
using namespace std;

struct edge
{
     int src;
     int des;
     int wt;

    edge(int src, int des, int wt)
    {
        this->src = src;
        this->des = des;
        this->wt = wt;
    }

    edge(){
    }
};

int find(int v , vector<int>&parent){
    if(parent[v]<=-1) return v;
    else return parent[v]=find(parent[v],parent);
}


void _union(int from, int to, vector<int>&parent){
    if(parent[from]<parent[to]) parent[to]=from;
    else if(parent[from]>parent[to]) parent[from]=to;
    else{
        parent[to]=from;
        parent[from]--;
    }
}

bool compare(edge a, edge b){
    return a.wt<b.wt;
}


int main(){
    int v;
    cin>>v;
  vector<pair<int,int>> point(v);

  for(int i=0; i<v; i++){
    cin>>point[i].first>>point[i].second;
  }

    vector<edge> Edge;;
    for(int i=0; i<v; i++){
        for(int j=i+1; j<v; j++){
            int wt =abs(point[i].first-point[j].first)+abs(point[i].second-point[j].second);
            Edge.push_back(edge(i,j,wt));
        }
    }

    int size = Edge.size();

    sort(Edge.begin(),Edge.end(),compare);

    vector<int> parent(v+1,-1);

    int i=0;
    int j=0;
    int wt=0;

    while(i<v-1 and j<size){
        int from_parent = find(Edge[j].src,parent);
        int to_parent = find(Edge[j].des,parent);

        if(from_parent!=to_parent){
            _union(from_parent,to_parent,parent);
            wt+=Edge[j].wt;
            i++;
        }
        j++;
    }
    cout<<wt<<endl;







   


}