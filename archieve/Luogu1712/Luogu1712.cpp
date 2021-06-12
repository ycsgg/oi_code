#include <algorithm>
#include <iostream>
using namespace std;
const int N = 5e5 + 5;
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int val, tag;
} tr[N << 3];
void pushdown(int rt) {
    if (tr[rt].tag) {
        tr[ls(rt)].val += tr[rt].tag;
        tr[ls(rt)].tag += tr[rt].tag;
        tr[rs(rt)].val += tr[rt].tag;
        tr[rs(rt)].tag += tr[rt].tag;
        tr[rt].tag = 0;
    }
}
void pushup(int rt) {
    tr[rt].val = max(tr[ls(rt)].val, tr[rs(rt)].val);
}
void update(int rt, int l, int r, int L, int R, int v) {
    if (L > r || R < l) {
        return;
    }
    if (l >= L && r <= R) {
        tr[rt].tag += v;
        tr[rt].val += v;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(rt);
    if (L <= mid) {
        update(ls(rt), l, mid, L, R, v);
    }
    if (mid <= R) {
        update(rs(rt), mid + 1, r, L, R, v);
    }
    pushup(rt);
}
} // namespace SegmentTree
int n, m;
struct Data {
    int val, id, l, r;
} a[N];
int b[N * 2];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        a[i].id      = i;
        a[i].val     = y - x;
        a[i].l       = x;
        a[i].r       = y;
        b[i * 2 - 1] = x;
        b[i * 2]     = y;
    }
    sort(b + 1, b + 1 + 2 * n);
    sort(a + 1, a + 1 + n, [](const Data &A, const Data &B) -> bool {
        return A.val < B.val;
    });
    int tot = unique(b + 1, b + 1 + 2 * n) - b - 1;
    for (int i = 1; i <= n; i++) {
        a[i].l = lower_bound(b + 1, b + 1 + tot, a[i].l) - b;
        a[i].r = lower_bound(b + 1, b + 1 + tot, a[i].r) - b;
    }
    int cur = 1, res = 0x3f3f3f3f;
    bool flag = 0;
    for (int i = 1; i <= n; i++) {
        SegmentTree::update(1, 1, tot, a[i].l, a[i].r, 1);
        // cout << a[i].l << " " << a[i].r << endl;
        while (SegmentTree::tr[1].val >= m) {
            flag = 1;
            res  = min(res, a[i].val - a[cur].val);
            SegmentTree::update(1, 1, tot, a[cur].l, a[cur].r, -1);
            cur++;
        }
    }
    if (flag) {
        cout << res << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
// Asusetic eru quionours
