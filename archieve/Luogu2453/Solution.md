### P2453 [SDOI2006]最短距离

https://www.luogu.com.cn/problem/P2453

大力DP

设 $dp[i][j]$为源串删除到第$i$个字符，目标串完成到$j$个字符

然后暴力转移，注意$Twiddle$的判断即可

```cpp
#include <cstring>
#include <iostream>
using namespace std;
const int INF  = 0x3f3f3f3f;
const int NINF = -0x3f3f3f3f;
typedef long long ll;
enum TYPE { VOID, Del, Rep, Copy, Ins, Twid };
int cost[8];
const int N = 205;
char a[N], b[N];
ll dp[N][N]; // dp[i][j] =>  Deleted Ori_i Completed Target_j
int main() {
    cin >> a + 1 >> b + 1;
    cin >> cost[Del] >> cost[Rep] >> cost[Copy] >> cost[Ins] >> cost[Twid];
    int lena = strlen(a + 1), lenb = strlen(b + 1);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= lena; i++) {
        dp[i][0] = i * cost[Del];
    }
    for (int i = 1; i <= lenb; i++) {
        dp[0][i] = i * cost[Ins];
    }
    for (int i = 1; i <= lena; i++) {
        for (int j = 1; j <= lenb; j++) {
            if (a[i] == b[j]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + cost[Copy]);
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + cost[Rep]);
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + cost[Del]);
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + cost[Ins]);
            if (i >= 2 && j >= 2 && a[i - 1] == b[j] && b[j - 1] == a[i]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + cost[Twid]);
            }
        }
    }
    for (int i = 1;i<lena;i++){
        dp[lena][lenb] = min(dp[lena][lenb], dp[i][lenb]+cost[Del]*(lena-i)-1);
    }
    cout<<dp[lena][lenb];
}
```





