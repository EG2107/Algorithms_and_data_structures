#include<iostream>
#include<vector>
using namespace std;

const int maxn = 5e4;
const int INF = 2e9;

vector<pair<int, int>> g[maxn], mn[maxn];
bool used[maxn];
int s[maxn];

void sizes(int v, int p = -1){
    s[v] = 1;
    for (auto to : g[v]){
        int u = to.first;
        if (u != p && !used[u]){
            sizes(u, v);
            s[v] += s[u];
        }
    }
}

int centroid(int v, int p, int n){
    for (auto to : g[v]){
        int u = to.first;
        if (u != p && !used[u] && s[u] > n / 2){
            return centroid(u, v, n);
        }
    }
    return v;
}

void dfs(int v, int p, int p_v){
    for (auto to : g[v]){
        int u = to.first;
        if (u != p && !used[u]){
            mn[u].push_back({p_v, min(to.second, mn[v].back().second)});
            dfs(u, v, p_v);
        }
    }
}

void solve(int v){
    sizes(v);
    mn[v].push_back({v, INF});
    dfs(v, -1, v);

    used[v] = 1;
    for (auto to : g[v]){
        int u = to.first;
        if (!used[u]){
            solve(centroid(u, v, s[u]));
        }
    }
}

int query(int v, int u){
    int i = 0;
    for (; i < min(mn[v].size(), mn[u].size()); ++i){
        if (mn[v][i] != mn[u][i]){
            return min(mn[v][i].second, mn[u][i].second);
        }
    }
    return min(mn[v][i].second, mn[u][i].second);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    cin >> n;
    int v, u, weight;
    for (v = 1; v < n; ++v){
        cin >> u >> weight;
        u--;
        g[v].push_back({u, weight});
        g[u].push_back({v, weight});
    }

    solve(centroid(0, -1, n));

    int m;
    cin >> m;
    while (m--){
        cin >> v >> u;
        v--; u--;
        cout << query(v, u) << "\n";
    }
    
    return 0;
}