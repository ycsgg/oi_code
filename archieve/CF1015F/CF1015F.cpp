#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 305;
ll dp[N][N][N];
char s[N];
int nxt[N], trans[N][2];
int n, m;
void KMP(char *s, int n) {
    int j = nxt[1] = 0;
    for (int i = 2; i <= n; i++) {
        while (j && s[i] != s[j + 1]) {
            j = nxt[j];
        }
        if (s[i] == s[j + 1]) {
            j++;
        }
        nxt[i] = j;
    }
    for (int i = 0; i < m; i++) {
        int p1 = i, p2 = i;
        while (p1 && s[p1 + 1] != '(') {
            p1 = nxt[p1];
        }
        while (p2 && s[p2 + 1] != ')') {
            p2 = nxt[p2];
        }
        if (s[p1 + 1] == '(') {
            p1++;
        }
        if (s[p2 + 1] == ')') {
            p2++;
        }
        trans[i][1] = p1;
        trans[i][0] = p2;
    }
    trans[m][0] = trans[m][1] = m;
}
int main() {
    cin >> n;
    n *= 2;
    cin >> (s + 1);
    m = strlen(s + 1);
    KMP(s, m);
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n / 2; j++) {
            for (int k = 0; k <= m; k++) {
                auto val = dp[i][j][k];
                if (j) {
                    dp[i + 1][j - 1][trans[k][0]] =
                        (dp[i + 1][j - 1][trans[k][0]] + val) % mod;
                }
                dp[i + 1][j + 1][trans[k][1]] =
                    (dp[i + 1][j + 1][trans[k][1]] + val) % mod;
            }
        }
    }
    cout << dp[n][0][m];
    return 0;
}
// Asusetic eru quionours.