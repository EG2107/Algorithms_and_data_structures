#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> g;
vector<vector<pair<int, int>>> queries;
vector<int> dsu, dsu_rank, ancestor, ans;
vector<bool> used;

void dsu_make_set(int v){
    dsu[v] = v;
    dsu_rank[v] = 0;
}

int dsu_get(int v){
    return v == dsu[v] ? v : dsu[v] = dsu_get(dsu[v]);
}

void dsu_unite(int a, int b, int new_ancestor){
    a = dsu_get(a);
    b = dsu_get(b);
    if (dsu_rank[a] < dsu_rank[b]){
        swap(a, b);
    }
    dsu[a] = b;
    if (dsu_rank[a] == dsu_rank[b]){
        dsu_rank[a]++;
    }
    ancestor[b] = new_ancestor;
}

void dfs(int v){
    dsu[v] = v;
    ancestor[v] = v;
    used[v] = true;
    for (int to : g[v]){
        if (!used[to]){
            dfs(to);
            dsu_unite(v, to, v);
        }
    }

    for (pair<int, int> q : queries[v]){
        if (used[q.first]){
            ans[q.second] = ancestor[dsu_get(q.first)];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    g.resize(n, vector<int>(0));
    used.resize(n, false);
    queries.resize(n, vector<pair<int, int>>(0));
    dsu.resize(n);
    dsu_rank.resize(n);
    ancestor.resize(n);

    int v_node, u_node;
    for (v_node = 1; v_node < n; ++v_node){
        cin >> u_node;
        u_node--;
        g[u_node].push_back(v_node);
    }
    
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node;
        u_node--; v_node--;
        queries[u_node].push_back({v_node, i});
        queries[v_node].push_back({u_node, i});
    }

    ans.resize(m);
    dfs(0);

    for (int i : ans){
        cout << i+1 << "\n";
    }

    return 0;
}