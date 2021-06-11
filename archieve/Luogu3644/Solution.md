### P3644 [APIO2015]八邻旁之桥

$K=1$ 结论就是经典中位数

$K=2$ 的时候考虑每对点肯定要走靠近自己中点的哪个桥，所以一定存在某个分界线使得左边全走一个桥，右边走另一个

按照坐标之和排序然后枚举分界点的位置，用线段树快速统计点到中位数的距离和即可

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 2e6 + 5;
int n, k;
long long ans = 0;
namespace SubTask1 {
int cnt = 0, c[N];
void solve() {
    char a, b;
    int x, y;
    for (int i = 1; i <= n; i++) {
        cin >> a >> x >> b >> y;
        if (a == b) {
            ans += abs(x - y);
            continue;
        } else {
            if (a == 'B') {
                swap(x, y);
            }
            ans++;
            c[++cnt] = x;
            c[++cnt] = y;
        }
    }
    sort(c + 1, c + cnt + 1);
    int mid = c[cnt / 2];
    for (int i = 1; i <= cnt; i++)
        ans += abs(mid - c[i]);
    cout << ans;
}
} // namespace SubTask1
namespace SubTask2 {
int cnt  = 0;
int bcnt = 0, b[N];
long long s[N];
struct SegmentTree {
    struct Node {
        long long val, sum;
        int l, r;
    } tr[N << 2];
    inline void pushup(int rt) {
        tr[rt].val = tr[rt * 2].val + tr[rt * 2 + 1].val;
        tr[rt].sum = tr[rt * 2].sum + tr[rt * 2 + 1].sum;
    }
    void build(int l, int r, int rt) {
        tr[rt].l   = l;
        tr[rt].r   = r;
        tr[rt].val = tr[rt].sum = 0;
        if (l >= r) {
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, rt * 2);
        build(mid + 1, r, rt * 2 + 1);
    }
    void update(int k, int v, int rt) {
        tr[rt].val++;
        tr[rt].sum += v;
        if (tr[rt].l == tr[rt].r)
            return;
        int mid = tr[rt].l + tr[rt].r >> 1;
        if (k <= mid)
            update(k, v, rt * 2);
        else
            update(k, v, rt * 2 + 1);
    }
    long long query(int k, int rt) {
        if (tr[rt].l == tr[rt].r)
            return 1LL * b[tr[rt].l] * k;
        if (k <= tr[rt * 2].val)
            return query(k, rt * 2);
        else
            return tr[rt * 2].sum + query(k - tr[rt * 2].val, rt * 2 + 1);
    }
    inline long long query(int x) {
        return tr[1].sum - 2LL * query(x, 1);
    }
} T;
struct Node {
    int x, y;
} d[N];
void solve() {
    char ch1, ch2;
    int x, y, p, q;
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> ch1 >> x >> ch2 >> y;
        if (ch1 == ch2) {
            res += abs(x - y);
        } else {
            res += 1;
            b[++bcnt] = x;
            b[++bcnt] = y;
            if (x > y) {
                swap(x, y);
            }
            d[++cnt].x = x;
            d[cnt].y   = y;
        }
    };
    sort(d + 1, d + cnt + 1, [&](Node A, Node B) -> bool {
        return (A.x + A.y) < (B.x + B.y);
    });
    sort(b + 1, b + bcnt + 1);
    bcnt = unique(b + 1, b + bcnt + 1) - b - 1;
    T.build(1, bcnt, 1);
    // cout << "P" << endl;
    for (int i = 1; i <= cnt; i++) {
        d[i].x = lower_bound(b + 1, b + bcnt + 1, d[i].x) - b;
        d[i].y = lower_bound(b + 1, b + bcnt + 1, d[i].y) - b;
        T.update(d[i].x, b[d[i].x], 1);
        T.update(d[i].y, b[d[i].y], 1);
        s[i] = T.query(i);
    }
    long long ans = s[cnt];
    T.build(1, bcnt, 1);
    for (int i = cnt; i >= 1; i--) {
        T.update(d[i].x, b[d[i].x], 1);
        T.update(d[i].y, b[d[i].y], 1);
        ans = min(ans, s[i - 1] + T.query(cnt - i + 1));
    }
    cout << ans + res << endl;
}
} // namespace SubTask2
int main() {
    cin >> k >> n;
    if (k == 1)
        SubTask1::solve();
    else
        SubTask2::solve();
    return 0;
}
```

