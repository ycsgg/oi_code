###  P4151 [WC2011]最大XOR和路径

我们发现如果一条路径被重复经过两次，那他对答案没用贡献但是可以通过它到达另一些点

那我们先随便选一个 $1 \rightarrow n$ 的路径，然后考虑用一些环去拓展它

而环到链连接的边 $e$ 则完全不会被计算

这样只需要把所有的环扔进线性基然后查询异或最大值即可

而最初的链不管怎么选都是不影响最终答案的

因为假设有两个链 $A$ $B$ ，那么 $A$ $B$ 就构成了 $1 \leftrightarrow n$ 的环，那么如果 $A$ 更优秀就会异或上这个大环来变成 $A$

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
namespace xor_base {
array<ll, 88> base;
bool insert(ll x) {
    for (int i = 63; ~i; i--) {
        if ((x >> i) & 1) {
            if (!base[i]) {
                base[i] = x;
                return 1;
            }
            x ^= base[i];
        }
    }
    return 0;
}
ll query(ll v) {
    ll res = v;
    for (int i = 63; ~i; i--) {
        res = max(res, res ^ base[i]);
    }
    return res;
}
} // namespace xor_base
const int N = 50050;
struct Graph {
    struct Node {
        int v;
        ll w;
    };
    vector<Node> edge[N];
    void add(int u, int v, ll w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
int n, m;
array<ll, N> val;
array<bool, N> vis;
void dfs(int x, ll now) {
    val[x] = now;
    vis[x] = 1;
    for (auto e : G.edge[x]) {
        if (!vis[e.v]) {
            dfs(e.v, now ^ e.w);
        } else {
            xor_base::insert(now ^ e.w ^ val[e.v]);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        G.add(u, v, w);
        G.add(v, u, w);
    }
    dfs(1, 0);
    cout << xor_base::query(val[n]);
    return 0;
}
// Asusetic eru quionours
```