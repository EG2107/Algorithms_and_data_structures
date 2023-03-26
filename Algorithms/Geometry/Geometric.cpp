#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

const long double PI = 3.14159265358979323846;

struct Point{
    int x, y;
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
};

struct Vector{
    int x, y;
    Vector() = default;
    Vector(int x, int y) : x(x), y(y) {}
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}

    Vector operator+(Vector a){
        return Vector(x + a.x, y + a.y);
    }

    Vector operator*(int a){
        return Vector(x * a, y * a);
    }
};

struct Line{
    int A, B, C;
    Line() = default;
    Line(int A, int B, int C) : A(A), B(B), C(C) {}
    Line(Point a, Point b) : A(b.y - a.y), B(a.x - b.x), C(b.x * a.y - a.x * b.y) {}
};

struct Triangle{
    Point a, b, c;
    Triangle() = default;
    Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {}
};

int dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y;
}

int cross(Vector a, Vector b){
    return a.x * b.y - b.x * a.y;
}

long double angle(Vector a, Vector b){
    return atan2(cross(a, b), dot(a, b));
}

long double len(Vector a){
    return sqrt(a.x * a.x + a.y * a.y);
}

long double dist(Point a, Line l){
    return abs(l.A * a.x + l.B * a.y + l.C) / sqrt(l.A * l.A + l.B * l.B);
}

Line normal(Line l){
    return Line(-l.B, l.A, 0);
}

long double S(Triangle tr){
    return (long double)abs((tr.b.x - tr.a.x) * (tr.c.y - tr.a.y) - (tr.c.x - tr.a.x) * (tr.b.y - tr.a.y)) / 2;
}

pair<long double, long double> intersect(Line l1, Line l2){
    return {(long double)(l1.B * l2.C - l2.B * l1.C) / (l1.A * l2.B - l2.A * l1.B), -(long double)(l1.A * l2.C - l2.A * l1.C) / (l1.A * l2.B - l2.A * l1.B)};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << fixed << showpoint;
    cout << setprecision(15);

    return 0;
}