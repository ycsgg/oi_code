
#include <algorithm>
#include <iostream>
using namespace std;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
const int N   = 1e6 + 5;
const int mod = 1e9 + 7;
int n, p, q;
int v[N], cnt[N], d[N];
int tot[N];
int dp[2][N], ans[N];
int main() {
    cin >> n >> q >> p;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        v[i] = gcd(v[i], p);
    }
    cnt[1] = 2;
    for (int i = 2; i <= n; i++) {
        cnt[i] = 2ll * cnt[i - 1] % mod;
    }
    for (int i = 1; i <= n; i++) {
        cnt[i] = (cnt[i] - 1ll + mod) % mod;
    }
    int pcnt = 0;
    for (int i = 1; i * i <= p; i++) {
        if (p % i == 0) {
            d[++pcnt] = i;
        }
    }
    for (int i = pcnt; i > 1; i--) {
        if (p / d[i] != d[i]) {
            d[++pcnt] = p / d[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(d + 1, d + 1 + pcnt, v[i]) - d;
        tot[pos]++;
    }
    int now = 0;
    for (int i = 1; i <= pcnt; i++) {
        if (tot[i]) {
            now ^= 1;
            for (int j = 1; j <= pcnt; j++) {
                dp[now][j] = dp[now ^ 1][j];
            }
            for (int j = 1; j <= pcnt; j++) {
                if (dp[now ^ 1][j]) {
                    int k        = gcd(d[j], d[i]);
                    int pos      = lower_bound(d + 1, d + 1 + pcnt, k) - d;
                    dp[now][pos] = (dp[now][pos] +
                                    1ll * dp[now ^ 1][j] * cnt[tot[i]] % mod) %
                                   mod;
                }
            }
            dp[now][i] = (dp[now][i] + cnt[tot[i]] % mod) % mod;
        }
    }
    for (int i = 1; i <= pcnt; i++) {
        for (int j = 1; j <= i; j++) {
            if (d[i] % d[j] == 0) {
                ans[i] = (ans[i] + dp[now][j]) % mod;
            }
        }
    }
    while (q--) {
        int x;
        cin >> x;
        x       = gcd(x, p);
        int pos = lower_bound(d + 1, d + 1 + pcnt, x) - d;
        cout << ans[pos] << endl;
    }
    return 0;
}


