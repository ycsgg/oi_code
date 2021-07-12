### CF1545D AquaMoon and Wrong Coordinate

参考了官方题解

考虑怎么能找出来被修改的位置，需要找到一些与顺序无关的性质，容易发现因为时刻是相邻的，每个相邻时刻的所有人坐标总和之差都是 $\sum v_i$

所以只要找到差不对的那一个就是错误的位置

复原这个位置需要靠更“精细”的性质，考虑记录位置的平方和 $S^2(t)$ 为 $t$ 时刻的位置的平方和，原因类似平均数和方差

推下式子能够发现：


$$
S^2(t)=\sum\limits_{i=1}^{m}(x_i+v_it)^2=\sum\limits_{i=1}^{m}x_i^2+2v_ix_it+v_i^2t^2\\
S^2(t+1)=\sum\limits_{i=1}^{m}(x_i+v_i(t+1))^2=\sum\limits_{i=1}^{m}x_i^2+2v_i(t+1)x_i+v_i^2(t+1)^2=\sum\limits_{i=1}^{m}x_i^2+2v_ix_it+2v_ix_i+v_i^2t^2+2tv_i^2t+v_i^2\\
S^2(t+2)=\sum\limits_{i=1}^{m}(x_i+v_i(t+2))^2=\sum\limits_{i=1}^{m}x_i^2+2v_i(t+2)x_i+v_i^2(t+2)^2=\sum\limits_{i=1}^{m}x_i^2+2v_ix_it+4v_ix_i+v_i^2t^2+4v_i^2t+4v_i^2
$$

$S^2(t+1)+S^2(t-1)-2S^2(t)=2\sum v_i^2$

所以只要随便找三个位置得到速度的平方和然后枚举每一位就可以找到原始值了

```cpp
#include <array>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
int n, k;
map<int, int> cnt;
int main() {
    cin >> n >> k;
    vector<vector<int>> record(k, vector<int>(n));
    vector<ll> s(k), s2(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> record[i][j];
            s[i] += record[i][j];
            s2[i] += record[i][j] * record[i][j];
        }
    }
    for (int i = 0; i < k - 1; i++) {
        cnt[s[i + 1] - s[i]]++;
    }
    int pos;
    int cpos = 1;
    for (int i = 0; i < k - 1; i++) {
        if (cnt[s[i + 1] - s[i]] == 1) {
            pos  = i + 1;
            cpos = (pos < 3 ? 4 : 1); // FIX
            break;
        }
    }
    int d  = (s[cpos] - s[cpos - 1]);
    int d2 = s2[cpos + 1] + s2[cpos - 1] - 2 * s2[cpos];
    cout << pos << " ";
    for (int i = 0; i < n; i++) {
        int now = record[pos][i];
        int res = record[pos][i] + d - (s[pos] - s[pos - 1]);
        int dif = res * res - now * now;
        if (s2[pos + 1] + s2[pos - 1] - 2 * (s2[pos] + dif) == d2) {
            cout << res;
            cout.flush();
            return 0;
        }
    }
    return 0;
}
// Asusetic eru quionours
```

