#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
using ll = long long;
int n, Q;
int st[N], l[N], r[N];
ll a[N], sum[N];
ll ans[N];
struct Oper {
    int place;
    ll val;
};
struct Query {
    int l, r, id;
};
vector<Oper> pos[N];
vector<Query> q[N];
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct node {
    int l, r, len;
    ll tag1, tag2;
    ll val1, val2;
} tr[1200005];
void pushdown(int x) {
    if (tr[x].tag1) {
        tr[ls(x)].tag1 += tr[x].tag1;
        tr[ls(x)].val1 += tr[x].tag1 * (tr[ls(x)].r - tr[ls(x)].l + 1);
        tr[rs(x)].tag1 += tr[x].tag1;
        tr[rs(x)].val1 += tr[x].tag1 * (tr[rs(x)].r - tr[rs(x)].l + 1);
        tr[x].tag1 = 0;
    }
    if (tr[x].tag2) {
        tr[ls(x)].tag2 += tr[x].tag2;
        tr[ls(x)].val2 += tr[x].tag2 * (tr[ls(x)].r - tr[ls(x)].l + 1);
        tr[rs(x)].tag2 += tr[x].tag2;
        tr[rs(x)].val2 += tr[x].tag2 * (tr[rs(x)].r - tr[rs(x)].l + 1);
        tr[x].tag2 = 0;
    }
}
void pushup(int x) {
    tr[x].val1 = tr[ls(x)].val1 + tr[rs(x)].val1;
    tr[x].val2 = tr[ls(x)].val2 + tr[rs(x)].val2;
}
void build(int x, int l, int r) {
    tr[x].l = l;
    tr[x].r = r;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
}
void update1(int x, int l, int r, ll val) {
    if (l <= tr[x].l && tr[x].r <= r) {
        tr[x].tag1 += val;
        tr[x].val1 += val * (tr[x].r - tr[x].l + 1);
        return;
    }
    int mid = (tr[ls(x)].r);
    pushdown(x);
    if (l <= mid) {
        update1(ls(x), l, r, val);
    }
    if (mid < r) {
        update1(rs(x), l, r, val);
    }
    pushup(x);
}
void update2(int x, int l, int r, ll val) {
    if (l <= tr[x].l && tr[x].r <= r) {
        tr[x].tag2 += val;
        tr[x].val2 += val * (tr[x].r - tr[x].l + 1);
        return;
    }
    int mid = (tr[ls(x)].r);
    pushdown(x);
    if (l <= mid) {
        update2(ls(x), l, r, val);
    }
    if (mid < r) {
        update2(rs(x), l, r, val);
    }
    pushup(x);
}
ll query1(int x, int L, int R) {
    auto l = tr[x].l;
    auto r = tr[x].r;
    if (L <= l && r <= R) {
        return tr[x].val1;
    }
    pushdown(x);
    int mid = tr[ls(x)].r;
    ll res = 0;
    if (L <= mid) {
        res += query1(ls(x), L, R);
    }
    if (mid < R) {
        res += query1(rs(x), L, R);
    }
    return res;
}
ll query2(int x, int L, int R) {
    auto l = tr[x].l;
    auto r = tr[x].r;
    if (L <= l && r <= R) {
        return tr[x].val2;
    }
    pushdown(x);
    int mid = tr[ls(x)].r;
    ll res = 0;
    if (L <= mid) {
        res += query2(ls(x), L, R);
    }
    if (mid < R) {
        res += query2(rs(x), L, R);
    }
    return res;
}
void update(int x, int y, int val) {
    update1(1, -n, x, val);
    update2(1, -n, y - 1, val);
}
ll query(int a, int b, int c, int d) {
    ll res = query1(1, a, b) - query2(1, c, d);
    return res;
}
}; // namespace SegmentTree
int top;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> Q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i <= Q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        ans[i] = sum[r] - sum[l - 1];
        q[t].push_back({l, r, i});
    }
    for (int i = 1; i <= n; ++i) {
        while (top && a[i] >= a[st[top]]) {
            r[st[top]] = i;
            top--;
        }
        l[i] = st[top];
        st[++top] = i;
    }
    for (int i = 1; i <= n; ++i) {
        if (l[i]) {
            pos[i - l[i]].push_back({i, a[l[i]] - a[i]});
            if (r[i]) {
                pos[r[i] - l[i]].push_back({r[i], a[i] - a[l[i]]});
            }
        }
    }
    SegmentTree::build(1, -n, n);
    for (int i = 1; i <= n; i++) {
        for (auto v : pos[i]) {
            SegmentTree::update(v.place - i, v.place, v.val);
        }
        for (auto qr : q[i]) {
            ans[qr.id] += SegmentTree::query(qr.l - i, qr.r - i, qr.l, qr.r);
        }
    }
    for (int i = 1; i <= Q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
// Asusetic eru quionours.