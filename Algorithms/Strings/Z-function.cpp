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
    vector<int> z(n, 0);

    int l = 0, r = 0;
    for (int i = 1; i < n; ++i){
        if (i <= r){
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]){
            z[i]++;
        }
        if (i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i : z){
        cout << i << " ";
    }

    return 0;
}