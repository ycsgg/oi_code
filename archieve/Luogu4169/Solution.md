### P4169 [Violet]天使玩偶/SJY摆棋子

~~能离线谁KDT啊~~

考虑cdq

如果所有回忆出来的点都在左下，那询问点 $Q$ 里回忆点的距离 $dis(Q,A)=|x_Q-x_A|+|y_Q-y_A|=(x_Q+y_Q)-(x_A+y_A)$

当 $(x_A+y_A)$ 取最大就有最小 $dis$

这就可以直接 cdq 了

其他的点需要换坐标达成

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e6 + 10;
int maxy, maxx;
namespace BIT {
int c[N];
int lowbit(int x) {
    return x & (-x);
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res = max(res, c[pos]);
        pos -= lowbit(pos);
    }
    return res;
}
void add(int pos, int v) {
    while (pos <= maxy) {
        c[pos] = max(c[pos], v);
        pos += lowbit(pos);
    }
}
void remove(int pos) {
    while (pos <= maxy) {
        c[pos] = 0;
        pos += lowbit(pos);
    }
}
} // namespace BIT
struct Oper {
    int x, y, id;
    bool tag;
    bool operator<(const Oper &B) const {
        return x <= B.x;
    }
} q[N], p[N], a[N];
int n, m;
int ans[N];
void cdq(int l, int r) {
    using BIT::add;
    using BIT::query;
    using BIT::remove;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        if (!p[i].tag) {
            while (j <= mid && p[j].x <= p[i].x) {
                if (p[j].tag) {
                    add(p[j].y, p[j].x + p[j].y);
                }
                ++j;
            }
            int tmp = query(p[i].y);
            if (tmp) {
                ans[p[i].id] = min(ans[p[i].id], p[i].x + p[i].y - tmp);
            }
        }
    }
    for (int i = l; i < j; i++) {
        if (p[i].tag) {
            remove(p[i].y);
        }
    }
    merge(p + l, p + mid + 1, p + mid + 1, p + r + 1, q + l);
    for (int i = l; i <= r; i++) {
        p[i] = q[i];
    }
}
void init() {
    int rx, ry;
    rx = ry = m = 0;
    for (int i = 1; i <= n; ++i) {
        if (!p[i].tag) {
            rx = max(rx, p[i].x);
            ry = max(ry, p[i].y);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (p[i].x <= rx && p[i].y <= ry) {
            q[++m] = p[i];
        }
    }
    for (int i = 1; i <= m; ++i) {
        p[i] = q[i];
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        x++, y++;
        p[i] = {x, y, i, true};
        maxx = max(maxx, x);
        maxy = max(maxy, y);
    }
    while (m--) {
        int k, x, y;
        cin >> k >> x >> y;
        x++, y++;
        ++n;
        p[n] = {x, y, n, (k == 1) ? true : false};
        maxx = max(maxx, x);
        maxy = max(maxy, y);
    }
    for (int i = 1; i <= n; i++) {
        a[i] = p[i];
    }
    ++maxx;
    ++maxy;
    init();
    memset(ans, 0x3f, sizeof(ans));
    cdq(1, m);
    for (int i = 1; i <= n; ++i) {
        p[i]   = a[i];
        p[i].x = maxx - p[i].x;
    }
    init();
    cdq(1, m);

    for (int i = 1; i <= n; ++i) {
        p[i]   = a[i];
        p[i].y = maxy - p[i].y;
    }
    init();
    cdq(1, m);

    for (int i = 1; i <= n; ++i) {
        p[i]   = a[i];
        p[i].x = maxx - p[i].x;
        p[i].y = maxy - p[i].y;
    }
    init();
    cdq(1, m);

    for (int i = 1; i <= n; ++i) {
        if (!a[i].tag) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
```

