### P4197 Peaks

在线做法

考虑这个东西肯定是在最小生成树上走最优

建出来克鲁斯卡尔重构树之后可以发现所有父节点的点权大于儿子的点权，这样向上跳到最大的不大于 $y$ 的点的叶子节点都是可达的

DFS序+主席树查询即可

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 7;
int n, m, q, id;
namespace KrTree {
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N * 2], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int val[N * 2];
int tid, pos[N * 2];
int fa[N][22];
int L[N * 2], R[N * 2];
void dfs(int x, int f) {
    L[x]     = ++tid;
    pos[tid] = x;
    fa[x][0] = f;
    for (int i = 1; i <= 19; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v != f) {
            dfs(v, x);
        }
    }
    R[x] = tid;
}
} // namespace KrTree

namespace MST {
struct Data {
    int u, v, w;
};
vector<Data> edge;
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void MST() {
    int tot = 0;
    for (int i = 1; i <= n * 2; i++) {
        fa[i] = i;
    }
    sort(edge.begin(), edge.end(), [](const Data &A, const Data &B) -> bool {
        return A.w < B.w;
    });
    for (auto d : edge) {
        int u = find(d.u), v = find(d.v);
        if (u != v) {
            KrTree::val[++id] = d.w;
            KrTree::add(id, u);
            KrTree::add(id, v);
            fa[u] = fa[v] = id;
            ++tot;
            if (tot == n - 1) {
                break;
            }
        }
    }
}
} // namespace MST
namespace PSegmentTree {
int tot;
int ls[N * 20], rs[N * 20], sum[N * 20];
void insert(int &now, int pre, int l, int r, int pos) {
    now      = ++tot;
    sum[now] = sum[pre] + 1;
    ls[now]  = ls[pre];
    rs[now]  = rs[pre];
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(ls[now], ls[pre], l, mid, pos);
    } else {
        insert(rs[now], rs[pre], mid + 1, r, pos);
    }
}
int query(int now, int pre, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    int x   = sum[rs[now]] - sum[rs[pre]];
    if (k <= x) {
        return query(rs[now], rs[pre], mid + 1, r, k);
    } else {
        return query(ls[now], ls[pre], l, mid, k - x);
    }
}
} // namespace PSegmentTree

int h[N], b[N];
int rt[N * 2];
int main() {
    cin >> n >> m >> q;
    id = n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        b[i] = h[i];
    }
    sort(b + 1, b + 1 + n);
    int lim = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; i++) {
        h[i] = lower_bound(b + 1, b + 1 + lim, h[i]) - b;
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        MST::edge.emplace_back(MST::Data{a, b, c});
    }
    MST::MST();
    KrTree::dfs(id, id);
    for (int i = 1; i <= id; i++) {
        if (KrTree::pos[i] <= n) {
            PSegmentTree::insert(rt[i], rt[i - 1], 1, lim, h[KrTree::pos[i]]);
        } else {
            rt[i] = rt[i - 1];
        }
    }
    using KrTree::fa;
    using KrTree::L;
    using KrTree::R;
    using KrTree::val;
    int ans = 0;
    while (q--) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        // if (ans != -1 && ans != 0) {
        //     x ^= ans;
        //     y ^= ans;
        //     k ^= ans;
        // }
        for (int i = 19; i >= 0; i--) {
            if (val[fa[x][i]] <= y) {
                x = fa[x][i];
            }
        }
        int res = PSegmentTree::sum[rt[R[x]]] - PSegmentTree::sum[rt[L[x] - 1]];
        if (res < k) {
            ans = -1;
            printf("%d\n", -1);
            continue;
        } else {
            ans = b[PSegmentTree::query(rt[R[x]], rt[L[x] - 1], 1, lim, k)];
            printf("%d\n", ans);
        }
    }
}
```