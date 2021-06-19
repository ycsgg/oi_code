### P4243 [JSOI2009]等差数列

线段树题，写起来略恶心

维护每个区间左右端点选/不选的答案，合并取$\min$ 还需要记录左右端点的值

```cpp
#include <array>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
const int N = 100005;
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int lv, rv;
    int tag;
    array<array<int, 2>, 2> val;
    array<int, 2> &operator[](const int x) {
        return val[x];
    }
    const array<int, 2> operator[](const int x) const {
        return val[x];
    }
};
array<Node, N * 4> tr;
void pushdown(int x) {
    if (tr[x].tag) {
        tr[ls(x)].tag += tr[x].tag;
        tr[ls(x)].lv += tr[x].tag;
        tr[ls(x)].rv += tr[x].tag;
        tr[rs(x)].tag += tr[x].tag;
        tr[rs(x)].lv += tr[x].tag;
        tr[rs(x)].rv += tr[x].tag;
        tr[x].tag = 0;
    }
}
Node merge(const Node &L, const Node &R, int tag = 0) {
    Node res;
    res.tag   = tag;
    res.lv    = L.lv;
    res.rv    = R.rv;
    res[0][0] = L[0][1] + R[1][0] - (L.rv == R.lv);
    res[0][0] = min(res[0][0], L[0][0] + R[1][0]);
    res[0][0] = min(res[0][0], L[0][1] + R[0][0]);
    res[1][0] = L[1][1] + R[1][0] - (L.rv == R.lv);
    res[1][0] = min(res[1][0], L[1][0] + R[1][0]);
    res[1][0] = min(res[1][0], L[1][1] + R[0][0]);
    res[0][1] = L[0][1] + R[1][1] - (L.rv == R.lv);
    res[0][1] = min(res[0][1], L[0][1] + R[0][1]);
    res[0][1] = min(res[0][1], L[0][0] + R[1][1]);
    res[1][1] = L[1][1] + R[1][1] - (L.rv == R.lv);
    res[1][1] = min(res[1][1], L[1][1] + R[0][1]);
    res[1][1] = min(res[1][1], L[1][0] + R[1][1]);
    return res;
}
void build(int rt, int l, int r, const vector<int> &p) {
    if (l == r) {
        tr[rt][0][0] = 0;
        tr[rt][1][0] = tr[rt][0][1] = tr[rt][1][1] = 1;
        tr[rt].tag                                 = 0;
        tr[rt].lv = tr[rt].rv = p[l];
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid, p);
    build(rs(rt), mid + 1, r, p);
    tr[rt].tag = 0;
    tr[rt]     = merge(tr[ls(rt)], tr[rs(rt)]);
}
void update(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && R >= r) {
        tr[rt].tag += v;
        tr[rt].lv += v;
        tr[rt].rv += v;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(rt), l, mid, L, R, v);
    }
    if (mid < R) {
        update(rs(rt), mid + 1, r, L, R, v);
    }
    tr[rt] = merge(tr[ls(rt)], tr[rs(rt)], tr[rt].tag);
}
Node query(int rt, int l, int r, int L, int R) {
    if (L <= l && R >= r) {
        return tr[rt];
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (R <= mid) {
        return query(ls(rt), l, mid, L, R);
    } else if (L > mid) {
        return query(rs(rt), mid + 1, r, L, R);
    } else {
        return merge(query(ls(rt), l, mid, L, mid),
                     query(rs(rt), mid + 1, r, mid + 1, R));
    }
}
} // namespace SegmentTree
int n, q;
int main() {
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        a[i] = a[i + 1] - a[i];
    }
    SegmentTree::build(1, 1, n - 1, a);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        char opt;
        int s, t, a, b;
        cin >> opt;
        if (opt == 'A') {
            cin >> s >> t >> a >> b;
            if (s != 1)
                SegmentTree::update(1, 1, n - 1, s - 1, s - 1, a);
            if (t != n)
                SegmentTree::update(1, 1, n - 1, t, t, -(a + b * (t - s)));
            if (s != t)
                SegmentTree::update(1, 1, n - 1, s, t - 1, b);
        } else {
            cin >> a >> b;
            if (a == b || b - a == 1) {
                cout << 1 << endl;
                continue;
            }
            cout << SegmentTree::query(1, 1, n - 1, a, b - 1)[1][1] << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours
```

#线段树 