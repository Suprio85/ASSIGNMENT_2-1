#include<bits/stdc++.h>
using namespace std;

bool is_cycle(int node, int v, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& parent, pair<int,int>& ans){
    visited[node] = true;

    cout<<"node :" <<node<<endl;

    for(auto x : adj[node]){
        cout<<"adj :";
        cout<<x<<endl;
        if(!visited[x]){
            parent[x] = node;

            cout<<"parent :" <<parent[x] << "node :" <<x<<endl;
            if(is_cycle(x, v, adj, visited, parent, ans)){
                return true;
            }
        }
        else if(parent[node] != x){
            cout<<"parent :" <<parent[x] <<" "<<node<<endl;
            ans = {x, node};
            cout<<x<<" "<<node<<endl;
            return true;
        }
    }

    return false;
}

bool detect_cycle(int v, int e, vector<vector<int>> adj, pair<int,int>& ans){
    vector<bool> visited(v+1, false);
    vector<int> parent(v+1, -1);

    for(int i=1; i<=v; i++){
        if(!visited[i]){
            if(is_cycle(i, v, adj, visited, parent, ans)){
                return true;
            }
        }
    }

    return false;
}

int main(){
    int no_nodes, no_edges;
    cin >> no_nodes >> no_edges;

    vector<vector<int>> adj(no_nodes+1);

    for(int i=0; i<no_edges; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pair<int, int> ans;

    if(detect_cycle(no_nodes, no_edges, adj, ans)){
        cout << "YES" << endl;
        cout << ans.first << " " << ans.second << endl;
    }
    else
        cout << "NO" << endl;

    return 0;
}
