#include<iostream>
#include<vector>
using namespace std;

struct Node {
    int value;
    Node* next = nullptr;
};

Node* push(Node* ver, int x){
    return new Node{x, ver};
}

Node* pop(Node* ver){
    return (ver ? ver->next : nullptr);
}

int top(Node* ver){
    return (ver ? ver->value : 0);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<Node*> a(n+1, nullptr);
    vector<int> sums(n+1, 0);
    for (int i = 1; i <= n; ++i){
        int t, m;
        cin >> t >> m;
        if (m){
            sums[i] = sums[t] + m;
            a[i] = push(a[t], m);
        } else {
            sums[i] = sums[t] - top(a[t]);
            a[i] = pop(a[t]);
        }
    }
    
    long long ans = 0;
    for (long long i : sums){
        ans += i;
    }
    cout << ans;

    return 0;
}