#include <iostream>
using namespace std;
const int N = 300005, mod = 1000000007;

int n, mx, m;
int a[N], b[N], dp[N];
int pcnt, primes[N], phi[N];
bool vis[N];

void pre(int n) {
    pcnt   = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            primes[++pcnt] = i;
            phi[i]         = i - 1;
        }
        for (int j = 1; j <= pcnt && primes[j] * i <= n; ++j) {
            vis[primes[j] * i] = 1;
            if (i % primes[j] == 0) {
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            } else {
                phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ++a[x];
        mx = max(mx, x);
    }
    m = 0;
    while ((1 << m) <= mx) {
        ++m;
    }
    pre(N - 1);
    dp[0] = 1, b[0] = 0;
    for (int i = 1; i < (1 << m); ++i) {
        b[i] = b[i >> 1] << 1 | 1;
        if (a[i]) {
            int mask = b[i] ^ i;
            for (int S = mask;; S = (S - 1) & mask) {
                dp[S | i] = (dp[S | i] + 1ll * dp[S] * a[i]) % mod;
                if (!S) {
                    break;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << m); ++i) {
        ans = (ans + 1ll * dp[i] * phi[i + 1]) % mod;
    }
    for (int i = 0; i < a[0]; ++i) {
        ans = 2 * ans % mod;
    }
    cout << ans << endl;
}
// Asusetic eru quionours
