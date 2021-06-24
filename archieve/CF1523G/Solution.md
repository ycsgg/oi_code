### CF1523G Try Booking

考虑设 $f(l,r)$ 表示 $[l,r]$ 的答案，那么每次需要支持找到一个最小的安排 $[x,y]$ 加上答案然后计算 $[l,x-1]$ $[y+1,r]$

如果我们让要求的区间长度递减，那就是往里插入新区间，查符合要求的最小的区间

这是一个二维问题，相当于在一个二维矩阵上单点修改子矩阵查询的问题

树套树可以解决，复杂度是 $O(n\log^3 n+m\log^2n)$

因为考虑每次调用 $f(l,r)$ 都会至少减去当前长度的区间，最多减去 $O(\frac{n}{l})$ 次，对其求和大概是 $O(n\ln n) $

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N   = 1e5 + 5;
const int INF = 0x7f7f7f7f;
namespace SegmentTree {
int rt[N];
#define ls(x) tr[x].ls
#define rs(x) tr[x].rs
struct Node {
    int ls, rs, mmin;
};
array<Node, N * 200> tr;
int tot;
void insert(int &rt, int l, int r, int pos, int v) {
    if (!rt) {
        rt          = ++tot;
        tr[rt].mmin = v;
    } else {
        tr[rt].mmin = min(tr[rt].mmin, v);
    }
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(ls(rt), l, mid, pos, v);
    } else {
        insert(rs(rt), mid + 1, r, pos, v);
    }
}
int query(int rt, int l, int r, int L, int R) {
    if (!rt) {
        return INF;
    }
    if (L <= l && R >= r) {
        return tr[rt].mmin;
    }
    int mid = (l + r) / 2;
    int res = INF;
    if (L <= mid) {
        res = min(res, query(ls(rt), l, mid, L, R));
    }
    if (mid < R) {
        res = min(res, query(rs(rt), mid + 1, r, L, R));
    }
    return res;
}
void dfs(int x, int l, int r) {
    if (!x) {
        return;
    }
    int mid = (l + r) / 2;
    dfs(ls(x), l, mid);
    dfs(rs(x), mid + 1, r);
}
#undef ls
#undef rs
} // namespace SegmentTree
int n, m;
namespace BIT {
using namespace SegmentTree;
int lowbit(int x) {
    return x & (-x);
}
void add(int l, int r, int v) {
    while (r <= n) {
        insert(rt[r], 1, n, l, v);
        r += lowbit(r);
    }
}
int query(int l, int r) {
    int res = INF;
    while (r >= l) {
        res = min(res, SegmentTree::query(rt[r], 1, n, l, n));
        r -= lowbit(r);
    }
    return res;
}
} // namespace BIT
vector<int> r, l, id;
int solve(int L, int R) {
    if (L > R)
        return 0;
    int cur = BIT::query(L, R);
    if (cur == INF)
        return 0;
    return r[cur] - l[cur] + 1 + solve(L, l[cur] - 1) + solve(r[cur] + 1, R);
}
int main() {
    cin >> n >> m;
    r.resize(m);
    l.resize(m);
    id.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        id[i] = i;
    }
    sort(id.begin(), id.end(), [&](const auto &x, const auto &y) -> bool {
        return r[x] - l[x] > r[y] - l[y];
    });
    int cur = 0;
    vector<int> ans(n + 1);
    for (int i = n; i >= 1; i--) {
        while (cur < m && r[id[cur]] - l[id[cur]] + 1 == i) {
            BIT::add(l[id[cur]], r[id[cur]], id[cur]);
            cur++;
        }
        ans[i] = solve(1, n);
    }
    for (int i = 1; i <= n;i++){
        cout << ans[i] << endl;
    }
        return 0;
}
// Asusetic eru quionours
```

#线段树

#树套树