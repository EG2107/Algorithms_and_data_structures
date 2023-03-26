#include<iostream>
#include<vector>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    const int N = 3e7;
    vector<bool> prime(N, true);
    freopen("prime.txt", "w", stdout);

    for (int i = 2; i * i <= N; ++i){
        if (prime[i]){
            for (int j = i * i; j < N; j += i){
                prime[j] = false;
            }
        }
    }

    for (int i = 2; i < N; ++i){
        if (prime[i] == true){
            cout << i << "\n";
        }
    }

    return 0;
}