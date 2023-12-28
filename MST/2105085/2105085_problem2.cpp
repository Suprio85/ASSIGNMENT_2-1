#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int src;
    int des;
    int wt;
    int idx;


    edge(int src, int des, int wt)
    {
        this->src = src;
        this->des = des;
        this->wt = wt;

    }

    edge()
    {
    }
};

bool compare(edge a, edge b)
{
    return a.wt < b.wt;
}

int find(int v, vector<int> &parent)
{
    if (parent[v] <= -1)
        return v;
    else
        return parent[v] = find(parent[v], parent);
}

void _union(int from, int to, vector<int> &parent)
{
    if (parent[from] > parent[to])
        parent[to] = from;
    else if (parent[from] < parent[to])
        parent[from] = to;

    else
    {
        parent[to] = from;
        parent[from]--;
    }
}

void build_mst(int idx, int w, int &max_weight, int v, int e, vector<edge> edges, vector<int> parent, vector<edge> mst_sets, vector<int>& count ,int& no_of_mst)
{
    if (mst_sets.size() == v - 1)
    {

        if (w <= max_weight)
        {
            for (auto x : mst_sets)
            {
              //  cout << x.src << "  " << x.des << "  " << x.wt << endl;
                count[x.idx]++;
                
            }
            no_of_mst++;
          //  cout << w << endl;

            max_weight = w;
            return;
        }
    }

    vector<int> temp_parent;
    int i = idx;
    int sz = edges.size();

    while (i < sz and edges[i].wt == edges[idx].wt)
    {
        int from_parent = find(edges[i].src, parent);
        int to_parent = find(edges[i].des, parent);

        // cout << "u:" << edges[i].src << " v:" << edges[i].des << " wt:" << edges[i].wt << endl;
        // cout << "u_parent:" << from_parent << " v_parent:" << to_parent << endl;

        if (from_parent != to_parent)
        {

           //cout << "no cycle" << endl;

            temp_parent = parent;
            _union(from_parent, to_parent, parent);
            mst_sets.push_back(edges[i]);
            build_mst(i + 1, w + edges[i].wt, max_weight, v, e, edges, parent, mst_sets,count,no_of_mst);
            mst_sets.pop_back();
            parent = temp_parent;
        }

        else if (from_parent == to_parent)
        {
            //cout << "cycle" << endl;
            build_mst(i + 1, w, max_weight, v, e, edges, parent, mst_sets,count,no_of_mst);
        }
        i++;
    }
}

void find_all_msts(int v, int e, vector<edge> sorted_edges, vector<int> parent, vector<edge> mst_sets,vector<edge> edges)
{

    int max_weight = INT_MAX;
    int w = 0;
    int idx = 0;
    vector<int> count(e, 0);
    int no_of_mst = 0;

    build_mst(idx, w, max_weight, v, e, sorted_edges, parent, mst_sets,count,no_of_mst);

    for(auto x : edges){
        if(count[x.idx] == no_of_mst)
                cout<<"any"<<endl;
        else if(count[x.idx] == 0)
                cout<<"none"<<endl;
        else
                cout<<"at least one"<<endl;
    }
   
}

int main()
{
     //freopen("input.txt", "r", stdin);
    int v, e;
    cin >> v >> e;
    vector<edge> edges(e);
    vector<edge> sorted_edges(e);

     //freopen("output.txt", "w", stdout);

    for (int i = 0; i < e; i++)
    {
        int src, des, wt;
        cin >> src >> des >> wt;
        edges[i] = edge(src, des, wt);
        edges[i].idx = i;
    }

    sorted_edges = edges;

    sort(sorted_edges.begin(), sorted_edges.end(), compare);
    vector<int> parent(v+1, -1);
    vector<edge> mst_sets;
   // vector<string> result(e, "none");

    find_all_msts(v, e, sorted_edges, parent, mst_sets,edges);

    

    return 0;
}
