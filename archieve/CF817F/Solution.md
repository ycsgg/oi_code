### CF817F MEX Queries

区间赋值 $0/1$，区间异或 $1$ ，维护区间和线段树上打俩标记解决

找 $\mathrm{mex}$ 就在线段树上找和和不等于长度的区间，先左后右

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
namespace SegmentTree {
enum Type {
    ASSIGN0,
    ASSIGN1,
    XOR,
};
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int sum, assign, rev;
    int l, r;
} tr[N << 4];
void pushup(int rt) {
    tr[rt].sum = tr[ls(rt)].sum + tr[rs(rt)].sum;
}
void pushdown(int rt) {
    int mid = (tr[rt].l + tr[rt].r) / 2;
    if (~tr[rt].assign) {
        tr[ls(rt)].assign = tr[rs(rt)].assign = tr[rt].assign;
        tr[ls(rt)].rev = tr[rs(rt)].rev = 0;
        if (tr[rt].assign) {
            tr[ls(rt)].sum = mid - tr[rt].l + 1;
            tr[rs(rt)].sum = tr[rt].r - mid;
        } else {
            tr[ls(rt)].sum = 0;
            tr[rs(rt)].sum = 0;
        }
        tr[rt].assign = -1;
    } else if (tr[rt].rev) {
        if (~tr[ls(rt)].assign) {
            tr[ls(rt)].assign ^= 1;
        } else {
            tr[ls(rt)].rev ^= 1;
        }
        if (~tr[rs(rt)].assign) {
            tr[rs(rt)].assign ^= 1;
        } else {
            tr[rs(rt)].rev ^= 1;
        }
        tr[ls(rt)].sum = mid - tr[rt].l + 1 - tr[ls(rt)].sum;
        tr[rs(rt)].sum = tr[rt].r - mid - tr[rs(rt)].sum;
        tr[rt].rev     = 0;
    }
}
void build(int rt, int l, int r) {
    tr[rt].l      = l;
    tr[rt].r      = r;
    tr[rt].assign = -1;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
}
void update(int rt, int L, int R, Type typ) {
    int &l = tr[rt].l;
    int &r = tr[rt].r;
    if (L <= l && R >= r) {
        // cout << l << " " << r << " " << L << " " << R << endl;
        if (typ == ASSIGN0) {
            tr[rt].assign = 0;
            tr[rt].rev    = 0;
            tr[rt].sum    = 0;
        } else if (typ == ASSIGN1) {
            tr[rt].assign = 1;
            tr[rt].rev    = 0;
            tr[rt].sum    = r - l + 1;
        } else {
            if (~tr[rt].assign) {
                tr[rt].assign ^= 1;
            } else {
                tr[rt].rev ^= 1;
            }
            tr[rt].sum = r - l + 1 - tr[rt].sum;
        }
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(rt), L, R, typ);
    }
    if (mid < R) {
        update(rs(rt), L, R, typ);
    }
    pushup(rt);

} // namespace SegmentTree
long long query(int rt = 1) {
    int &l = tr[rt].l;
    int &r = tr[rt].r;
    if (l == r)
        return l;
    pushdown(rt);
    int mid = (l + r) / 2;
    if (tr[ls(rt)].sum < (mid - l + 1)) {
        return query(ls(rt));
    } else {
        return query(rs(rt));
    }
}
#undef ls
#undef rs
} // namespace SegmentTree
int m;
struct Oper {
    int typ;
    long long l, r;
} q[N];
long long b[N * 4];
int main() {
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].typ >> q[i].l >> q[i].r;
        b[i * 3 - 2] = q[i].l;
        b[i * 3 - 1] = q[i].r;
        b[i * 3]     = q[i].r + 1;
    }
    b[3 * m + 1] = 1;
    sort(b + 1, b + 1 + 3 * m + 1);

    int tot = unique(b + 1, b + 1 + 3 * m + 1) - b - 1;
    for (int i = 1; i <= m; i++) {
        q[i].l = lower_bound(b + 1, b + 1 + tot, q[i].l) - b;
        q[i].r = lower_bound(b + 1, b + 1 + tot, q[i].r) - b;
    }
    SegmentTree::build(1, 1, tot);
    static auto turn = [&](const int x) -> SegmentTree::Type {
        if (x == 1) {
            return SegmentTree::ASSIGN1;
        } else if (x == 2) {
            return SegmentTree::ASSIGN0;
        } else {
            return SegmentTree::XOR;
        }
    };
    for (int i = 1; i <= m; i++) {
        SegmentTree::update(1, q[i].l, q[i].r, turn(q[i].typ));
        // cout << "P" << endl;
        cout << b[SegmentTree::query()] << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

