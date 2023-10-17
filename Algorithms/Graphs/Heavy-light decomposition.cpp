#include<iostream>
#include<vector>
using namespace std;

const int maxn = 1e6;
int timer = 0;

vector<int> g[maxn];
int s[maxn], p[maxn], tin[maxn], tout[maxn], w[maxn], head[maxn];
vector<int> et_weights;

struct segment_tree {
    vector<int> arr;
    vector<long long> tree;
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

    long long query(int v, int l, int r, int lx, int rx){
        if (r <= lx || rx <= l){
            return 0;
        } else if (lx <= l && r <= rx){
            return tree[v];
        } else {
            int m = (l + r) / 2;
            return query(2*v, l, m, lx, rx) + query(2*v + 1, m, r, lx, rx);
        }
    }

    long long query(int lx, int rx){
        return query(1, 0, n, lx, rx+1);
    }
};

void sizes(int v = 0){
    s[v] = 1;
    for (int &u : g[v]){
        p[u] = v;
        sizes(u);
        s[v] += s[u];
        if (s[u] > s[g[v][0]]){
            swap(u, g[v][0]);
        }
    }
}

void hld(int v = 0){
    tin[v] = timer++;
    et_weights.push_back(w[v]);
    for (int u : g[v]){
        head[u] = (u == g[v][0] ? head[v] : u);
        hld(u);
    }
    tout[v] = timer++;
    et_weights.push_back(w[v]);
}

bool ancestor(int v, int u){
    return tin[v] <= tin[u] && tin[u] <= tout[v];
}

void up(int &v, int &u, long long &ans, segment_tree &seg_tree){
    while (!ancestor(head[v], u)){
        ans += seg_tree.query(tin[head[v]], tin[v]);
        v = p[head[v]];
    }
}

long long get_sum(int v, int u, segment_tree &seg_tree){
    long long ans = 0;
    up(v, u, ans, seg_tree);
    up(u, v, ans, seg_tree);
    if (!ancestor(v, u)){
        swap(v, u);
    }
    ans += seg_tree.query(tin[v], tin[u]);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    cin >> n;
    for (int i = 0 ; i < n; ++i){
        cin >> w[i];
    }
    
    int v, u;
    for (v = 1; v < n; ++v){
        cin >> u;
        u--;
        g[u].push_back(v);
    }

    sizes();
    hld();
    segment_tree seg_tree(et_weights);

    int q;
    cin >> q;
    while (q--){
        cin >> v >> u;
        v--; u--;
        cout << get_sum(v, u, seg_tree) << "\n";
    }
    
    return 0;
}