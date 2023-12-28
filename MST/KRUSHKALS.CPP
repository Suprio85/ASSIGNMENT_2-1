#include<bits/stdc++.h>
using namespace std;

struct edge{
    int src;
    int des;
    
    float wt;

    edge(int src, int des, float wt){
        this->src=src;
        this->des=des;
        this->wt=wt;
    }

    edge(){
    }
};

bool compare(edge a, edge b){
    return a.wt<b.wt;
}


int find(int v, vector<int> & parent){
    if(parent[v]<=-1) return v;

     return parent[v]=find(parent[v],parent); 
}

void _union(int from, int to, vector<int>& parent){

    if(parent[from]<parent[to])
        parent[to]=from;
    else if(parent[from]>parent[to])
        parent[from]=to;
    else{
        parent[to]=from;
        parent[from]--;
    }

}


int main(){
    int v, e;
    float k;
    cin>>v>>e>>k;

    vector<edge> Edge(e);

    for(int i=0; i<e; i++){
        int src, des, wt;
        cin>>src>>des>>wt;
        if(wt>k) 
        Edge[i]=edge(src,des,k);
        else
        Edge[i]=edge(src,des,wt);
    }

    vector<int> parent(v,-1);
    sort(Edge.begin(),Edge.end(),compare);

    float wt;

    int i=0; int j=0;
    while(i<e and j<=v-1){
        int from = find(Edge[i].src,parent);
        int to = find(Edge[i].des,parent);

        if(from!=to){
            _union(from,to,parent);
            wt+=Edge[i].wt;
            j++;
        }
        i++;
    }


    cout<<wt<<endl;


}
