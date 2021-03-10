#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int N = 5e6;
long long n, mod, inv2, inv6, s[N + 2];
int phi[N + 2], prime[N + 1], pcnt, pn;
bool vis[N + 3];
unordered_map<int, ll> s_map;
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
void init() {
    phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            phi[i]        = i - 1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i <= N; i++)
        s[i] = (1ll * i * i % mod * phi[i] % mod + s[i - 1]) % mod;
}

ll s3(ll k) {
    k %= mod;
    return (k * (k + 1) / 2) % mod * ((k * (k + 1) / 2) % mod) % mod;
}
ll s2(ll k) {
    k %= mod;
    return k * (k + 1) % mod * (k * 2 + 1) % mod * inv6 % mod;
}
ll calc(ll k) {
    if (k <= N)
        return s[k];
    if (s_map.count(k))
        return s_map[k];
    long long res = s3(k), pre = 1, cur;
    for (ll l = 2, r; l <= k; l = r + 1) {
        r   = k / (k / l);
        res = (res - calc(k / l) * (s2(r) - s2(l - 1) + mod) % mod + mod) % mod;
    }
    s_map[k] = (res + mod) % mod;
    return s_map[k];
}
int main() {
    cin >> mod >> n;
    inv2 = qpow(2, mod - 2), inv6 = qpow(6, mod - 2);
    init();
    ll res = 0, cur, pre = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        r   = n / (n / l);
        cur = calc(r);
        res = (res + (s3(n / l) * (cur - pre + mod) % mod) % mod) % mod;
        pre = cur;
    }
    cout << res;
    return 0;
}