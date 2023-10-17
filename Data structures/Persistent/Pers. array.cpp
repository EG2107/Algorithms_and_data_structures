#include<iostream>
#include<vector>
using namespace std;

struct node {
    int value;
    node* left;
    node* right;

    node(int value) : value(value), left(nullptr), right(nullptr) {}
    node(node* left, node* right) : value(left ? (left->value + right->value) : 0), left(left), right(right) {}
    node(int l, int r){
        if (l + 1 >= r) return;
        int m = (r + l) / 2;
        left = new node(l, m);
        right = new node(m, r);
    }
};

node* update(node* v, int l, int r, int ind, int x){
    if (l + 1 == r){
        return new node(x);
    }

    node* left = v->left;
    node* right = v->right;
    int m = (r + l) / 2;
    if (ind < m){
        left = update(left, l, m, ind, x);
    } else {
        right = update(right, m, r, ind, x);
    }
    return new node(left, right);
}

int query(node* v, int l, int r, int lx, int rx){
    if (r <= lx || rx <= l){
        return 0;
    }
    if (lx <= l && r <= rx){
        return v->value;
    }
    int m = (r + l) / 2;
    return query(v->left, l, m, lx, rx) + query(v->right, m, r, lx, rx);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, tmp;
    cin >> n;
    node* seg_tree = new node(0, n);
    for (int i = 0; i < n; ++i){
        cin >> tmp;
        seg_tree = update(seg_tree, 0, n, i, tmp);
    }
    vector<node*> versions = {seg_tree};

    int m;
    string q;
    int ver_ind, ind, x;
    cin >> m;
    while(m--){
        cin >> q >> ver_ind >> ind;
        ver_ind--;
        ind--;
        if (q == "get"){
            cout << query(versions[ver_ind], 0, n, ind, ind+1) << "\n";
        } else {
            cin >> x;
            versions.push_back(update(versions[ver_ind], 0, n, ind, x));
        }
    }

    return 0;
}