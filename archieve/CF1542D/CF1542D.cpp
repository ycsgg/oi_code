#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N  = 2085;
using ll     = long long;
const ll mod = 998244353;
int n;
struct Data {
    char opt;
    ll val;
};
array<Data, N> a;
array<int, N> opt;
ll dp[N][N];
ll solve(int x) {
    for (int i = 1; i <= n; i++) {
        if (a[i].opt == '-') {
            opt[i] = -1;
        } else {
            opt[i] = (a[i].val == a[x].val ? (i <= x) : a[i].val <= a[x].val);
        }
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i <= n - 1; i++) {
        for (int j = 0; j <= n; j++) {
            if (i + 1 != x) {
                dp[i + 1][j] += dp[i][j];
                dp[i + 1][j] %= mod;
            }
            if (j + opt[i + 1] == -1) {
                if (i < x) {
                    dp[i + 1][0] += dp[i][j];
                    dp[i + 1][0] %= mod;
                }
            } else {
                dp[i + 1][j + opt[i + 1]] += dp[i][j];
                dp[i + 1][j + opt[i + 1]] %= mod;
            }
        }
        if (i + 1 >= x) {
            dp[i + 1][0] = 0;
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        res += dp[n][i];
        res %= mod;
    }
    return res;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].opt;
        if (a[i].opt == '+') {
            cin >> a[i].val;
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i].opt == '+') {
            res += 1ll * a[i].val * solve(i) % mod;
            res %= mod;
        }
    }
    cout << res << endl;
    return 0;
}
// Asusetic eru quionours