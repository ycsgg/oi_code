### CF1526B I Hate 1111

考虑对于长度为偶数的 $111\dots$ 都是 $11$ 的倍数

长度为奇数的可以表示为 $111x+11$

所以仅需表示为 $11a+111b$ 即可

因为小凯的疑惑所以 $x\ge 1100$ 的都可以表示

小的暴力即可

```cpp
#include <iostream>
using namespace std;
int t;
long long x;
int main() {
    cin >> t;
    while (t--) {
        cin >> x;
        if (x >= 1100) {
            cout << "YES" << endl;
        } else {
            bool f = 0;
            for (int i = 1; i <= 10; i++) {
                if (x % 11 == 0) {
                    cout << "YES" << endl;
                    f = 1;
                    break;
                }
                x -= 111;
                if (x < 0) {
                    break;
                }
            }
            if (!f) {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
// Asusetic eru quionours
```

