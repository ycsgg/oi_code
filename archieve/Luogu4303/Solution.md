### P4303 [AHOI2006]基因匹配

考虑朴素的 $O(n^2)$ 子序列

发现 $a_i=b_j$ 其实特别少，那么只要从这几个位置转移即可

那么 $dp_{pos_{c,i}}=\max\limits_{pos_{c,i}-1}dp_i+1$

树状数组维护即可

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 20005;
int n;
namespace BIT {
int c[N * 5];
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int v) {
    while (pos <= n) {
        c[pos] = max(c[pos], v);
        pos += lowbit(pos);
    }
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res = max(res, c[pos]);
        pos -= lowbit(pos);
    }
    return res;
}
} // namespace BIT
vector<int> pos[N];
int main() {
    cin >> n;
    n *= 5;
    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        pos[c].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        for (int j = 4; ~j; j--) {
            BIT::add(pos[c][j], BIT::query(pos[c][j] - 1) + 1);
        }
    }
    cout << BIT::query(n) << endl;
    return 0;
}
// Asusetic eru quionours

```

#DP