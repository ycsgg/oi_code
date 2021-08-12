#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int LIM = 5000000;
ll mu[LIM];
unordered_map<ll, ll> mp;
int vis[LIM], prime[LIM], pcnt;
ll qpow(ll a, ll b) {
    b %= mod - 1;
    if (b < 0) {
        b += mod - 1;
    }
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
void Sieve() {
    mu[1] = 1;
    for (int i = 2; i < LIM; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] >= LIM) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i < LIM; i++) {
        mu[i] += mu[i - 1];
    }
}
ll solve(ll x) {
    if (x < LIM) {
        return mu[x];
    }
    if (mp.count(x)) {
        return mp[x];
    }
    ll ans = 1;
    for (ll l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= solve(x / l) * (r - l + 1);
    }
    mp[x] = ans;
    return ans;
}
ll n, k, L, R;
int main() {
    Sieve();
    cin >> n >> k >> L >> R;
    R /= k;
    L = L / k + (L % k != 0);
    ll ans = 0;
    L--;
    for (ll l = 1, r; l <= R; l = r + 1) {
        if (!(L / l)) {
            r = R / (R / l);
        } else {
            r = min(L / (L / l), R / (R / l));
        }
        ans = (ans + qpow(R / l - L / l, n) *
                         (solve(r) - solve(l - 1) + mod % mod) % mod) %
              mod;
    }
    cout << (ans + mod) % mod << endl;
    return 0;
}
// Asusetic eru quionours