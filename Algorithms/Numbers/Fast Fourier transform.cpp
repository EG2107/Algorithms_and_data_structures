#include<iostream>
#include<vector>
#include<complex>
#include<cmath>
using namespace std;
typedef complex<long double> base;

const long double PI = 3.14159265358979323846;

void fft(vector<base> &a, bool invert){
    int n = a.size();
    if (n == 1) return;

    vector<base> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j){
        a0[j] = a[i];
        a1[j] = a[i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    long double ang = 2 * PI / n * (invert ? -1 : 1);
    base w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; ++i){
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert){
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

void multiply(vector<int> &a, vector<int> &b, vector<int> &res){
    vector<base> fa(a.begin(), a.end()),  fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(), b.size())) n *= 2;
    n *= 2;
    fa.resize(n);
    fb.resize(n);
    res.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; ++i){
        fa[i] *= fb[i];
    }
    fft(fa, true);

    for (int i = 0; i < n; ++i){
        res[i] = lroundl(fa[i].real());
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n+1);
    for (int i = 0; i <= n; ++i){
        cin >> a[i];
    }

    int m;
    cin >> m;
    vector<int> b(m+1);
    for (int i = 0; i <= m; ++i){
        cin >> b[i];
    }

    vector<int> res;
    multiply(a, b, res);
    cout << n + m << " ";
    for (int i = 0; i <= n + m; ++i){
        cout << res[i] << " ";
    }

    return 0;
}