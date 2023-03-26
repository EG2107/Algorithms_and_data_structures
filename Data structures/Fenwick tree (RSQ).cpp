#include<iostream>
#include<vector>
#include<string>
using namespace std;

int sum(int r, vector<int> &t){
    int res = 0;
    for (; r > 0; r -= r & -r){
        res += t[r];
    }
    return res;
}

int sum(int l, int r, vector<int> &t){
    return sum(r, t) - sum(l - 1, t);
}

void add(int k, int x, int n, vector<int> &t){
    for (; k <= n; k += k & -k){
        t[k] += x;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }

    vector<int> t(n + 1, 0);
    for (int i = 0; i < n; ++i){
        add(i + 1, a[i], n, t);
    }

    string q_type;
    int l, r, pos, x;
    while (cin >> q_type){
        if (q_type == "sum"){
            cin >> l >> r;
            cout << sum(l, r, t) << "\n";
        } else if (q_type == "set"){
            cin >> pos >> x;
            add(pos, x - a[pos-1], n, t);
            a[pos-1] = x;
        }
    }

    return 0;
}