#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    cin >> s;
    int n = s.length();
    vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i){
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]){
            j = pi[j - 1];
        }
        if (s[i] == s[j]){
            j++;
        }
        pi[i] = j;
    }

    for (int i : pi){
        cout << i << " ";
    }

    return 0;
}