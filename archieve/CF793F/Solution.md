### CF793F Julia the snail

优雅的非分块做法

询问先离线下来，按右端点排个序，然后考虑当右端点移动的时候答案怎么变化

记点 $x$ 点的答案为 $r_x$

当从 $r \rightarrow r+1$ 的时候，如果这个点有绳子 $[l,r+1]$ 那么考虑在 $l$ 左边的点如果它的答案在 $[l+1,r]$ 之间（事实上不可能超过 $r$）

那就将其更新为 $r+1$ ，那么我们要快速找到 $[1,l]$ 的点中大于 $l$ 的点并将其修改为 $r+1$

这个东西可以用势能线段树做，具体来说记录一个两元的标记 $tag(x,y)$ 表示大于等于 $y$ 的点修改为 $x$ 就可以做了，下放注意下要取最小的 $y$

其他操作和势能线段树一样，复杂度 $O(m\log n)$

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N   = 1e5 + 10;
const int INF = 0x3f3f3f3f;
namespace SegmentBeats {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int max, sem;
    pair<int, int> tag;
    int l, r;
};
array<Node, N * 4> tr;
auto merge(const Node &A, const Node &B) {
    pair<int, int> res;
    if (B.max > A.max) {
        res.first  = B.max;
        res.second = max(A.max, B.sem);
    } else if (B.max < A.max) {
        res.first  = A.max;
        res.second = max(A.sem, B.max);
    } else {
        res.first  = A.max;
        res.second = max(A.sem, B.sem);
    }
    return res;
}
// apply B -> A
void apply_tag(Node &A, const Node &B) {
    if (A.max >= B.tag.second) {
        A.max = B.tag.first;
        if (!A.tag.second) {
            A.tag.second = B.tag.second;
        } else {
            A.tag.second = min(A.tag.second, B.tag.second);
        }
        A.tag.first = B.tag.first;
    }
}
void apply_tag(Node &A, const pair<int, int> &B) {
    if (A.max >= B.second) {
        A.max = B.first;
        if (!A.tag.second) {
            A.tag.second = B.second;
        } else {
            A.tag.second = min(A.tag.second, B.second);
        }
        A.tag.first = B.first;
    }
}
void pushup(int x) {
    auto &&res = merge(tr[ls(x)], tr[rs(x)]);
    tr[x].max  = res.first;
    tr[x].sem  = res.second;
}
void pushdown(int x) {
    if (tr[x].tag.first) {
        apply_tag(tr[ls(x)], tr[x]);
        apply_tag(tr[rs(x)], tr[x]);
        tr[x].tag = make_pair(0, 0);
    }
}
void build(int rt, int l, int r) {
    tr[rt].l = l;
    tr[rt].r = r;
    if (l == r) {
        tr[rt].max = l;
        tr[rt].sem = -INF;
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
void update(int rt, int L, int R, int x, int y) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (tr[rt].max < y) {
        return;
    }
    if (l >= L && r <= R && tr[rt].sem < y) {
        apply_tag(tr[rt], make_pair(x, y));
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(rt), L, R, x, y);
    }
    if (mid < R) {
        update(rs(rt), L, R, x, y);
    }
    pushup(rt);
}
int query(int rt, int pos) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (l == r) {
        return tr[rt].max;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (pos <= mid) {
        return query(ls(rt), pos);
    } else {
        return query(rs(rt), pos);
    }
}
#undef ls
#undef rs
} // namespace SegmentBeats
int n, m, q;
array<int, N> lb, ans;
struct Query {
    int l, id;
};
vector<Query> qr[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        lb[r] = l;
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        qr[r].emplace_back(Query{l, i});
    }
    SegmentBeats::build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        if (lb[i]) {
            SegmentBeats::update(1, 1, lb[i], i, lb[i]);
        }
        for (auto &p : qr[i]) {
            ans[p.id] = SegmentBeats::query(1, p.l);
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

#势能线段树