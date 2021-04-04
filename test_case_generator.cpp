#include <bits/stdc++.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
typedef long double big_pp;

typedef struct Point {
    big_pp x;
    big_pp y;
    Point(big_pp _x, big_pp _y) {
        x = _x;
        y = _y;
    }

    bool operator<(const Point& p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
} Point;

vector<Point> rotatePoints(const vector<Point>& points, float angle) {
    vector<Point> rotatedPoints;
    float precos = cos(angle);
    float presin = sin(angle);
    for (const Point& p : points) {
        float x = precos * p.x - presin * p.y;
        float y = presin * p.x + precos * p.y;
        rotatedPoints.push_back(Point(x, y));
    }
    return rotatedPoints;
}

int main(int argc, char const* argv[]) {
    int n = atoi(argv[1]);  // penalization factor
    srand(time(NULL));

    // freopen(argv[2], "w", stdout);
    // cout << (2 * n + 1) << '\n';
    // cout << n << '\n';

    // int x = rand() % 50;
    int x = 50;

    /* IMPORTTANT */
    vector<Point> points;
    // for (int i = (-x); i <= x; ++i) {
    for (int i = 1; i <= 2 * x + 1; ++i) {
        points.push_back(Point(i, log(i)));
        // x^3 Function
        // points.push_back(Point(i, pow(i, 3)));

        // 10000sin(100x) Function
        // points.push_back(Point(i, 10000 * sin(100 * i)));

        // Normal Function
        // double exp_value = exp(-1 * (i * i) / 1e4);
        // points.push_back(Point(i, 100000 * exp_value));

        // xsinx Function
        // points.push_back(Point(i, 1000 * i * sin(i)));

        // x * |sin(x)| Function
        // points.push_back(Point(i, 10 * i * fabs(sin(i))));

        // |x| * sin(x) Function
        // points.push_back(Point(i, 10 * fabs(i) * sin(i)));

        // c / x (c=100) Function
        // if (i != 0)
        //     points.push_back(Point(i, 100 / i));

        // values from 0-5000
        // int x = rand() % 500;
        // int y = rand() % 500;

        // cout << (x + i * 10) << ' ' << (x + i) * (x + i) << '\n';
        // cout << ((-x) + i * 10) << ' ' << pow((-x) + i * 10, 3) << '\n';
    }
    // points = rotatePoints(points, (3.1415926535 / 4));

    // for (int i = 1; i <= n; ++i) {
    //     // values from 0-5000
    //     // int x = rand() % 500;
    //     // int y = rand() % 500;

    //     cout << (x + i * 10) << ' ' << (x + i) * (x + i) << '\n';
    //     // cout << ((-x) + i * 10) << ' ' << pow((-x) + i * 10, 3) << '\n';
    // }

    // for (int i = 0; i <= n; i++) {
    //     // values from 0-5000
    //     // int x = rand() % 500;
    //     // int y = rand() % 500;

    //     // cout << (x + i * 10) << ' ' << (x + i) * (x + i) << '\n';
    //     cout << (x + i * 10) << ' ' << pow(x + i * 10, 3) << '\n';
    // }

    /* IMPORTANT */
    freopen(argv[2], "w", stdout);
    cout << points.size() << '\n';
    for (unsigned int i = 0; i < points.size(); ++i) {
        cout << points[i].x << " " << points[i].y << '\n';
    }

    // cout << rand() % 100 << '\n';
    // cout << 0.01 << '\n';
    // cout << n << '\n';
    cout << pow(10, n) << '\n';
    fclose(stdout);
    return 0;
}