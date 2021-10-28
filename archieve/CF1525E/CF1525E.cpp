#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 5e4 + 10;
const ll mod = 998244353;
const int N = 22;
int n, m;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
int buc[M][N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            buc[j][x]++;
        }
    }
    ll down = 1;
    for (int i = 1; i <= n; i++) {
        down = down * i % mod;
    }
    down = qpow(down, mod - 2);
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        ll sum = 0;
        ll res = 1;
        for (int j = n; j >= 1; j--) {
            sum += buc[i][j + 1];
            res = res * sum % mod;
            sum = (sum - 1);
        }
        res = res * down % mod;
        res = (1 - res + mod) % mod;
        ans = (ans + res) % mod;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours.