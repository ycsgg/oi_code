### AT4144 [ARC098D] Donation

显然一个点如果支付了费用就不会再访问了，因为考虑留下的费用越多越好，如果之后还会访问那不如最后支付费用

我们假设当前钱是 $x$ 先选 $i$ 点支付然后去 $j$ 和先去 $j$ 再去 $i$ 有两种条件

即 $x\ge a_i+b_j$ 与 $x \ge a_j+b_i$

要求最小则当且仅当 $a_i+b_j \le a_j+b_i \Rightarrow a_i-b_i \le a_j-b_j$ 才选 $i$

记 $c_i=\max(a_i-b_i,0)$

对于一个点 $i$ 来说它的剩余钱数至少为 $c_i$

~~很自然的想到排序按顺序做~~ 

但是这样是忽略的图的限制的

那么我们继续考虑，选一个点之后剩下了几个连通块，先把几个连通块支付完再支付这个点然后是另一个联通块

按上面的条件仅需选择 $c_i$ 最大的点

这样一直选下去会构成一个树形结构，并且有 $c_i \le c_{fa_i}$

这样就可以排序然后并查集求出树了

之后在树上dp，记 $dp_i$ 为 $i$ 与它的子树的代价

那么 $dp_i=\min\limits_{v\in son(i)}(\sum\limits_{t\in subtree(i)}b_t-\sum\limits_{t\in subtree(v)}b_t+\max(dp_v,c+v))$

叶子当然是 $\max(a_i,b_i)$

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 105000;
typedef long long ll;
int f[N];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int x, int y) {
    x    = find(x);
    y    = find(y);
    f[x] = y;
}
vector<int> Tr[N], G[N];
ll dp[N], s[N];
int c[N], b[N];
void pre(int x) {
    s[x] = b[x];
    for (auto v : Tr[x]) {
        pre(v);
        s[x] += s[v];
    }
}
void dfs(int x) {
    if (!Tr[x].size())
        dp[x] = b[x] + c[x];
    else
        dp[x] = 2e19;
    for (auto v : Tr[x]) {
        dfs(v);
        dp[x] = min(dp[x], s[x] - s[v] + max((ll)c[x], dp[v]));
    }
}
bool cmp(const int &A, const int &B) {
    return c[A] < c[B];
}
int n, m, p[N];
bool vis[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> b[i];
        f[i] = i;
        c[i] = max(c[i] - b[i], 0);
        p[i] = i;
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    sort(p + 1, p + n + 1, cmp);
    for (int t = 1; t <= n; t++) {
        int u = p[t];
        for (auto v : G[u]) {
            if (vis[v]) {
                v = find(v);
                u = find(u);
                if (u != v) {
                    merge(v, u);
                    Tr[u].push_back(v);
                }
            }
        }
        vis[u] = 1;
    }
    pre(p[n]);
    dfs(p[n]);
    cout << dp[p[n]];
    return 0;
}
// Asusetic eru quionours
```