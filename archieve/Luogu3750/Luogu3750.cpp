#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 100003;
const int N = 100002;
int n, k, a[N];
ll dp[N], inv[N];
vector<int> factor[N];
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
    }
    ll ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            factor[j].push_back(i);
        }
    }
    for (int i = n; i >= 1; i--) {
        if (a[i]) {
            for (auto v : factor[i]) {
                a[v] ^= 1;
            }
            cnt++;
        }
    }
    if (cnt <= k) {
        ans = cnt;
    } else {
        dp[n] = 1;
        for (int i = n - 1; i >= 1; i--) {
            dp[i] = (1 + (n - i) * (dp[i + 1] + 1) * inv[i]) % mod;
        }
        for (int i = cnt; i > k; i--) {
            ans = (ans + dp[i]) % mod;
        }
        ans = (ans + k) % mod;
    }
    for (int i = 1; i <= n; i++)
        ans = (ans * i) % mod;
    printf("%lld", ans);
    return 0;
}
// Asusetic eru quionours.