#include<bits/stdc++.h>
using namespace std;

struct edge{
int src;
int dest;
int wt;

edge(){
}

edge(int src, int des, int wt){
this->src=src;
this->dest=des;
this->wt=wt;
}

};


int find(int v, vector<int>&parent){
if(parent[v]<=-1) return v;
return parent[v] =find(parent[v],parent);
}

bool compare(edge a ,edge b){
 return a.wt<b.wt;
}


void _union(int from, int to, vector<int>&parent){
 if(parent[from]<parent[to])
    parent[to]=from;

 else if(parent[to]>parent[from]){
    parent[from]=to;
 }

 else
    parent[to]=from;
     parent[from]--;
}

int main(){
int v;
cin>>v;

vector<pair<int,int>> points(v);
vector<edge> edges(v);

for(int i=0; i<v; i++){
        cin>> points[i].first>>points[i].second;
}

for(int i=0; i<v; i++){
    for(int j=i+1;j<v; j++)
    {
        int wt =abs(points[i].first-points[j].first)+abs(points[i].second-points[j].second);
       edges.push_back(edge(i,j,wt));

    }
}

sort(edges.begin(),edges.end(),compare);

vector<int> parent(v,-1);


int i=0;
int j=0;
int w=0;

int e =edges.size();

while(i<e and j<v-1){
    int from =find(edges[i].src,parent);
    int to =find(edges[i].dest,parent);

    if(from!=to){
            _union(from,to,parent);
            w+=edges[i].wt;
            j++;
    }
    i++;
}

cout<<w<<endl;

}



