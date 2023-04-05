#include<iostream>
using namespace std;

void divs(int n){
    int div = 2;
    while (div * div <= n){
        while (n % div == 0){
            cout << div << " ";
            n /= div;
        }
        div++;
    }
    if (n > 1){
        cout << n;
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, a;
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> a;
        divs(a);
    }
    
    return 0;
}