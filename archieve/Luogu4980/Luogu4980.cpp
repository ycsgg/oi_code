#include <iostream>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll phi(ll n) {
    ll res = 1;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            n /= i;
            res = res * (i - 1);
            while (n % i == 0) {
                n /= i;
                res = res * i;
            }
        }
    }
    if (n > 1) {
        res = res * (n - 1);
    }
    return res;
}

ll solve(ll n) {
    ll tot = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i)
            continue;
        tot += phi(i) * qpow(n, n / i - 1);
        if (i * i != n)
            tot += phi(n / i) * qpow(n, i - 1);
    }
    return tot % mod;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        cout << solve(n) << endl;
    }
}