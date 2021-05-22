#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N  = 1e6 + 5;
const ll mod = 998244353;
char s[N];
int n;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
int cntq1[N], cntl[N], cntr[N], cntq2[N];
ll fac[N], ifac[N];
ll C(ll n, ll m) {
    if (m < 0 || n - m < 0) {
        return 0;
    }
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int cnt;
int main() {
    cin >> s + 1;
    n      = strlen(s + 1);
    fac[0] = fac[1] = 1;
    for (int i = 1; i <= n; i++) {
        cnt += (s[i] == '?');
        fac[i]   = 1ll * fac[i - 1] * i % mod;
        cntq1[i] = cntq1[i - 1] + (s[i] == '?');
        cntl[i]  = cntl[i - 1] + (s[i] == '(');
    }
    fac[n + 1]  = 1ll * fac[n] * 1ll * (n + 1) % mod;
    ifac[n + 1] = qpow(fac[n + 1], mod - 2);
    ifac[0]     = 1;
    for (int i = n; i >= 1; i--) {
        ifac[i]  = 1ll * ifac[i + 1] * (i + 1) % mod;
        cntr[i]  = cntr[i + 1] + (s[i] == ')');
        cntq2[i] = cntq2[i + 1] + (s[i] == '?');
    }
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans = (ans +
               cntl[i] * C(cnt, cntq2[i + 1] + cntr[i + 1] - cntl[i]) % mod) %
              mod;
        ans = (ans + cntq1[i] *
                         C(cnt - 1, cntq2[i + 1] + cntr[i + 1] - cntl[i] - 1) %
                         mod) %
              mod;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours