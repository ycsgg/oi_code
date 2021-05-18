#include <cstring>
#include <iostream>
using namespace std;
const int N = 500005;
int n;
char s[N];
int nxt[N];
int dp[N];
int pos[N];
int main() {
    cin >> s + 1;
    n      = strlen(s + 1);
    nxt[0] = -1;
    nxt[1] = 0;
    dp[1]  = 1;
    pos[1] = 1;
    int j  = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = i;
        while (j != -1 && s[j + 1] != s[i]) {
            j = nxt[j];
        }
        ++j;
        nxt[i] = j;
    }
    for (int i = 2; i <= n; i++) {
        if (pos[dp[nxt[i]]] >= i - nxt[i]) {
            dp[i] = min(dp[i], dp[nxt[i]]);
        }
        pos[dp[i]] = i;
    }
    cout << dp[n];
    return 0;
}
// Asusetic eru quionours