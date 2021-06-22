#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 200010;
namespace SegmentTree {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
struct Node {
    int l, r, val, tag;
};
array<Node, N * 4> tr;
void pushup(int x) {
    tr[x].val = tr[ls(x)].val + tr[rs(x)].val;
}
void pushdown(int x) {
    if (~tr[x].tag) {
        int mid       = (tr[x].l + tr[x].r) / 2;
        tr[ls(x)].tag = tr[rs(x)].tag = tr[x].tag;
        tr[ls(x)].val                 = (mid - tr[x].l + 1) * tr[x].tag;
        tr[rs(x)].val                 = (tr[x].r - mid) * tr[x].tag;
        tr[x].tag                     = -1;
    }
}
void build(int rt, int l, int r, const vector<int> &p) {
    tr[rt].l   = l;
    tr[rt].r   = r;
    tr[rt].tag = -1;
    if (l == r) {
        tr[rt].val = p[l];
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid, p);
    build(rs(rt), mid + 1, r, p);
    pushup(rt);
}
void update(int rt, int L, int R, int v) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (L <= l && R >= r) {
        tr[rt].val = (r - l + 1) * v;
        tr[rt].tag = v;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(rt), L, R, v);
    }
    if (mid < R) {
        update(rs(rt), L, R, v);
    }
    pushup(rt);
}
int query_sum(int rt, int L, int R) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (L <= l && R >= r) {
        return tr[rt].val;
    }
    int mid = (l + r) / 2;
    pushdown(rt);
    int res = 0;
    if (L <= mid) {
        res += query_sum(ls(rt), L, R);
    }
    if (mid < R) {
        res += query_sum(rs(rt), L, R);
    }
    return res;
}
int query_pos(int pos) {
    return query_sum(1, pos, pos);
}
} // namespace SegmentTree
int n, m, q;
array<int, N> L, R, opt;
bool check(int x, const vector<int> val) {
    vector<int> p(val);
    for_each(p.begin(), p.end(), [&](int &u) -> void {
        u = (u >= x);
    });
    SegmentTree::build(1, 1, n, p);
    for (int i = 1; i <= m; i++) {
        int c = SegmentTree::query_sum(1, L[i], R[i]);
        if (opt[i] == 0) {
            SegmentTree::update(1, R[i] - c + 1, R[i], 1);
            SegmentTree::update(1, L[i], R[i] - c, 0);
        } else {
            SegmentTree::update(1, L[i], L[i] + c - 1, 1);
            SegmentTree::update(1, L[i] + c, R[i], 0);
        }
    }
    return SegmentTree::query_pos(q);
}
int main() {
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> opt[i] >> L[i] >> R[i];
    }
    cin >> q;
    int ans;
    int l = 1, r = n, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (check(mid, a)) {
            ans = mid;
            l   = mid + 1;
        } else
            r = mid - 1;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours