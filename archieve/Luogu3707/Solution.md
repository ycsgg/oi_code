### P3707 [SDOI2017]相关分析

推柿子题

参考题解 [\[Luogu 3707\] SDOI2017 相关分析 - Capella - 博客园 (cnblogs.com)](https://www.cnblogs.com/Capella/p/8481720.html)

我就不再复述了

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
double x[N], y[N];
int n, m;
struct SegmentTree {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
    double ansxqr, ansysum, ansxsum, ansxy;
    struct Node {
        int tag;
        double S, T;
        double xsqr, xsum, ysum, xy;
        int l, r;
        Node(int _l = 0, int _r = 0) {
            l = _l, r = _r, tag = S = T = 0;
        }
    } tr[N << 2];
    double calc(double x) {
        return x * (x + 1) * (2 * x + 1) / 6;
    }
    void _add(int rt, double S, double T) {
        double size = double(tr[rt].r - tr[rt].l + 1);
        tr[rt].xsqr += S * S * size + 2 * S * tr[rt].xsum;
        tr[rt].xy += S * T * size + S * tr[rt].ysum + T * tr[rt].xsum;
        tr[rt].xsum += S * size;
        tr[rt].ysum += T * size;
        tr[rt].S += S, tr[rt].T += T;
    }
    void _change(int rt) {
        double l = double(tr[rt].l), r = double(tr[rt].r);
        tr[rt].xsqr = tr[rt].xy = calc(r) - calc(l - 1);
        tr[rt].xsum = tr[rt].ysum = (r - l + 1) * (l + r) / 2;
        tr[rt].tag = 1, tr[rt].S = tr[rt].T = 0;
    }
    void pushup(int rt) {
        tr[rt].xsqr = tr[ls(rt)].xsqr + tr[rs(rt)].xsqr;
        tr[rt].xsum = tr[ls(rt)].xsum + tr[rs(rt)].xsum;
        tr[rt].xy   = tr[ls(rt)].xy + tr[rs(rt)].xy;
        tr[rt].ysum = tr[ls(rt)].ysum + tr[rs(rt)].ysum;
    }
    void pushdown(int rt) {
        if (tr[rt].tag) {
            _change(ls(rt));
            _change(rs(rt));
        }
        _add(ls(rt), tr[rt].S, tr[rt].T);
        _add(rs(rt), tr[rt].S, tr[rt].T);
        tr[rt].tag = tr[rt].S = tr[rt].T = 0;
    }
    void get_sum(int rt, int l, int r) {
        if (l == tr[rt].l && r == tr[rt].r) {
            ansxqr += tr[rt].xsqr;
            ansxsum += tr[rt].xsum;
            ansysum += tr[rt].ysum;
            ansxy += tr[rt].xy;
            return;
        }
        pushdown(rt);
        int mid = (tr[rt].l + tr[rt].r) / 2;
        if (r <= mid)
            get_sum(ls(rt), l, r);
        else if (l > mid)
            get_sum(rs(rt), l, r);
        else
            get_sum(ls(rt), l, mid), get_sum(rs(rt), mid + 1, r);
    }
    void build(int rt, int l, int r) {
        tr[rt].l = l;
        tr[rt].r = r;
        if (l == r) {
            tr[rt].xsqr = x[l] * x[l];
            tr[rt].xy   = x[l] * y[r];
            tr[rt].xsum = x[l];
            tr[rt].ysum = y[r];
            return;
        }
        int mid = (l + r) / 2;
        build(ls(rt), l, mid);
        build(rs(rt), mid + 1, r);
        pushup(rt);
    }
    void update_add(int rt, int l, int r, double S, double T) {
        if (l == tr[rt].l && r == tr[rt].r) {
            _add(rt, S, T);
            return;
        }
        pushdown(rt);
        int mid = (tr[rt].l + tr[rt].r) / 2;
        if (r <= mid)
            update_add(ls(rt), l, r, S, T);
        else if (l > mid)
            update_add(rs(rt), l, r, S, T);
        else {
            update_add(ls(rt), l, mid, S, T);
            update_add(rs(rt), mid + 1, r, S, T);
        }
        pushup(rt);
    }
    void update_change(int rt, int l, int r, double S, double T) {
        if (l == tr[rt].l && r == tr[rt].r) {
            _change(rt);
            _add(rt, S, T);
            return;
        }
        pushdown(rt);
        int mid = (tr[rt].l + tr[rt].r) / 2;
        if (r <= mid)
            update_change(ls(rt), l, r, S, T);
        else if (l > mid)
            update_change(rs(rt), l, r, S, T);
        else {
            update_change(ls(rt), l, mid, S, T);
            update_change(rs(rt), mid + 1, r, S, T);
        }
        pushup(rt);
    }
    double query(double l, double r) {
        double size = r - l + 1;
        ansxqr = ansxsum = ansxy = ansysum = 0;
        get_sum(1, l, r);
        return (ansxy - ansxsum * ansysum / size) /
               (ansxqr - ansxsum * ansxsum / size);
    }
#undef ls
#undef rs
} Tr;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &x[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &y[i]);
    Tr.build(1, 1, n);
    for (int i = 1, opt, l, r; i <= m; ++i) {
        double S, T;
        cin >> opt >> l >> r;
        if (opt == 1) {
            printf("%.10lf\n", Tr.query(l, r));
        } else if (opt == 2) {
            cin >> S >> T;
            Tr.update_add(1, l, r, S, T);
        } else {
            cin >> S >> T;
            Tr.update_change(1, l, r, S, T);
        }
    }
    return 0;
}
// Asusetic eru quionours.
```

#线段树