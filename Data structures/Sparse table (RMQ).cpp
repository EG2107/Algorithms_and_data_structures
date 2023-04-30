#include<iostream>
#include<vector>
using namespace std;

struct sparse_table {
    vector<vector<int>> mn;

    sparse_table(const vector<int> &a) {
        int n = a.size();
        mn.resize(__lg(n) + 1, vector<int>(n, 2e9));
        for (int i = 0; i < n; ++i){
            mn[0][i] = a[i];
        }
        for (int l = 0; l < __lg(n); l++){
            for (int i = 0; i + (2 << l) <= n; i++){
                mn[l + 1][i] = min(mn[l][i], mn[l][i + (1 << l)]);
            }
        }
    }

    int rmq(int l, int r){
        int t = __lg(r - l);
        return min(mn[t][l], mn[t][r - (1 << t)]);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    sparse_table sp_table(a);

    int l, r;
    while (m--){
        cin >> l >> r;
        l--;
        cout << sp_table.rmq(l, r) << "\n";
    }

    return 0;
}