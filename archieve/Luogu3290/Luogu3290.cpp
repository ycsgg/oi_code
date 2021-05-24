#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 105, M = 13;
const int mod = 1e9 + 7;
int n, m, c, q;
int dp[2][(1 << M)][7][7];
char c1[7], c2[7];
int a1[7], a2[7], nxt1[7], nxt2[7], to1[7][4], to2[7][4];
void KMP(int *s, int *nxt) {
    int j = 0;
    for (int i = 2; i <= c; i++) {
        if (j && s[j + 1] != s[i]) {
            j = nxt[j];
        }
        if (s[j + 1] == s[i]) {
            j++;
        }
        nxt[i] = j;
    }
}
void pre(int *s, int *nxt, int to[][4]) {
    for (int i = 0; i < c; i++) {
        for (int j = 0; j <= 2; j++) {
            int k = i;
            while (k && s[k + 1] != j) {
                k = nxt[k];
            }
            if (s[k + 1] == j) {
                k++;
            }
            to[i][j] = k;
        }
    }
}
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
int main() {
    cin >> n >> m >> c >> q;
    int U      = 1 << (m - c + 1);
    auto trans = [](char c) -> int {
        if (c == 'W')
            return 0;
        if (c == 'B')
            return 1;
        if (c == 'X')
            return 2;
        return 0;
    };
    while (q--) {
        cin >> c1 + 1 >> c2 + 1;
        for (int i = 1; i <= c; i++) {
            a1[i] = trans(c1[i]);
            a2[i] = trans(c2[i]);
        }
        KMP(a1, nxt1);
        KMP(a2, nxt2);
        pre(a1, nxt1, to1);
        pre(a2, nxt2, to2);
        memset(dp[0], 0, sizeof(dp[0]));
        dp[0][0][0][0] = 1;
        int now        = 1;
        for (int i = 1; i <= n; i++) {
            memset(dp[now], 0, sizeof(dp[now]));
            for (int s = 0; s < U; s++) {
                for (int a = 0; a < c; a++) {
                    for (int b = 0; b < c; b++) {
                        dp[now][s][0][0] += dp[now ^ 1][s][a][b];
                        dp[now][s][0][0] %= mod;
                    }
                }
            }
            now ^= 1;
            for (int j = 1; j <= m; j++) {
                memset(dp[now], 0, sizeof(dp[now]));
                for (int s = 0; s < U; s++) {
                    for (int a = 0; a < c; a++) {
                        for (int b = 0; b < c; b++) {
                            if (!dp[now ^ 1][s][a][b])
                                continue;
                            for (int p = 0; p <= 2; p++) {
                                int pa = to1[a][p];
                                int pb = to2[b][p];
                                int S  = s;
                                if (j >= c) {
                                    if ((S >> (j - c)) & 1) {
                                        S ^= 1 << (j - c);
                                    }
                                }
                                if (pa == c) {
                                    S ^= 1 << (j - c);
                                    pa = nxt1[c];
                                }
                                if (pb == c) {
                                    if ((s >> (j - c)) & 1) {
                                        continue;
                                    }
                                    pb = nxt2[c];
                                }
                                dp[now][S][pa][pb] += dp[now ^ 1][s][a][b];
                                dp[now][S][pa][pb] %= mod;
                            }
                        }
                    }
                }
                now ^= 1;
            }
        }
        ll ans = qpow(3, n * m);
        for (int i = 0; i < U; i++) {
            for (int j = 0; j < c; j++) {
                for (int k = 0; k < c; k++) {
                    ans = (ans - dp[now ^ 1][i][j][k] + mod) % mod;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours