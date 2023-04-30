#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int INF = 2e9;
vector<int> order, dist;

struct sparse_table {
    vector<vector<pair<int, int>>> mn;

    sparse_table(const vector<int> &a) {
        int n = a.size();
        mn.resize(__lg(n) + 1, vector<pair<int, int>>(n, {INF, 0}));

        for (int i = 0; i < n; ++i){
            mn[0][i] = {a[i], i};
        }

        for (int l = 0; l < __lg(n); l++){
            for (int i = 0; i + (2 << l) <= n; i++){
                mn[l + 1][i] = min(mn[l][i], mn[l][i + (1 << l)]);
            }
        }
    }

    pair<int, int> rmq(int l, int r){
        int t = __lg(r - l);
        return min(mn[t][l], mn[t][r - (1 << t)]);
    }
};

void dfs(int v, int p, vector<bool> &used, vector<vector<int>> &g){
    used[v] = true;
    order.push_back(v);
    for (int to : g[v]){
        if (!used[to] && to != p){
            dfs(to, v, used, g);
        }
        order.push_back(v);
    }
    order.push_back(v);
}

vector<int> bfs(int s, int n, vector<vector<int>> &g){
    queue<int> q;
    q.push(s);
    vector<bool> used(n, false);
    vector<int> d(n, INF);
    used[s] = true;
    d[s] = 0;
    
    int v, to;
    while (!q.empty()){
        v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); ++i){
            to = g[v][i];
            if (!used[to]){
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    return d;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    int v_node, u_node;
    vector<vector<int>> g(n, vector<int>(0));
    for (v_node = 1; v_node < n; ++v_node){
        cin >> u_node;
        u_node--;
        g[u_node].push_back(v_node);
    }

    vector<bool> used(n, false);
    order.clear();
    dfs(0, 0, used, g);

    vector<int> first(order.size(), 0);
    vector<int> d = bfs(0, n, g);
    dist.resize(order.size());
    for (int i = 0; i < order.size(); ++i){
        dist[i] = d[order[i]];
        first[order[i]] = i;
    }
    sparse_table sp_table(dist);
    
    int m, left, right;
    cin >> m;
    while (m--){
        cin >> u_node >> v_node;
        u_node--; v_node--;
        left = first[u_node];
        right = first[v_node];
        if (left > right){
            swap(left, right);
        }
        cout << order[sp_table.rmq(left, right).second]+1 << "\n";
    }

    return 0;
}