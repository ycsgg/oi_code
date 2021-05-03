### P3226 [HNOI2012]集合选数

tql

考虑构造如下的矩阵
$\begin{bmatrix} \begin{array}{c} 1 & 2^1 & 2^2 & \dots\\ 3^1 & 3^12^1 & 3^12^2 & \dots \\ 3^2 & 3^22^1 & 3^22^2 & \dots \\ \vdots & \vdots & \vdots & \ddots \end{array}\end{bmatrix}$

要求选出一些数字且数字不相邻的方案数

状压即可，而对于不全是 $2^x3^y$ 的数字可以都建矩阵跑

最后把答案乘起来

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1000000001;
bool ok[1 << 18];
const int N = 21;
int n;
int a[N][N], line[N], row;
bool vis[100005];
void build(int x) {
    for (int i = 1; i <= 12; i++) {
        if (i == 1) {
            a[i][1] = x;
        } else {
            a[i][1] = a[i - 1][1] * 3;
        }
        if (a[i][1] > n) {
            break;
        }
        row          = i;
        line[i]      = 1;
        vis[a[i][1]] = 1;
        for (int j = 2; j <= 18; j++) {
            a[i][j] = a[i][j - 1] * 2;
            if (a[i][j] > n) {
                break;
            }
            line[i]      = j;
            vis[a[i][j]] = 1;
        }
    }
}
ll dp[N][(1 << 18)];
ll solve(int x) {
    ll res = 0;
    for (int i = 0; i < (1 << line[1]); i++) {
        dp[1][i] = ok[i];
    }
    for (int i = 2; i <= row; i++) {
        for (int j = 0; j < (1 << line[i]); j++) {
            if (!ok[j])
                continue;
            dp[i][j] = 0;
            for (int k = 0; k < (1 << line[i - 1]); k++) {
                if (ok[k] && ((k & j) == 0)) {
                    dp[i][j] += dp[i - 1][k];
                    dp[i][j] %= mod;
                }
            }
        }
    }
    for (int i = 0; i < (1 << line[row]); i++) {
        res += dp[row][i];
        res %= mod;
    }
    return res;
}
int main() {
    cin >> n;
    for (int i = 0; i < (1 << 18); i++) {
        ok[i] = ((i << 1) & i) ? 0 : 1;
    }
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            build(i);
            ans = ans * solve(i) % mod;
        }
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours

```