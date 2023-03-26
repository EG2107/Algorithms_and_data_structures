#include<iostream>
#include<vector>
#include<string>
using namespace std;

const int k = 317;

struct Sqrt_decomposition {
    vector<int> a;
    vector<int> blocks;
    int n;

    Sqrt_decomposition(const vector<int> &a) : a(a) {
        n = a.size();
        blocks.resize((n + k - 1) / k, 0);
        for (int i = 0; i < n; ++i){
            blocks[i / k] += a[i];
        }
    }

    void update(int i, int v){
        blocks[i / k] += v - a[i];
        a[i] = v;
    }

    int sum(int l, int r) {
        int res = 0;
        while (l <= r) {
            if (l % k == 0 && l + k - 1 <= r) {
                res += blocks[l / k];
                l += k; 
            } else {
                res += a[l];
                l++;
            }
        }
        return res;
    }
};

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
    Sqrt_decomposition my_sqrtd(a);

    int pos, x, lx, rx;
    string q_type;
    while (cin >> q_type){
        if (q_type == "set"){
            cin >> pos >> x;
            pos--;
            my_sqrtd.update(pos, x);
        } else if (q_type == "sum"){
            cin >> lx >> rx;
            lx--;
            rx--;
            cout << my_sqrtd.sum(lx, rx) << "\n";
        }
    }

    return 0;
}