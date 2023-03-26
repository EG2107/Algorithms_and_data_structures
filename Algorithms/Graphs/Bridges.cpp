#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int timer = 0;
vector<int> bridges;

void dfs(int v, int p, vector<bool> &used, vector<int> &tin, vector<int> &fup, vector<vector<pair<int, int>>> &g){
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int i = 0; i < g[v].size(); ++i){
        int to = g[v][i].first;
        if (to != p){
            if (used[to]){
                fup[v] = min(fup[v], tin[to]);
            } else {
                dfs(to, v, used, tin, fup, g);
                fup[v] = min(fup[v], fup[to]);
                if (fup[to] > tin[v]){
                    bridges.push_back(g[v][i].second);
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>(0));
    int u_node, v_node;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node;
        u_node--;
        v_node--;
        g[u_node].push_back({v_node, i});
        g[v_node].push_back({u_node, i});
    }

    vector<bool> used(n, false);
    vector<int> tin(n), fup(n);
    for (int i = 0; i < n; ++i){
        if (!used[i]){
            dfs(i, -1, used, tin, fup, g);
        }
    }

    sort(bridges.begin(), bridges.end());
    cout << bridges.size() << "\n";
    for (int i : bridges){
        cout << i + 1 << " ";
    }

    return 0;
}