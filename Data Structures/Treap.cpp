#include<iostream>
using namespace std;

struct item {
    int key, prior;
    item *left, *right;
    item(){}
    item(int key, int prior) : key(key), prior(prior), left(nullptr), right(nullptr) {}
};

void split(item* t, int key, item* &l, item* &r){
    if (!t){
        l = r = nullptr;
    } else if (key < t->key){
        split(t->left, key, l, t->left);
        r = t;
    } else {
        split(t->right, key, t->right, r);
        l = t;
    }
}

void insert(item* &t, item* it){
    if (!t){
        t = it;
    } else if (it->prior > t->prior){
        split(t, it->key, it->left, it->right);
        t = it;
    } else {
        if (it->key < t->key){
            insert(t->left, it);
        } else {
            insert(t->right, it);
        }
    }
}

void merge(item* &t, item* l, item* r){
    if (!l || !r){
        t = l ? l : r;
    } else if (l->prior > r->prior){
        merge(l->right, l->right, r);
        t = l;
    } else {
        merge(r->left, l, r->left);
        t = r;
    }
}

void erase(item* & t, int key){
    if (t->key == key){
        merge(t, t->left, t->right);
    } else {
        if (key < t->key){
            erase(t->left, key);
        } else {
            erase(t->right, key);
        }
    }
}

item* unite(item* l, item* r){
    if (!l || !r){
        return l ? l : r;
    }
    if (l->prior < r->prior){
        swap(l, r);
    }
    auto lt = new item, rt = new item;
    split(r, l->key, lt, rt);
    l->left = unite(l->left, lt);
    l->right = unite(l->right, rt);
    return l;
}

void print(item* &t){
    if (!t){
        return;
    }
    print(t->left);
    cout << t->key << " ";
    print(t->right);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    srand(time(NULL));

    int n;
    cin >> n;
    int tmp;
    cin >> tmp;
    auto treap = new item(tmp, rand());
    for (int i = 1; i < n; ++i){
        cin >> tmp;
        insert(treap, new item(tmp, rand()));
    }
    print(treap);

    return 0;
}