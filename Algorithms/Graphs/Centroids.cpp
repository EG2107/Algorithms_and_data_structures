#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void sizes(int v, int p, vector<vector<int>> &g, vector<int> &s, vector<bool> &used){
    s[v] = 1;
    for (int u : g[v]){
        if (u != p && !used[u]){
            sizes(u, v, g, s, used);
            s[v] += s[u];
        }
    }
}

int centroid(int v, int p, int n, vector<vector<int>> &g, vector<int> &s, vector<bool> &used){
    for (int u : g[v]){
        if (u != p && !used[u] && s[u] > n/2){
            return centroid(u, v, n, g, s, used);
        }
    }
    return v;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(0));
    int u_node, v_node;
    for (int i = 1; i < n; ++i){
        cin >> u_node >> v_node;
        u_node--; 
        v_node--;
        g[u_node].push_back(v_node);
        g[v_node].push_back(u_node);
    }

    vector<int> s(n, 0);
    vector<bool> used(n, false);
    vector<char> ans(n, 'Z');
    char cur_rank = 'A';
    int cnt = 0;
    queue<int> q1, q2;
    sizes(0, -1, g, s, used);
    int st = centroid(0, -1, n, g, s, used);
    q1.push(st);
    while (cnt < n){
        while (!q1.empty()){
            int cur = q1.front();
            q1.pop();
            sizes(cur, -1, g, s, used);
            int cur_centr = centroid(cur, -1, s[cur], g, s, used);
            if (!used[cur_centr]){
                ans[cur_centr] = cur_rank;  
                used[cur_centr] = true;
                cnt++;
                for (int v : g[cur_centr]){
                    if (!used[v]);
                    q2.push(v);
                }
            }
        }
        cur_rank++;
        swap(q1, q2);
    }
    
    for (char i : ans){
        cout << i << " ";
    }
    
    return 0;
}