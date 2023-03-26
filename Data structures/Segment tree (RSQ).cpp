#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct segment_tree {
    vector<int> arr;
    vector<int> tree;
    int n;

    segment_tree(const vector<int> &arr) : arr(arr) {
        n = arr.size();
        tree.resize(4*n, 0);
        build(1, 0, n);
    }

    void build(int v, int l, int r){
        if (l + 1 == r){
            tree[v] = arr[l];
        } else {
            int m = (l + r) / 2;
            build(2*v, l, m);
            build(2*v + 1, m, r);
            tree[v] = tree[2*v] + tree[2*v + 1];
        }
    }

    void update(int v, int l, int r, int pos, int x){
        if (l + 1 == r){
            arr[l] = x;
            tree[v] = x;
        } else {
            int m = (l + r) / 2;
            if (pos < m){
                update(2*v, l, m, pos, x);
            } else {
                update(2*v + 1, m, r, pos, x);
            }
            tree[v] = tree[2*v] + tree[2*v + 1];
        }
    }

    void update(int pos, int x){
        update(1, 0, n, pos, x);
    }

    int query(int v, int l, int r, int lx, int rx){
        if (r <= lx || rx <= l){
            return 0;
        } else if (lx <= l && r <= rx){
            return tree[v];
        } else {
            int m = (l + r) / 2;
            return query(2*v, l, m, lx, rx) + query(2*v + 1, m, r, lx, rx);
        }
    }

    int query(int lx, int rx){
        return query(1, 0, n, lx, rx);
    }

    void print(){
        for (int i : tree){
            cout << i << " ";
        }
        cout << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, prev_n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }

    segment_tree seg_tree(a);
    string q_type;
    int pos, x, lx, rx;
    while (cin >> q_type){
        if (q_type == "set"){
            cin >> pos >> x;
            pos--;
            seg_tree.update(pos, x);
        } else if (q_type == "sum"){
            cin >> lx >> rx;
            lx--;
            cout << seg_tree.query(lx, rx) << "\n";
        }
    }
    
    return 0;
}