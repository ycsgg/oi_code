#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 5005;
const ll mod = 998244353;
ll pw[N];
ll sum[N];
int main() {
    int n, m;
    cin >> n >> m;
    ll ans = m;
    pw[0] = 1;
    for (int i = 1; i <= m; i++) {
        sum[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * m % mod;
    }
    for (int i = 2; i <= n; i++) {
        auto pre = ans;
        ans = 0;
        if (i > 2) {
            for (int j = 1; j <= m; j++) {
                sum[j] = (sum[j] * (m - j) % mod + pw[i - 2]) % mod;
            }
        }
        for (int j = 1; j <= m; j++) {
            ans = (ans + (pre + pw[i - 1] - sum[j] + mod) % mod) % mod;
        }
    }
    cout << ans << '\n';
    return 0;
}
// Asusetic eru quionours.