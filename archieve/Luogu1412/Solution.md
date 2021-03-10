### P1412 经营与开发

反着dp，反正每一个乘法都是给后面乘个系数

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, w;
double k, c, ans;
int typ[N], val[N];
int main() {
    cin >> n >> k >> c >> w;
    k = 1.0 - 0.01 * k;
    c = 1.0 + 0.01 * c;
    for (int i = 1; i <= n; i++) {
        cin >> typ[i] >> val[i];
    }
    for (int i = n; i >= 1; i--) {
        if (typ[i] == 1) {
            ans = max(ans, ans * k + val[i]);
        } else {
            ans = max(ans, ans * c - val[i]);
        }
    }
    printf("%.2lf", 1.0 * ans * w);
    return 0;
}
```