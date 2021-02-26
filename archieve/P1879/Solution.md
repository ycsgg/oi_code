### P1879 [USACO06NOV]Corn Fields G

https://www.luogu.com.cn/problem/P1879

基础状压

先把每一个能种的状态存下来($state[i]$数组)

然后枚举每个合法的横排相邻的状态，左移一位右移一位之后取并即可

大力转移即可

```cpp
#include <iostream>
using namespace std;
int n, m;
const int Mod = 100000000;
bool used[1 << 14];
int field[50][50];
int state[50], dp[15][1 << 14];
bool check(int x) {
    return ((x & (x << 1)) == 0) && ((x & (x >> 1)) == 0);
}
int main() {
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> field[i][j];
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            state[i] = (state[i] << 1) + field[i][j];
        }
    }
    int maxstate = (1 << n);
    for (int i = 0; i < maxstate;i++){
        used[i] = check(i);
    }
    dp[0][0] = 1;
    for (int i = 1;i<=m;i++){
        for (int j = 0; j < maxstate;j++){
            if(used[j]&&((j&state[i])==j)){
                for (int k = 0; k < maxstate;k++){
                    if((k&j)==0){
                        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % Mod;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < maxstate;i++){
        ans = (ans + dp[m][i]) % Mod;
    }
    cout << ans << endl;
}
```

