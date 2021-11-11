#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int mod = 998244353;
ll f[100001], g[100001];
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        ll res = 0;
        for (int i = n - 1; i >= 1; i--) {
            f[a[i + 1]] = (f[a[i + 1]] + 1) % mod;
            for (int l = 1, r; l <= a[i + 1]; l = r + 1) {
                r = a[i + 1] / (a[i + 1] / l);
                auto now = a[i + 1] / l;
                g[now] = f[now];
                f[now] = 0;
            }
            for (int l = 1, r; l <= a[i + 1]; l = r + 1) {
                r = a[i + 1] / (a[i + 1] / l);
                auto now = a[i + 1] / l;
                if (!g[now]) {
                    continue;
                }
                auto k = (a[i] + now - 1) / now;
                f[a[i] / k] = (f[a[i] / k] + g[now]) % mod;
                res = (res + 1ll * g[now] * i % mod * (k - 1) % mod) % mod;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int l = 1, r; l <= a[i]; l = r + 1) {
                f[a[i] / l] = 0;
                r = a[i] / (a[i] / l);
            }
        }
        cout << res << '\n';
    }
    return 0;
}
// Asusetic eru quionours.