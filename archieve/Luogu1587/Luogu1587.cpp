#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using ll    = long long;
const int N = 1e6 + 10;
ll _g[N], mu[N], f[N];
bool vis[N];
int prime[N], pcnt;
ll n, k, m;
ll g(int x) {
    return x / k * _g[k] + _g[x % k];
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
void pre() {
    for (int i = 1; i <= k; i++) {
        _g[i] = _g[i - 1] + (gcd(i, k) == 1);
    }
    mu[1] = f[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i]         = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] >= N)
                break;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
        f[i] = f[i - 1] + mu[i] * ((gcd(i, k) == 1));
    }
}
unordered_map<int, ll> mf;
ll F(int x) {
    if (x < N) {
        return f[x];
    }
    if (mf.count(x)) {
        return mf[x];
    }
    int res = 1;

    for (int l = 2, r; l <= x; l = r + 1) {
        r = (x / (x / l));
        res -= F(x / l) * (g(r) - g(l - 1));
    }

    mf[x] = res;
    return res;
}
int main() {
    cin >> n >> m >> k;
    pre();
    ll ans = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += 1LL * (n / l) * g(m / l) * (F(r) - F(l - 1));
    }
    cout << ans << endl;
}
// Asusetic eru quionours
