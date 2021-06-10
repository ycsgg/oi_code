#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const double eps = 1e-8;
const int N      = 505;
typedef long long ll;
struct Vector {
    ll x, y;
    Vector(ll x = 0, ll y = 0) : x(x), y(y) {
    }
    Vector operator+(const Vector &B) const {
        return Vector(x + B.x, y + B.y);
    }
    Vector operator-(const Vector &B) const {
        return Vector(x - B.x, y - B.y);
    }
    Vector operator-() const {
        return Vector(-x, -y);
    }
    bool operator==(const Vector &B) const {
        return (x == B.x) && (y == B.y);
    }
} A[N], B[N];
ll cross(const Vector &A, const Vector &B) {
    return A.x * B.y - B.x * A.y;
}
ll dot(const Vector &A, const Vector &B) {
    return A.x * B.x + A.y * B.y;
}
bool isLeft(const Vector &X, const Vector &Y, const Vector &P) {
    return cross(Y - X, P - X) > 0;
}
int n, m;
bool check(const Vector &X, const Vector &Y) {
    for (int i = 1; i <= m; i++) {
        if (isLeft(X, Y, B[i])) {
            return false;
        }
    }
    for (int i = 1; i <= m; ++i)
        if (cross(X - Y, B[i] - X) == 0) {
            if (X == B[i] || Y == B[i])
                continue;
            double l, r;
            l = X.x, r = Y.x;
            if (l > r) {
                swap(l, r);
            }
            if (l > B[i].x || B[i].x > r)
                return false;
            l = X.y, r = Y.y;
            if (l > r)
                swap(l, r);
            if (l > B[i].y || B[i].y > r) {
                cout << "R" << endl;
                return false;
            }
        }
    return 1;
}
int dis[N][N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        double tmp;
        double a, b;
        cin >> a >> b >> tmp;
        A[i].x = a * 1000000;
        A[i].y = b * 1000000;
    }
    for (int i = 1; i <= m; i++) {
        double tmp;
        double a, b;
        cin >> a >> b >> tmp;
        B[i].x = a * 1000000;
        B[i].y = b * 1000000;
    }
    static auto cmp = [&](const Vector &A, const Vector &B) -> bool {
        if ((A.x != B.x)) {
            return A.x < B.x;
        }
        if ((A.y != B.y)) {
            return A.y < B.y;
        }
        return 0;
    };
    sort(A + 1, A + 1 + n, cmp);
    sort(B + 1, B + 1 + m, cmp);
    n = unique(A + 1, A + 1 + n) - A - 1;
    m = unique(B + 1, B + 1 + m) - B - 1;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            if (check(A[i], A[j])) {
                dis[i][j] = 1;
                // cout << i << " " << j << endl;
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dis[i][i]);
    }
    if (n == 1 && m == 1 && A[1] == B[1]) {
        cout << 1 << endl;
        return 0;
    }
    if (ans == 1e9) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours