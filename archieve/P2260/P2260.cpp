
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 19940417;
ll inv2 = 9970209, inv6 = 3323403;
ll sum1(ll n) {
    return ((1ll * n * (n + 1) % mod) * inv2) % mod;
}
ll sum2(ll n) {
    return (((1ll * n * (n + 1) % mod) * (2 * n + 1) % mod) * inv6) % mod;
}
ll ans, ans1, ans2, ans3, n, m;
int main() {
    cin >> n >> m;
    if (n > m)
        swap(n, m);
    ans1 = (1ll * n * n) % mod;
    for (ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        ans1 =
            (ans1 - (((n / i) * ((sum1(j) - sum1(i - 1) + mod) % mod)) % mod) +
             mod) %
            mod;
    }
    ans2 = 1ll * m * m % mod;
    for (ll i = 1, j; i <= m; i = j + 1) {
        j = m / (m / i);
        ans2 =
            (ans2 - (((m / i) * ((sum1(j) - sum1(i - 1) + mod) % mod)) % mod) +
             mod) %
            mod;
    }
    ans  = 1ll * ans1 * ans2 % mod;
    ans3 = n * m % mod;
    ans3 = ans3 * n % mod;
    for (ll i = 1, j; i <= n; i = j + 1) {
        j    = min(m / (m / i), n / (n / i));
        ans3 = (ans3 -
                ((((((m / i) * ((sum1(j) - sum1(i - 1) + mod) % mod)) % mod) *
                   (((1) * n) % mod)) %
                  mod) +
                 mod) %
                    mod);
        ans3 = (ans3 -
                ((((((n / i) * ((sum1(j) - sum1(i - 1) + mod) % mod)) % mod) *
                   (((1) * m) % mod)) %
                  mod) +
                 mod) %
                    mod);
        ans3 = (ans3 + (((((m / i) * (n / i)) % mod) *
                         ((sum2(j) - sum2(i - 1) + mod) % mod)) %
                        mod) %
                           mod) %
               mod;
    }
    ans = (ans - ans3 + mod) % mod;
    printf("%lld", ans);
    return 0;
}


