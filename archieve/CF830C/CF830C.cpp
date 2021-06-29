#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int n;
ll k, sum;
int main() {
    cin >> n >> k;
    vector<ll> a(n);
    sum     = k;
    ll mmax = -1;
    for (auto &v : a) {
        cin >> v;
        sum += v;
        mmax = max(mmax, v);
    }
    ll ans = 0;
    for (ll l = 1, r; l <= mmax; l = r + 1) {
        r      = (1ll << 62);
        ll res = 0;
        for (auto x : a) {
            if (x > l) {
                r = min(r, (x - 1) / ((x - 1) / l));
            }
        }
        for (auto x : a) {
            res += (x - 1) / l + 1;
        }
        ll d = sum / res;
        if (d >= l && d <= r) {
            ans = max(ans, d);
        }
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours