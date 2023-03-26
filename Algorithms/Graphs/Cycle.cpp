#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int cycle_st = -1, cycle_end = -1;

bool dfs(int v, vector<int> &p, vector<int> &mark, vector<vector<int>> &g){
    mark[v] = 1;
    for (int to : g[v]){
        if (mark[to] == 0){
            p[to] = v;
            if (dfs(to, p, mark, g)){
                return true;
            }
        } else if (mark[to] == 1){
            cycle_end = v;
            cycle_st = to;
            return true;
        }
    }
    mark[v] = 2;
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> mark(n, 0), p(n, -1);
    vector<vector<int>> g(n, vector<int>(0));

    int u_node, v_node;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node;
        u_node--;
        v_node--;
        g[u_node].push_back(v_node);
    }

    for (int i = 0; i < n; ++i){
        if (dfs(i, p, mark, g)){
            break;
        }
    }

    if (cycle_st == -1){
        cout << "NO";
    } else {
        vector<int> cycle(0);
        for (int v = cycle_end; v != cycle_st; v = p[v]){
            cycle.push_back(v);
        }
        cycle.push_back(cycle_st);
        reverse(cycle.begin(), cycle.end());

        cout << "YES\n";
        for (int i : cycle){
            cout << i + 1 << " ";
        }
    }

    return 0;
}