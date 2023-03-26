#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;

struct point {
    long long x, y;
};

bool compare(point a, point b){
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw(point a, point b, point c){
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool ccw(point a, point b, point c){
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

vector<point> convex_hull(vector<point> &a){
    if (a.size() == 1){
        return a;
    }
    sort(a.begin(), a.end(), compare);

    point p1 = a.front(), p2 = a.back();
    vector<point> up(0), down(0);
    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < a.size(); ++i){
        if (i == a.size() - 1 || cw(p1, a[i], p2)){
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i])){
                up.pop_back();
            }
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)){
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i])){
                down.pop_back();
            }
            down.push_back(a[i]);
        }
    }

    vector<point> res(0);
    for (int i = 0; i < up.size(); ++i){
        res.push_back(up[i]);
    }
    for (int i = down.size() - 2; i > 0; --i){
        res.push_back(down[i]);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << fixed << showpoint;
    cout << setprecision(15);

    vector<point> points(0);
    int n;
    cin >> n;
    point tmp;
    for (int i = 0; i < n; ++i){
        cin >> tmp.x >> tmp.y;
        points.push_back(tmp);
    }

    vector<point> res = convex_hull(points);

    cout << res.size() << "\n";
    for (point i : res){
        cout << (long long)(i.x) << " " << (long long)(i.y) << "\n";
    }

    long double area = 0;
    for (int i = 1; i < res.size(); ++i){
        area += abs((res[i].x - res[0].x) * (res[i - 1].y - res[0].y) - (res[i].y - res[0].y) * (res[i - 1].x - res[0].x));
    }
    cout << area / 2;

    return 0;
}