#include<bits/stdc++.h>
using namespace std;

#define INF 1e7+8

struct island{
    string name;
    int toll;
};




 unordered_map<string, int> dijsktra(int v, int e, set<string>& island_names, unordered_map<string, vector<pair<string,int>>>& adj,  string start) {

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, int> dist;
   
    for(auto it: island_names){
        dist[it] = INF;
    }

    dist[start] = 0;
    pq.push({0, start});


    while (!pq.empty()) {
        string parent = pq.top().second;
        int curr_time = pq.top().first;

        pq.pop();
        
        cout<<"result :"<<endl;
        cout<<parent<<" "<<curr_time<<endl;


        for(auto it : adj[parent]){

            string child = it.first;
            int toll = it.second;
            int total_time = curr_time + toll;

        
            
            if (total_time < dist[child]) {

            cout<<parent<<" "<<child<<" "<<total_time<<endl;
                dist[child] = total_time;
                //cout<<dist[child]<<" "<<endl;
                pq.push({total_time, child});
            }
        }
    }
    // cout<<dist["Njy"];

    for(auto x: island_names){
        cout<<x<<" "<<dist[x]<<endl;
    }
     

    return dist;

}


int main(){
    int v1, e1;
    cin>>v1>>e1;

    int v2, e2;
    cin>>v2>>e2;

   // getchar();

    unordered_map<string, vector<pair<string,int>>> adj1(v1+1);
    set<string> island_names1;


    for(int i=0;i<e1;i++){
        string src, dest;
        int wt;
        cin>>src>>dest>>wt;
       // getchar();
        adj1[src].push_back({dest,wt});
        adj1[dest].push_back({src,wt});
        island_names1.insert(src);
        island_names1.insert(dest);
    }


    unordered_map<string, vector<pair<string,int>>> adj2(v2+1);
    set<string> island_names2;

    for(int i=0;i<e2;i++){
        string src, dest;
        int wt;
        cin>>src>>dest>>wt;
       // getchar();
        adj2[src].push_back({dest,wt});
        adj2[dest].push_back({src,wt});
        island_names2.insert(src);
        island_names2.insert(dest);
    }
    int k;
    cin>>k;
    vector<pair<string,int>> islands1(k+1);
    for(int i=0;i<k;i++){
        string name;
        int toll;
        cin>>name>>toll;
       // getchar();  
        islands1[i].first = name;
        islands1[i].second = toll;
    }




    int n;
    cin>>n;
    vector<pair<string,int>> islands2(n+1);

    for(int i=0; i<n; i++){
        string name;
        int toll;
        cin>>name>>toll;
       // getchar();
        islands2[i].first = name;
        islands2[i].second = toll;
    }
    
    string start, end;
    cin>>start>>end;
    

    unordered_map<string, int> dist1 = dijsktra(v1, e1, island_names1, adj1, start);

    cout<<",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";
    unordered_map<string, int> dist2 = dijsktra(v2, e2, island_names2, adj2, end);
   
    int _min1 =INF;
    for(auto  x: islands1){

        _min1=min(_min1,dist1[x.first]);
    }
    
    cout<<_min1<<endl;

    int _min2 =INF;

    for(auto x: islands2){

        _min2=min(_min2,dist2[x.first]);
    }
     cout<<"hi"<<endl;
     cout<<_min2<<endl;


   
}
