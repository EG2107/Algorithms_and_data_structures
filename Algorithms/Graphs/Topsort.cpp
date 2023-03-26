#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> ans;
bool no_cycles = true;

void dfs(int v, vector<int> &mark, vector<vector<int>> &g){
    mark[v] = 1;
    for (int to : g[v]){
        if (mark[to] == 0){
            dfs(to, mark, g);
        } else if (mark[to] == 1){
            no_cycles = false;
        }
    }
    ans.push_back(v);
    mark[v] = 2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> mark(n, 0);
    vector<vector<int>> g(n, vector<int>(0));

    int u_node, v_node;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node;
        u_node--;
        v_node--;
        g[u_node].push_back(v_node);
    }

    for (int i = 0; i < n; ++i){
        if (mark[i] == 0){
            dfs(i, mark, g);
        }
    }
    if (no_cycles){
        reverse(ans.begin(), ans.end());
        for (int i : ans){
            cout << i + 1 << " ";
        }
    } else {
        cout << -1;
    }

    return 0;
}