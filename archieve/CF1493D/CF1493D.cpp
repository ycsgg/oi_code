#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
namespace Sieve {
vector<int> factor[N];
int prime[N], pcnt;
bool vis[N];
void Sieve(int lim) {
    for (int i = 2; i < lim; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (1ll * prime[j] * i > lim) {
                break;
            }
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
    for (int i = 1; i <= pcnt; i++) {
        for (int j = 1; 1ll * prime[i] * j <= lim; j++) {
            factor[prime[i] * j].push_back(prime[i]);
        }
    }
}
} // namespace Sieve

namespace SegmentTree {
int ls[N * 50], rs[N * 50];
int val[N * 50];
int root[N];
int tot;
void pushup(int x) {
    val[x] = min(val[ls[x]], val[rs[x]]);
}
void add(int &x, int l, int r, int pos, int v) {
    if (!x) {
        x = ++tot;
    }
    if (l == r) {
        val[x] += v;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        add(ls[x], l, mid, pos, v);
    } else {
        add(rs[x], mid + 1, r, pos, v);
    }
    pushup(x);
}
int query(int x) {
    return val[root[x]];
}
} // namespace SegmentTree
using ll = long long;
const ll mod = 1e9 + 7;
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
int n, m;
int ans = 1;
void mul(int pos, int x) {
    using namespace Sieve;
    for (auto v : factor[x]) {
        auto now = SegmentTree::query(v);
        if (now != 0) {
            ans = 1ll * ans * qpow(qpow(v, now), mod - 2) % mod;
        }
        int cnt = 0;
        int tmp = x;
        while (tmp % v == 0) {
            tmp /= v;
            cnt++;
        }
        SegmentTree::add(SegmentTree::root[v], 1, n, pos, cnt);
        ans = 1ll * ans * qpow(v, SegmentTree::query(v)) % mod;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Sieve::Sieve(200000);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mul(i, x);
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        mul(x, y);
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.
