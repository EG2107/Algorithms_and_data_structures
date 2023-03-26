#include<iostream>
#include<vector>
using namespace std;

int cur_color = 1;

void dfs(int x, vector<int> &color, vector<vector<int>> &g){
    color[x] = cur_color;
    for (int i = 0; i < g[x].size(); ++i){
        if (color[g[x][i]] == 0){
            dfs(g[x][i], color, g);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> color(n, 0);
    vector<vector<int>> g(n, vector<int>(0));

    int u_node, v_node;
    for (int i = 0; i < m; ++i){
        cin >> u_node >> v_node;
        u_node--;
        v_node--;
        g[u_node].push_back(v_node);
        g[v_node].push_back(u_node);
    }

    for (int i = 0; i < n; ++i){
        if (color[i] == 0){
            dfs(i, color, g);
            cur_color++;
        }
    }

    for (int i = 0; i < n; ++i){
        cout << color[i] << " ";
    }
    
    return 0;
}