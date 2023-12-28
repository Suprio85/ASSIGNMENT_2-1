#include<bits/stdc++.h>
using namespace std;

struct airport {
    string name;
    int layover;
};

struct state {
    int time;
    string last;
};

void dijsktra(int v, int e, unordered_map<string, vector<pair<string,int>>> adj, unordered_map<string, airport> airports, string start, string end) {

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, int> dist;
    unordered_map<string, state> stateInfo;

    pq.push({0, start});
    dist[start] = 0;
    stateInfo[start] = {0, ""};

    while (!pq.empty()) {
        string parent = pq.top().second;
        int curr_time = pq.top().first;
//    cout<<"result :"<<endl;
//         cout<<parent<<endl;
//         cout<<curr_time<<endl;

        pq.pop();

        for (auto it : adj[parent]) {
            string child = it.first;
            int layover = airports[child].layover;
            int total_time = curr_time + layover + it.second;

            if ( !stateInfo.count(child) || total_time < stateInfo[child].time) {
                stateInfo[child] = {total_time, parent};
                dist[child] = total_time;
                pq.push({total_time, child});
            }
        }
    }

    if (!stateInfo.count(end)) {
        cout << -1 << endl;
        return;
    }

    cout << dist[end] << endl;

    stack<string> path;
    string curr = end;
    cout<< end << endl;
  //  cout<<"......................................................."<<endl;
    while (!curr.empty()) {
        path.push(curr);
        curr = stateInfo[curr].last;
    }
//  cout<<"......................................................."<<endl;
    while (!path.empty()) {
        cout << path.top() << " ->";
        path.pop();
    }

    cout << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    int v, e;
    cin >> v >> e;

    unordered_map<string, airport> airports;
    unordered_map<string, vector<pair<string,int>>> adj;

    for (int i = 0; i < v; i++) {
        string name;
        int layover;
        cin >> name >> layover;
        airports[name] = {name, layover};
    }

    for (int i = 0; i < e; i++) {
        string src, dest;
        int time;
        cin >> src >> dest >> time;
        adj[src].push_back({dest,time});
        adj[dest].push_back({src,time});
    }

     for (auto it : adj) {
        cout << it.first << " -> ";
        for (auto i : it.second) {
            cout << i.first << " "<<i.second<<", ";
        }
        cout << endl;
     }

    string start, end;
    cin >> start >> end;

    dijsktra(v, e, adj, airports, start, end);

    return 0;
}
