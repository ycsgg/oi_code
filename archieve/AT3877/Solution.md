### AT3877 [ARC089C] GraphXY

构造大失败

直接说正解

考虑 $S,T$  路径里有 $i$ 个 $x$ ，$j$ 个 $y$ 其余边最小值为 $f_{i,j}$ 

则 $d_{x,y}\ge ix+jy+f_{i,j} \Rightarrow d_{x,y}=\min (ix+jy+f_{i,j})j$

移项得到 $f_{i,j}\le d_{x,y}-ix-jy \Rightarrow f_{i,j}=\max(d_{x,y}-ix-y)$

构造从 $S$ 开始的一条链全是 $x$ ，到 $T$ 的链全是 $y$ 

然后在第 $i$ 个 $x$ 与 $j$ 个 $y$ 间连边，暴力求出 $f_{i,j}$

最后检查一遍如果不符合就是无解

```cpp
#include <iostream>
using namespace std;
int A, B;
int d[11][11];
int f[101][101];
int main() {
    cin >> A >> B;
    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= B; j++) {
            cin >> d[i][j];
        }
    }
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            for (int x = 1; x <= A; x++) {
                for (int y = 1; y <= B; y++) {
                    f[i][j] = max(f[i][j], d[x][y] - i * x - j * y);
                }
            }
        }
    }
    for (int x = 1; x <= A; x++) {
        for (int y = 1; y <= B; y++) {
            int now = 0x7f7f7f7f;
            for (int i = 0; i <= 100; i++) {
                for (int j = 0; j <= 100; j++) {
                    now = min(now, f[i][j] + i * x + j * y);
                }
            }
            if (now != d[x][y]) {
                cout << "Impossible";
                return 0;
            }
        }
    }
    cout << "Possible" << endl;
    cout << "202 10401" << endl;
    for (int i = 1; i <= 100;i++){
        cout << i << " " << i + 1 << " X" << endl;
    }
    for (int i = 102; i <= 201;i++){
        cout << i << " " << i + 1 << " Y" << endl;
    }
    for (int i = 0; i <= 100;i++){
        for (int j = 0; j <= 100;j++){
            cout << i + 1 << " " << 202 - j << " " << f[i][j] << endl;
        }
    }
    cout << "1 202";
    return 0;
}
// Asusetic eru quionours
```

