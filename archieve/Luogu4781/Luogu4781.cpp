#include <iostream>
using namespace std;
#define int long long
const int mod = 998244353;
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
int lagrange(int n, int *x, int *y, int xi) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int s1 = 1, s2 = 1;
        for (int j = 1; j <= n; j++)
            if (i != j) {
                s1 = 1ll * s1 * (xi - x[j]) % mod;
                s2 = 1ll * s2 * (x[i] - x[j]) % mod;
            }
        ans =
            (1ll * ans + 1ll * y[i] * s1 % mod * qpow(s2, mod - 2) % mod) % mod;
    }
    return (ans + mod) % mod;
}
const int N = 20005;
int n, k;
int x[N], y[N];
signed main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    cout << lagrange(n, x, y, k);
    return 0;
}
