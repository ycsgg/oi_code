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