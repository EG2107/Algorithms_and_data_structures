#include<iostream>
#include<vector>
using namespace std;

bool try_kuhn(int v, vector<bool> &used, vector<int> &mt, vector<vector<int>> &g){
    if (used[v]){
        return false;
    }
    used[v] = true;
    for (int to : g[v]){
        if (mt[to] == -1 || try_kuhn (mt[to], used, mt, g)){
            mt[to] = v;
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
    for (int i = 0; i < n; ++i){
        int tmp;
        while (cin >> tmp && tmp){
            g[i].push_back(tmp-1);
        }
    }

    vector<int> mt(m, -1);
    vector<bool> used;
    for (int v = 0; v < n; ++v){
        used.assign(n, false);
        try_kuhn(v, used, mt, g);
    }

    int cnt = 0;
    for (int i = 0; i < m; ++i){
        if (mt[i] != -1){
            cnt++;
        }
    }

    cout << cnt << "\n";
    for (int i = 0; i < m; ++i){
        if (mt[i] != -1){
            cout << mt[i] + 1 << " " << i + 1 << "\n";
        }
    }

    return 0;
}