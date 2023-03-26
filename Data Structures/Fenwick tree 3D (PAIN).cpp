#include<iostream>
#include<vector>
using namespace std;

int sum(int x, int y, int z, vector<vector<vector<int>>> &t){
    int res = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1){
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1){
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1){
                res += t[i][j][k];
            }
        }
    }
    return res;
}

int sum(int x0, int y0, int z0, int x, int y, int z, vector<vector<vector<int>>> &t){
    return sum(x, y, z, t) - sum(x0 - 1, y, z, t) - sum(x, y0 - 1, z, t) + sum(x0 - 1, y0 - 1, z, t) - sum(x, y,z0 - 1, t) + sum(x0 - 1, y, z0 - 1, t) + sum(x, y0 - 1, z0 - 1, t)  - sum(x0 - 1, y0 - 1, z0 - 1, t);
}

void add(int x, int y, int z, int delta, int n, vector<vector<vector<int>>> &t){
    for (int i = x; i < n; i = (i | (i + 1))){
        for (int j = y; j < n; j = (j | (j + 1))){
            for (int k = z; k < n; k = (k | (k + 1))){
                t[i][j][k] += delta;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<vector<vector<int>>> t(n+1, vector<vector<int>>(n+1, vector<int>(n+1, 0)));

    int type = 0;
    int x0, y0, z0, x, y, z, delta;
    while (type != 3){
        cin >> type;
        if (type == 1){
            cin >> x >> y >> z >> delta;
            add(x, y, z, delta, n, t);
        } else if (type == 2){
            cin >> x0 >> y0 >> z0 >> x >> y >> z;
            cout << sum(x0, y0, z0, x, y, z, t) << "\n";
        }
    }

    return 0;
}