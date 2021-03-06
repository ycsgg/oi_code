
#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;
char s[N];
int cnt[N];
int dp[N][N];
bool check(int l, int r, int len) {
  for (int i = l; i <= r - len; i++) {
    if (s[i] != s[i + len])
      return false;
  }
  return true;
}
int main() {
  cin >> s + 1;
  int slen = strlen(s + 1);
  for (int i = 1; i <= 9; i++) {
    cnt[i] = 1;
  }
  for (int i = 10; i <= 99; i++) {
    cnt[i] = 2;
  }
  cnt[100] = 3;
  memset(dp, 0x3f, sizeof(dp));
  for (int i = 1; i <= slen; i++) {
    dp[i][i] = 1;
  }
  for (int len = 2; len <= slen; len++) {
    for (int i = 1, j = i + len - 1; j <= slen; i++, j++) {
      for (int k = i; k < j; k++) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
      }
      for (int k = i; k < j; k++) {
        int plen = k - i + 1;
        if (len % plen != 0) {
          continue;
        }
        if (check(i, j, plen)) {
          dp[i][j] = min(dp[i][j], dp[i][k] + 2 + cnt[len / plen]);
        }
      }
    }
  }
  cout << dp[1][slen];
}
