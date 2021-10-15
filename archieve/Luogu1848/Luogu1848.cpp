#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const ll INF = (1ll << 55);
ll dp[N];
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int l, r;
    ll mmin, val, tag;
} tr[N * 4];
void pushup(int x) {
    tr[x].val = min(tr[ls(x)].val, tr[rs(x)].val);
    tr[x].mmin = min(tr[ls(x)].mmin, tr[rs(x)].mmin);
}
void pushdown(int x) {
    if (tr[x].tag) {
        tr[ls(x)].mmin = tr[ls(x)].val + tr[x].tag;
        tr[rs(x)].mmin = tr[rs(x)].val + tr[x].tag;
        tr[ls(x)].tag = tr[rs(x)].tag = tr[x].tag;
        tr[x].tag = 0;
    }
}
void build(int x, int l, int r) {
    tr[x].l = l;
    tr[x].r = r;
    tr[x].val = tr[x].mmin = INF;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
}
void update(int x, int L, int R, int v) {
    auto l = tr[x].l;
    auto r = tr[x].r;
    if (L <= l && r <= R) {
        tr[x].mmin = tr[x].val + v;
        tr[x].tag = v;
        return;
    }
    pushdown(x);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(x), L, R, v);
    }
    if (mid < R) {
        update(rs(x), L, R, v);
    }
    pushup(x);
}
void change(int x, int L, int R, int pos) {
    auto l = tr[x].l;
    auto r = tr[x].r;
    if (l == r) {
        tr[x].mmin = INF;
        tr[x].val = dp[l - 1];
        return;
    }
    pushdown(x);
    int mid = (l + r) / 2;
    if (pos <= mid) {
        change(ls(x), L, R, pos);
    } else {
        change(rs(x), L, R, pos);
    }
    pushup(x);
}
ll query(int x, int L, int R) {
    auto l = tr[x].l;
    auto r = tr[x].r;
    if (L <= l && r <= R) {
        return tr[x].mmin;
    }
    pushdown(x);
    int mid = (l + r) / 2;
    ll res = INF;
    if (L <= mid) {
        res = min(res, query(ls(x), L, R));
    }
    if (mid < R) {
        res = min(res, query(rs(x), L, R));
    }
    return res;
}
} // namespace SegmentTree
int n, L;
int h[N], w[N];
ll s[N];
int S[N], top, pre[N];
int main() {
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> w[i];
        s[i] = s[i - 1] + w[i];
    }
    S[++top] = 1;
    for (int i = 2; i <= n; i++) {
        while (top && h[i] > h[S[top]]) {
            top--;
        }
        if (top) {
            pre[i] = S[top];
        }
        S[++top] = i;
    }
    SegmentTree::build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        SegmentTree::change(1, 1, n, i);
        if (pre[i] + 1 <= i) {
            SegmentTree::update(1, pre[i] + 1, i, h[i]);
        }
        int l = lower_bound(s, s + 1 + n, s[i] - L) - s;
        if (l < i) {
            dp[i] = SegmentTree::query(1, l + 1, i);
        }
    }
    cout << dp[n];
    return 0;
}
// Asusetic eru quionours.