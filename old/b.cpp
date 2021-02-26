#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll n, m, q, x, y;
bool cov = 0;
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}
ll getRegion(int cur, ll num) {
    if (cur == 1) {
        return ceil(1.0 * num / n);
    } else {
        return ceil(1.0 * num / m);
    }
}
int main() {
    cin >> n >> m >> q;
    ll d = gcd(n, m);
    n = n / d, m = m / d;
    if (d == 1) {
        while (q--) {
            ll tmp;
            cin >> tmp >> tmp >> tmp >> tmp;
            cout << "YES" << endl;
        }
        return 0;
    }
    while (q--) {
        ll x, y, c1, c2;
        cin >> c1 >> x >> c2 >> y;
        if (getRegion(c1, x) != getRegion(c2, y)) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}