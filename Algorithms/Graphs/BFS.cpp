#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int INF = 2e9;

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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(0));
    int u_node, v_node;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node;
        u_node--;
        v_node--;
        g[u_node].push_back(v_node);
        g[v_node].push_back(u_node);
    }

    vector<int> d = bfs(0, n, g);
    for (auto i : d){
        if (i != INF){
            cout << i << " ";
        } else {
            cout << -1 << " ";
        }
    }

    return 0;
}