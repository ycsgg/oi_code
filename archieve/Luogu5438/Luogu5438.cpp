#include <array>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int LIM = 1e7 + 1;
#define int ll
ll l, r;
int mu[LIM], mu2[LIM], prime[LIM], pcnt, smu[LIM];
bool vis[LIM];
int lim = 0;
void Sieve(int up) {
    mu[1] = 1;
    lim = up;
    for (int i = 2; i <= up; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > up) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= up; i++) {
        smu[i] = smu[i - 1] + mu[i];
        mu2[i] = mu2[i - 1] + mu[i] * mu[i];
    }
}
ll solve(int x) {
    ll res = x;
    if (x < lim) {
        return x - mu2[x];
    }
    int upl = sqrt(x);
    for (int l = 2, r; l * l <= x; l = r + 1) {
        r = min(upl, (int)sqrt(x / (x / l / l)));
        res += (smu[r] - smu[l - 1]) * (x / l / l);
    }
    return x - res;
}
signed main() {
    cin >> l >> r;
    l--;
    Sieve(sqrt(r));
    int upl = l;
    int ans = solve(r) - solve(l);
    for (int c = 2; c * c <= r; c++) {
        int p = l / c / c;
        int q = min(upl, (int)r / c / c);
        if (p < q) {
            ans -= q - solve(q) - p + solve(p);
        }
        upl = p;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours