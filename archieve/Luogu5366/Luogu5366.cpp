#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
ll getMu(ll x) {
    ll res = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i) {
            continue;
        }
        if (x % (i * i) == 0) {
            return 0;
        }
        x /= i;
        res = -res;
    }
    if (x > 1) {
        res = -res;
    }
    return (res + mod) % mod;
}
ll n, l, g;
ll p2[8080], ans[8080];
int factor[8080], cnt;
int tot[8080][8080];
map<ll, ll> mu;
vector<int> d[8080], rd[8080];
int main() {
    cin >> n >> g >> l;
    if (l % g != 0) {
        int q;
        cin >> q;
        while (q--) {
            cout << 0 << endl;
        }
        return 0;
    }
    l /= g;
    n /= g;
    for (int i = 1; i * i <= l; i++) {
        if (l % i)
            continue;
        factor[++cnt] = i;
        if (i * i != l) {
            factor[++cnt] = l / i;
        }
    }
    sort(factor + 1, factor + 1 + cnt);
    p2[0] = 1;
    for (int i = 1; i <= cnt; i++) {
        p2[i] = p2[i - 1] * 2 % mod;
    }
    int mmax = 0;
    for (int i = 1; i <= cnt; i++) {
        if (factor[i] <= n) {
            mmax = max(mmax, factor[i]);
        }
        mu[factor[i]] = getMu(factor[i]);
        for (int j = 1; j <= i; j++) {
            if (factor[i] % factor[j] == 0) {
                rd[i].push_back(j);
                d[j].push_back(i);
            }
        }
    }
    for (int i = 1; i <= cnt; i++) {
        for (auto v : rd[i]) {
            int pos = lower_bound(factor + 1, factor + 1 + cnt,
                                  factor[i] / factor[v]) -
                      factor;
            for (auto p : rd[pos]) {
                if (factor[p] * factor[v] <= mmax) {
                    tot[v][i]++;
                }
            }
        }
    }
    for (int i = 1; i <= cnt; i++) {
        for (auto v : d[i]) {
            for (auto p : d[v]) {
                if (tot[i][p]) {
                    ans[v] = (ans[v] + p2[tot[i][p] - 1] * mu[factor[i]] % mod *
                                           mu[l / factor[p]] % mod) %
                             mod;
                }
            }
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        ll x;
        cin >> x;
        if (x % g || l % (x / g) || x > n * g) {
            cout << 0 << endl;
            continue;
        }
        int pos = lower_bound(factor + 1, factor + 1 + cnt, x / g) - factor;
        cout << ans[pos] << endl;
    }
    return 0;
}
// Asusetic eru quionours