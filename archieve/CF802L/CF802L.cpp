#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const ll mod = 1e9 + 7;
ll k[N], b[N];
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} Tr;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
void dfs(int x, int fa) {
    ll down = 0;
    if (Tr.edge[x].size() == 1) {
        // cout << "!";
        return;
    }
    k[x] = 1;
    for (auto e : Tr.edge[x]) {
        int v = e.v;
        int w = e.w;
        b[x] = (b[x] + w) % mod;
        if (v == fa) {
            continue;
        }
        dfs(v, x);
        down = (down + k[v]) % mod;
        b[x] = (b[x] + b[v]) % mod;
    }
    down = qpow((Tr.edge[x].size() - down + mod) % mod, mod - 2);
    k[x] = 1ll * k[x] * down % mod;
    b[x] = 1ll * b[x] * down % mod;
}
int n;
int main() {
    cin >> n;+
    for (int i = 1; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        Tr.add(x, y, w);
        Tr.add(y, x, w);
    }
    dfs(0, -1);
    cout << b[0];
    return 0;
}
// Asusetic eru quionours.