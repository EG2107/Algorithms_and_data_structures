#include<iostream>
#include<vector>
using namespace std;

int logn;
vector<vector<int>> g, up;
vector<bool> used;

void dfs(int v, int p){
    used[v] = true;
    up[v][0] = p;
    for (int i = 1; i <= logn; ++i){
        up[v][i] = up[up[v][i-1]][i-1];
    }
    for (int to : g[v]){
        if (!used[to] && to != p){
            dfs(to, v);
        }
    }
}

int LA(int v, int k){
    if (k == 0){
        return v;
    }
    int logk = __lg(k);
    if (k > 0 && logk <= logn){
        return LA(up[v][logk], k - (1 << logk));
    }
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    logn = __lg(n);
    g.resize(n, vector<int>(0));
    up.resize(n, vector<int>(logn+1, 0));
    used.resize(n, false);

    int u_node, v_node;
    for (int i = 1; i < n; ++i){
        cin >> u_node >> v_node;
        u_node--; v_node--;
        g[u_node].push_back(v_node);
        g[v_node].push_back(u_node);
    }
    dfs(0, 0);

    int m, v, k;
    cin >> m;
    while (m--){
        cin >> v >> k;
        cout << LA(v-1, k)+1 << "\n";
    }

    return 0;
}