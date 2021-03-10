### P2520 [HAOI2011]向量

https://www.luogu.com.cn/problem/P2520

实际有用的操作只有$(a,b),(b,a),(a,-b),(b,-a)$所以可以列方程

$k(a,b)+q(b,a)+w(a,-b)+c(b,-a)=(x,y)$

即$(k+w)a+(q+c)b=x$与$(k-w)b+(q-c)a=y$

根据裴蜀定理可知整数解的充要条件是$gcd(a,b)|x$且$gcd(a,b)|y$

设$(k+w)=f,(k-w)=g$则$k=\dfrac{f+g}{2},w=\dfrac{f-g}{2}$

也即$2|f+g,2|f-g$

$q+c,q-c$同理

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T;
int a, b, x, y,k;
bool check(int x,int y){
    return x % k == 0 && y % k == 0;
}
signed main() {
    cin >> T;
    while (T--) {
        cin >> a >> b >> x >> y;
        k = __gcd(a, b) * 2;
        if (check(x, y) || check(x + a, y + b) || check(x + b, y + a) ||
            check(x + a + b, y + a + b)) {
            cout << "Y" << endl;
        } else {
            cout << "N" << endl;
        }
    }
}
```

