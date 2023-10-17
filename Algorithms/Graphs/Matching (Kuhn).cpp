#include<iostream>
#include<vector>
using namespace std;

bool try_kuhn(int v, int iter, vector<vector<int>> &g, vector<int> &mt, vector<int> &used){
    if (used[v] == iter){
        return false;
    }
    used[v] = iter;

    for (int u : g[v]){
        if (mt[u] == -1){
            mt[u] = v;
            return true;
        }
    }

    for (int u : g[v]){
        if (try_kuhn(mt[u], iter, g, mt, used)){
            mt[u] = v;
            return true;
        }
    }

    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(0));
    for (int v = 0; v < n; ++v){
        int u;
        while ((cin >> u) && u){
            g[v].push_back(u - 1);
        }
    }

    vector<int> mt(m, -1);
    vector<int> used(n, -1);
    for (int v = 0; v < n; ++v){
        try_kuhn(v, v, g, mt, used);
    }

    int cnt = 0;
    for (int v = 0; v < m; ++v){
        if (mt[v] != -1){
            cnt++;
        }
    }
    cout << cnt << "\n";
    for (int v = 0; v < m; ++v){
        if (mt[v] != -1){
            cout << mt[v] + 1 << " " << v + 1 << "\n";
        }
    }

    return 0;
}