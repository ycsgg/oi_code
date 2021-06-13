#include <iostream>
using namespace std;
const int N = 35005;
int n, k;
int a[N], pre[N], cur[N];
int dp[N][2];
int now;
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int val, l, r, tag;
} tr[N << 2];
void pushup(int rt) {
    tr[rt].val = max(tr[ls(rt)].val, tr[rs(rt)].val);
}
void pushdown(int rt) {
    if (tr[rt].tag) {
        tr[ls(rt)].tag += tr[rt].tag;
        tr[rs(rt)].tag += tr[rt].tag;
        tr[ls(rt)].val += tr[rt].tag;
        tr[rs(rt)].val += tr[rt].tag;
        tr[rt].tag = 0;
    }
}
void build(int rt, int l, int r) {
    tr[rt].l   = l;
    tr[rt].r   = r;
    tr[rt].tag = 0;
    if (l == r) {
        tr[rt].val = dp[l][now ^ 1];
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
void update(int rt, int L, int R, int v) {
    int &l = tr[rt].l;
    int &r = tr[rt].r;
    if (L <= l && R >= r) {
        tr[rt].val += v;
        tr[rt].tag += v;
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
int query(int rt, int L, int R) {
    int &l = tr[rt].l;
    int &r = tr[rt].r;
    if (L <= l && R >= r) {
        return tr[rt].val;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    int res = 0;
    if (L <= mid) {
        res = max(res, query(ls(rt), L, R));
    }
    if (mid < R) {
        res = max(res, query(rs(rt), L, R));
    }
    return res;
}
} // namespace SegmentTree
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i]    = cur[a[i]];
        cur[a[i]] = i;
    }
    now = 0;
    for (int i = 1; i <= k; i++) {
        SegmentTree::build(1, 0, n);
        for (int j = i; j <= n; j++) {
            SegmentTree::update(1, pre[j], j - 1, 1);
            // cout << SegmentTree::tr[1].val << endl;
            dp[j][now] = SegmentTree::query(1, 0, j - 1);
        }
        now ^= 1;
    }
    cout << dp[n][now ^ 1];
    return 0;
}
// Asusetic eru quionours