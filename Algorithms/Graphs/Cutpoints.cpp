#include<iostream>
#include<vector>
#include<set>
using namespace std;

int timer = 0;
set<int> cutpoints;

void dfs(int v, int p, vector<bool> &used, vector<int> &tin, vector<int> &fup, vector<set<int>> &g){
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;

    for (int to : g[v]){
        if (to != p){
            if (used[to]){
                fup[v] = min(fup[v], tin[to]);
            } else {
                dfs(to, v, used, tin, fup, g);
                fup[v] = min(fup[v], fup[to]);
                if (fup[to] >= tin[v] && p != -1){
                    cutpoints.insert(v);
                }
                children++;
            }
        }
    }

    if (p == -1 && children > 1){
        cutpoints.insert(v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<set<int>> g(n);
    int u_node, v_node;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node;
        u_node--;
        v_node--;
        g[u_node].insert(v_node);
        g[v_node].insert(u_node);
    }

    vector<bool> used(n, false);
    vector<int> tin(n), fup(n);
    for (int i = 0; i < n; ++i){
        if (!used[i]){
            dfs(i, -1, used, tin, fup, g);
        }
    }

    cout << cutpoints.size() << "\n";
    for (int i : cutpoints){
        cout << i + 1 << " ";
    }

    return 0;
}