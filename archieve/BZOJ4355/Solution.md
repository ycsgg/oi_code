### 4355. Play with sequence

第二个操作拆成区间取 $\max$ 和区间加发，然后Jry线段树解决

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll     = long long;
const int N  = 300005;
const ll INF = (1ll << 62);
namespace SegBeats {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
struct Node {
    ll mmin, semin;
    ll cover, add;
    int cnt;
    int l, r;
};
array<Node, N * 4> tr;
void pushup(int x) {
    if (tr[ls(x)].mmin < tr[rs(x)].mmin) {
        tr[x].mmin  = tr[ls(x)].mmin;
        tr[x].cnt   = tr[ls(x)].cnt;
        tr[x].semin = min(tr[ls(x)].semin, tr[rs(x)].mmin);
    } else if (tr[ls(x)].mmin > tr[rs(x)].mmin) {
        tr[x].mmin  = tr[rs(x)].mmin;
        tr[x].cnt   = tr[rs(x)].cnt;
        tr[x].semin = min(tr[rs(x)].semin, tr[ls(x)].mmin);
    } else {
        tr[x].mmin  = tr[rs(x)].mmin;
        tr[x].cnt   = tr[rs(x)].cnt + tr[ls(x)].cnt;
        tr[x].semin = min(tr[rs(x)].semin, tr[ls(x)].semin);
    }
}
void pushdown(int x) {
    int mid = (tr[x].l + tr[x].r) / 2;
    if (~tr[x].cover) {
        tr[ls(x)].cover = tr[rs(x)].cover = tr[x].cover;
        tr[ls(x)].add = tr[rs(x)].add = 0;
        tr[ls(x)].mmin                = tr[x].cover;
        tr[rs(x)].mmin                = tr[x].cover;
        tr[ls(x)].semin               = INF;
        tr[rs(x)].semin               = INF;
        tr[ls(x)].cnt                 = (mid - tr[x].l + 1);
        tr[rs(x)].cnt                 = (tr[x].r - mid);
        tr[x].cover                   = -1;
    }
    // FIXED!
    if (tr[x].add) {
        tr[ls(x)].add += tr[x].add;
        tr[rs(x)].add += tr[x].add;
        tr[ls(x)].mmin += tr[x].add;
        tr[rs(x)].mmin += tr[x].add;
        tr[ls(x)].semin += tr[x].add;
        tr[rs(x)].semin += tr[x].add;
        tr[x].add = 0;
    }
    if (tr[ls(x)].mmin < tr[x].mmin) {
        tr[ls(x)].mmin = tr[x].mmin;
    }
    if (tr[rs(x)].mmin < tr[x].mmin) {
        tr[rs(x)].mmin = tr[x].mmin;
    }
}
void build(int rt, int l, int r, const vector<int> &p) {
    tr[rt].l     = l;
    tr[rt].r     = r;
    tr[rt].cover = -1;
    if (l == r) {
        tr[rt].mmin  = p[l];
        tr[rt].semin = INF;
        tr[rt].cnt   = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid, p);
    build(rs(rt), mid + 1, r, p);
    pushup(rt);
}
void update_cover(int rt, int L, int R, ll v) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (L <= l && R >= r) {
        tr[rt].mmin  = v;
        tr[rt].cnt   = r - l + 1;
        tr[rt].semin = INF;
        tr[rt].cover = v;
        tr[rt].add   = 0;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update_cover(ls(rt), L, R, v);
    }
    if (mid < R) {
        update_cover(rs(rt), L, R, v);
    }
    pushup(rt);
}
void update_add(int rt, int L, int R, ll v) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (L <= l && R >= r) {
        tr[rt].mmin += v;
        tr[rt].semin += v;
        tr[rt].add += v;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update_add(ls(rt), L, R, v);
    }
    if (mid < R) {
        update_add(rs(rt), L, R, v);
    }
    pushup(rt);
}
void update_max(int rt, int L, int R) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (tr[rt].mmin >= 0)
        return;
    if (L <= l && R >= r && tr[rt].semin > 0) {
        tr[rt].mmin = 0;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update_max(ls(rt), L, R);
    }
    if (mid < R) {
        update_max(rs(rt), L, R);
    }
    pushup(rt);
}
int query(int rt, int L, int R) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (L <= l && R >= r) {
        return tr[rt].mmin == 0 ? tr[rt].cnt : 0;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    int res = 0;
    if (L <= mid) {
        res += query(ls(rt), L, R);
    }
    if (mid < R) {
        res += query(rs(rt), L, R);
    }
    return res;
}
#undef ls
#undef rs
} // namespace SegBeats
int n, m;
int main() {
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    SegBeats::build(1, 1, n, a);
    while (m--) {
        int opt, x, y;
        ll z;
        cin >> opt >> x >> y;
        if (opt == 1) {
            cin >> z;
            SegBeats::update_cover(1, x, y, z);
        } else if (opt == 2) {
            cin >> z;
            SegBeats::update_add(1, x, y, z);
            SegBeats::update_max(1, x, y);
        } else {
            cout << SegBeats::query(1, x, y) << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours
```

#线段树 