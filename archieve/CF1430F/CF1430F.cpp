#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
int n;
int k;
ll l[2003], r[2003], a[2003];
ll dp[2003];
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i] >> a[i];
    }
    for (int i = n; i >= 1; --i) {
        ll rq = a[i];
        if (i != n) {
            rq += (r[i] == l[i + 1] ? dp[i + 1] : 0);
        }
        if ((r[i] - l[i] + 1) * k < rq) {
            cout << -1 << endl;
            exit(0);
        }
        dp[i] = max(rq - (r[i] - l[i]) * k, 0ll);
    }
    ll ans = 0, cur = k;
    for (int i = 1; i <= n; ++i) {
        if (cur < dp[i]) {
            ans += cur;
            cur = k;
        }
        ans += a[i];
        cur = ((cur - a[i]) % k + k) % k;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours.