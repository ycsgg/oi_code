### P3454 [POI2007]OSI-Axes of Symmetry

虽然看起来是个计算几何但是和计算几何完全没关系

考虑对称轴的充要条件是两边对应的角和边都相等

那考虑按 边-角-边-角-..... 的顺序连接起来一个环

这样的话如果某个地方是对称轴那么断开这条边，剩下的部分构成一个“回文串”

这样的话考虑复制两倍成链然后在这个 $4n$ 的链上找 $2n$ 的回文串即可

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
namespace Geo {
struct Point {
    ll x, y;
    Point(ll xx = 0, ll yy = 0) {
        x = xx;
        y = yy;
    }
    Point operator+(const Point &B) const {
        return Point(x + B.x, y + B.y);
    }
    Point operator-(const Point &B) const {
        return Point(x - B.x, y - B.y);
    }
};
ll dot(const Point &A, const Point &B) {
    return A.x * B.x + A.y * B.y;
}
ll cross(const Point &A, const Point &B) {
    return A.x * B.y - A.y * B.x;
}
ll dis(const Point &A, const Point &B) {
    Point tmp = A - B;
    return dot(tmp, tmp);
}
ll Angle(const Point &A, const Point &B, const Point &C) {
    return cross(B - A, C - B);
}
} // namespace Geo
using namespace Geo;
const int N = 1e5 + 5;
int T, n;
Point P[N];
ll calc_edge(int x) {
    int y = (x + 1) % (n + 1);
    if (!y) {
        y = 1;
    }
    return dis(P[x], P[y]);
}
ll calc_angle(int x) {
    int y = (x + 1) % (n + 1);
    if (!y) {
        y = 1;
    }
    int z = (y + 1) % (n + 1);
    if (!z) {
        z = 1;
    }
    return Angle(P[x], P[y], P[z]);
}
int s[N * 4];
int t[N * 2], nxt[N * 4], f[N * 4];
int KMP() {
    nxt[0] = -1;
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= n * 2; i++) {
        while (j != -1 && t[i] != t[j + 1])
            j = nxt[j];
        j++;
        nxt[i] = j;
    }
    for (int i = 2, j = 0; i <= n * 4; i++) {
        while (j != -1 && s[i] != t[j + 1])
            j = nxt[j];
        j++;
        f[i] = j;
    }
    int cnt = 0;
    for (int i = 1; i <= n * 4; i++) {
        if (f[i] == n * 2)
            cnt++;
    }
    return cnt;
}
int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        int cnt;
        for (int i = 1; i <= n; i++) {
            cin >> P[i].x >> P[i].y;
        }
        for (int i = 1; i <= n; i++) {
            s[i * 2 - 1]         = calc_edge(i);
            s[i * 2]             = calc_angle(i);
            s[2 * n + i * 2 - 1] = s[i * 2 - 1];
            s[2 * n + i * 2]     = s[i * 2];
        }
        for (int i = 2 * n; i >= 1; i--) {
            t[2 * n - i + 1] = s[i];
        }
        cout << KMP() << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

