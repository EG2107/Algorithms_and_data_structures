#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct lll {
    string num;
    int size;

    lll(string num) : num(num), size(num.size()) {}

    void resize(int sz){
        if (size < sz){
            string tmp = "";
            for (int i = 0; i < sz - size; ++i){
                tmp += '0';
            }
            num = tmp + num;
            size = sz;
        }
    }

    void multiply_10_x(int x){
        if (num != "0"){
            for (int i = 0; i < x; ++i){
                num += '0';
            }
            size += x;
        }
    }
};

lll operator+(lll a, lll b){
    int n = max(a.size, b.size);
    a.resize(n);
    b.resize(n);
    string res = "";
    res.resize(n);

    bool transfer = false;
    int cur_sum;
    for (int i = n-1; i >= 0; --i){
        cur_sum = a.num[i] + b.num[i] + transfer;
        if (cur_sum <= 105){
            transfer = false;
            res[i] = char(cur_sum - 48);
        } else {
            transfer = true;
            res[i] = char(cur_sum - 58);
        }
    }
    if (transfer){
        res = '1' + res;
    }
    return lll(res);
}

lll operator-(lll a, lll b){
    int n = max(a.size, b.size);
    a.resize(n);
    b.resize(n);
    if (a.num >= b.num){
        string res = "";

        bool transfer = false;
        int cur_diff;
        for (int i = n-1; i >= 0; --i){
            cur_diff = a.num[i] - b.num[i];
            if (transfer){
                cur_diff--;
            }
            if (cur_diff < 0){
                cur_diff += 10;
                transfer = true;
            } else {
                transfer = false;
            }
            res += char(cur_diff + 48);
        }
        while (res[res.size()-1] == '0' && res.size() > 1){
            res = res.substr(0, res.size()-1);
        }
        reverse(res.begin(), res.end());
        return lll(res);
    } else {
        return b - a;
    }
}

lll operator* (lll x, lll y){
    int n = max(x.size, y.size);
    x.resize(n);
    y.resize(n);
    if (n > 9){
        lll a(x.num.substr(0, n/2)), b(x.num.substr(n/2, n - n/2)), c(y.num.substr(0, n/2)), d(y.num.substr(n/2, n - n/2));
        lll ac(a * c), bd(b * d), adbc((a + b) * (c + d) - ac - bd);
        ac.multiply_10_x(2*(n - n/2));
        adbc.multiply_10_x(n - n/2);
        return ac + adbc + bd;
    }
    return lll(to_string(stoll(x.num) * stoll(y.num)));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string sa, sb;
    cin >> sa >> sb;
    bool negative = false;
    if (sa[0] == '-'){
        negative = !negative;
        sa = sa.substr(1, sa.size()-1);
    }
    if (sb[0] == '-'){
        negative = !negative;
        sb = sb.substr(1, sb.size()-1);
    }
    
    lll a(sa), b(sb);
    string res = (a * b).num;
    if (negative && res != "0"){
        cout << '-';
    }
    cout << res << "\n";

    return 0;
}