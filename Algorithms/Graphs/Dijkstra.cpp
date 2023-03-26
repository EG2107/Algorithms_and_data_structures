#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 2e9;

vector<int> dijkstra(int s, int n, vector<vector<pair<int, int>>> &g){
    vector<int> d(n, INF);
    vector<bool> used(n, false);
    d[s] = 0;

    for (int i = 0; i < n; ++i){
        int v = -1;
        for (int j = 0; j < n; ++j){
            if (!used[j] && (v == -1 || d[j] < d[v])){
                v = j;
            }
        }
        if (d[v] == INF){
            break;
        }
        used[v] = true;

        for (int j = 0; j < g[v].size(); ++j){
            int to = g[v][j].first, len = g[v][j].second;
            if (d[v] + len < d[to]){
                d[to] = d[v] + len;
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
    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>(0));

    int u_node, v_node, dist;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node >> dist;
        u_node--;
        v_node--;
        g[u_node].push_back({v_node, dist});
        g[v_node].push_back({u_node, dist});
    }

    vector<int> d = dijkstra(0, n, g);
    for (int i : d){
        cout << i << " ";
    }

    return 0;
}