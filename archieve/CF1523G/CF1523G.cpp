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
