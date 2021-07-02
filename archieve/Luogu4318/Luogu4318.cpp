#include <array>
#include <iostream>
using namespace std;
const int N = 60010;
using ll    = long long;
array<ll, N> mu, prime;
array<bool, N> vis;
int pcnt;
void pre() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i]         = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] >= N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}
bool check(ll x, ll k) {
    ll res = 0;
    for (ll i = 1; i * i <= x; i++) {
        res += mu[i] * (x / i / i);
    }
    return res >= k;
}
int T;
int main() {
    pre();
    cin >> T;
    while (T--) {
        ll k;
        cin >> k;
        ll l = k, r = k * 2, ans;
        while (l <= r) {
            ll mid = (l + r) / 2;
            if (check(mid, k)) {
                r   = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours