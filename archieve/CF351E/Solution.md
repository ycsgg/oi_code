### CF351E Jeff and Permutation

智商题，好妙

先取一个$\mathrm{abs}$肯定是没影响的

观察到序列中的最大值如果不取反，会对他后面的所有数字贡献一个逆序对

取反则是最前面所有数字贡献逆序对，可以考虑取$\mathrm{min}$

同理考虑第二大数字，因为第一大的已经处理完了，所以重复上述讨论即可

```cpp
#include <iostream>
using namespace std;
const int N = 2e5;
int n;
int a[N];
int ans;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = abs(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        int lans = 0, rans = 0;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i])
                lans++;
        }
        for (int j = i + 1; j <= n; j++) {
            if (a[j] < a[i])
                rans++;
        }
        ans += min(lans, rans);
    }
    cout << ans;
    return 0;
}
```

