#include <bits/stdc++.h>
using namespace std;

typedef long double big_pp;

const big_pp eps = 0.0000000001;
typedef struct Point {
    big_pp x;
    big_pp y;
    Point(big_pp _x, big_pp _y) {
        x = _x;
        y = _y;
    }

    bool operator<(const Point &p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
} Point;

typedef struct Segment {
    big_pp x1;
    big_pp y1;
    big_pp x2;
    big_pp y2;
    Segment(big_pp _x1, big_pp _y1, big_pp _x2, big_pp _y2) {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }
} Segment;

vector<vector<vector<big_pp> > > computeLeastSquareErrors(const vector<Point> &points, unsigned int n) {
    // vector<big_pp> pre_X_sum, pre_Y_sum, pre_XY_sum, pre_X_2_sum, pre_Y_2_sum;
    // pre_X_sum = pre_Y_sum = pre_XY_sum = pre_X_2_sum = pre_Y_2_sum = {0.0};

    vector<big_pp> pre_X_sum = vector<big_pp>(n + 1, 0.0);
    vector<big_pp> pre_Y_sum = vector<big_pp>(n + 1, 0.0);
    vector<big_pp> pre_XY_sum = vector<big_pp>(n + 1, 0.0);
    vector<big_pp> pre_X_2_sum = vector<big_pp>(n + 1, 0.0);
    vector<big_pp> pre_Y_2_sum = vector<big_pp>(n + 1, 0.0);

    for (unsigned int i = 1; i <= n; ++i) {
        pre_X_sum[i] = (points[i - 1].x + pre_X_sum[i - 1]);
        pre_Y_sum[i] = (points[i - 1].y + pre_Y_sum[i - 1]);
        pre_XY_sum[i] = (points[i - 1].x * points[i - 1].y) + pre_XY_sum[i - 1];
        pre_X_2_sum[i] = (points[i - 1].x * points[i - 1].x) + pre_X_2_sum[i - 1];
        pre_Y_2_sum[i] = (points[i - 1].y * points[i - 1].y) + pre_Y_2_sum[i - 1];
    }

    vector<vector<big_pp> > pre_a(n + 1, vector<big_pp>(n + 1, 0.0));
    vector<vector<big_pp> > pre_b(n + 1, vector<big_pp>(n + 1, 0.0));
    vector<vector<big_pp> > leastSquareErrors(n + 1, vector<big_pp>(n + 1, 0.0));

    for (unsigned int i = 1; i <= n; ++i) {
        for (unsigned int j = 1; j < i; ++j) {
            unsigned int num = i - j + 1;

            big_pp X_sum_segment = pre_X_sum[i] - pre_X_sum[j - 1];
            big_pp Y_sum_segment = pre_Y_sum[i] - pre_Y_sum[j - 1];
            big_pp XY_sum_segment = pre_XY_sum[i] - pre_XY_sum[j - 1];
            big_pp X_2_sum_segment = pre_X_2_sum[i] - pre_X_2_sum[j - 1];
            big_pp Y_2_sum_segment = pre_Y_2_sum[i] - pre_Y_2_sum[j - 1];

            pre_a[j][i] = (((num * XY_sum_segment) - (X_sum_segment * Y_sum_segment)) / ((num * X_2_sum_segment) - (X_sum_segment * X_sum_segment)));
            pre_b[j][i] = (Y_sum_segment - pre_a[j][i] * X_sum_segment) / num;

            big_pp _a2x2 = pre_a[j][i] * pre_a[j][i] * X_2_sum_segment;
            big_pp _2axy = 2 * pre_a[j][i] * XY_sum_segment;
            big_pp _2by = 2 * pre_b[j][i] * Y_sum_segment;
            big_pp _nb2 = num * pre_b[j][i] * pre_b[j][i];
            big_pp _y2 = Y_2_sum_segment;
            big_pp _2abx = 2 * pre_a[j][i] * pre_b[j][i] * X_sum_segment;

            leastSquareErrors[j][i] = (_a2x2) - (_2axy) - (_2by) + (_nb2) + (_y2) + (_2abx);
        }
    }

    return {leastSquareErrors, pre_a, pre_b};
}

Point intersection(big_pp m1, big_pp c1, big_pp m2, big_pp c2) {
    return Point(((c1 - c2) / (m2 - m1)), ((c1 * m2 - c2 * m1) / (m2 - m1)));
}

pair<big_pp, vector<Segment> > segmentedLeastSquares(unsigned int n, vector<Point> points, big_pp c) {
    vector<vector<vector<big_pp> > > preCalcValues = computeLeastSquareErrors(points, n);
    vector<vector<big_pp> > leastSquareErrors = preCalcValues[0];
    vector<vector<big_pp> > pre_a = preCalcValues[1];
    vector<vector<big_pp> > pre_b = preCalcValues[2];

    vector<big_pp> OPT(n + 1, 0);
    vector<unsigned int> parent(n + 1);
    for (unsigned int i = 1; i <= n; ++i) {
        OPT[i] = leastSquareErrors[1][i] + c;
        parent[i] = 1;
        for (unsigned int j = 2; j <= i; ++j) {
            big_pp temp = OPT[j - 1] + leastSquareErrors[j][i] + c;
            if (temp < OPT[i]) {
                OPT[i] = temp;
                parent[i] = j;
            }
        }
    }
    // Storing index of the OPT array
    vector<Segment> Segments;
    unsigned int cur = n;
    while(cur > 1){
      int nxt = parent[cur];
      // cout<<cur<<' '<<nxt<<'\n';
      // cout<<pre_a[nxt][cur]<<' '<<pre_b[nxt][cur]<<'\n';
      if(nxt == cur){
        Segments.push_back(Segment(points[cur-2].x, points[cur-2].y, points[cur-1].x, points[cur-1].y));
      }
      else{
        big_pp x1 = points[nxt-1].x;
        big_pp y1 = pre_a[nxt][cur] * x1 + pre_b[nxt][cur];
        big_pp x2 = points[cur-1].x;
        big_pp y2 = pre_a[nxt][cur] * x2 + pre_b[nxt][cur];
        Segments.push_back(Segment(x1, y1, x2, y2));
      }
      cur = nxt - 1;
    }
    if(cur == 1){
      //means our beloved point 1 is not included in any line
      Segments.push_back(Segment(points[cur-1].x, points[cur-1].y, points[cur].x, points[cur].y));
    }
    return make_pair(OPT[n], Segments);
    // unsigned int cur = n, seg_num = 1;
    // while (true) {
    //     // Lines.push_back(cur);
    //     if (cur == 1) break;

    //     // cout << "Segment Number: " << seg_num << '\n';

    //     if (parent[cur] == cur) {
    //         unsigned int i = cur - 1;
    //         // for (unsigned int k = i; k <= cur; ++k) {
    //         //     cout << "\t" << points[k - 1].x << " " << points[k - 1].y << '\n';
    //         // }
    //         endPts.push_back(Segment(points[i - 1].x, points[i - 1].y, points[cur - 1].x, points[cur - 1].y));
    //         --cur;
    //     } else {
    //         unsigned int i = parent[cur];
    //         // for (unsigned int k = i; k <= cur; ++k) {
    //         //     cout << "\t" << points[k - 1].x << " " << points[k - 1].y << '\n';
    //         // }
    //         endPts.push_back(Segment(points[i - 1].x, points[i - 1].y, points[cur - 1].x, points[cur - 1].y));
    //         // endPts.push_back(Segment(points[i - 1].x, pre_a[i][cur] * points[i - 1].x + pre_b[i][cur], points[cur - 1].x, pre_a[i][cur] * points[cur - 1].x + pre_b[i][cur]));
    //         cur = parent[cur];
    //     }
    //     ++seg_num;
    // }
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        cout << "Check number of inputs again.\n";
        return 0;
    }

    freopen(argv[1], "r", stdin);

    unsigned int n;
    cin >> n;
    vector<Point> points;
    for (unsigned int i = 0; i < n; ++i) {
        big_pp x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }
    big_pp c;
    cin >> c;
    c = fabs(c);

    sort(points.begin(), points.end());
    pair<big_pp, vector<Segment> > Result= segmentedLeastSquares(n, points, c);

    // freopen output file and write the segments
    freopen(argv[2], "w", stdout);
    cout<<fixed<<setprecision(10)/*cout*/<<Result.first<<'\n';
    for (const Segment &p : Result.second) {
        cout << p.x1 << " " << p.y1 << " " << p.x2 << " " << p.y2 << "\n";
    }
    return 0;
}