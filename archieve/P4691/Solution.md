### P3934 [Ynoi2016] 炸脖龙 I

~~P4691 Nephren Ruq Insania~~

在指数上做文章还要模一看就很扩展欧拉定理

开个节点记录以下当前是否大于$\phi(p)$，然后递归求解

修改用树状数组即可，（大概是最简单的YNOI吧）

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
int n, q;
const int N = 500005, M = 20000000 + 6;
int prime[M], phi[M], pcnt;
bool vis[M];
struct Node {
    ll val;
    bool type;
};
ll qpow(ll a, ll b, ll mod) {
    a %= mod;
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
void init() {
    for (int i = 2; i < M; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            phi[i]        = i - 1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] >= M) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
ll c[N];
int lowbit(int x) {
    return x & (-x);
}
void update(int pos, ll val) {
    while (pos <= n) {
        c[pos] += val;
        pos += lowbit(pos);
    }
}
void add(int l, int r, ll x) {
    update(l, x);
    update(r + 1, -x);
}
ll _query(int pos) {
    ll res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
Node power(ll a, ll t, ll p) {
    Node res = {1, 0};
    if (a >= p) {
        a %= p;
        res.type = 1;
    }
    while (t) {
        if (t & 1)
            res.val *= a;
        if (res.val >= p) {
            res.type = 1;
            res.val %= p;
        }
        a = a * a;
        if (a >= p) {
            res.type = 1;
            a %= p;
        }
        t >>= 1;
    }
    return res;
}
Node query(int l, int r, ll p) {
    ll sum = _query(l);
    Node res;
    if (p == 1) {
        return (Node){0, 1};
    }
    if (sum == 1) {
        return (Node){1, 0};
    }
    if (l == r) {
        return sum < p ? (Node){sum, 0} : (Node){sum % p, 1};
    }
    res = query(l + 1, r, phi[p]);
    if (res.type) {
        res.val += phi[p];
    }
    return power(sum, res.val, p);
}
int main() {
    cin >> n >> q;
    init();
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        add(i, i, x);
    }
    while (q--) {
        int op, l, r;
        ll v;
        cin >> op >> l >> r >> v;
        if (op == 1) {
            add(l, r, v);
        } else {
            cout << query(l, r, v).val << endl;
        }
    }
    return 0;
}
```