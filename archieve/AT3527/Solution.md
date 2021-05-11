### AT3527 [ARC082D] Sandglass

很妙的分析

如果以时间做 $x$ 轴，$A$ 中沙子做 $y$ 轴，那么当初始值 $a$ 确定的时候图象是一些斜率为 $1,-1$ 的斜线和 $y=0,y=X$ 的直线拼起来的分段函数

同时当且仅当在 $t=r_i$ 处斜率才会改变，再次之前如果碰到 $X$ 或 $0$ 就会变成直线

[这里应该有图]

设初始值为 $i$  的函数是 $f_i(t)$

那么显然有 $\forall t,f_i(t) \le f_{i+1}(t)$

我们考虑对于一个询问如果它的图像 $f_{a_i}(t)$ 在某一时刻触碰到了 $f_0$ 或 $f_X$  那么它之后就和他完全一致了

如果没有触碰过，那直线必然没碰到过 $0$ 或 $X$，因为他们斜率一样，所以只有当 $f_{0/X}$ 是横线而 $f_{a_i}$ 不是的时候才会碰撞

那这一部分就是对 $f_{0/X}$ 的平移而已，直接加上平移量即可

重点就是怎么判断碰到

记录当前时刻 $t_i$ 的 $f_0(t_i)$ 和 $f_X(t_i)$ 

先假设没触碰过，算出来答案是 $ans$

若 $ans>f_{0}(t_i)$ 或者 $ans<f_{X}(t_i)$ 那么就是触碰过对应的值

否则就是没触碰过（建议配合图食用）

```cpp
#include <iostream>
using namespace std;
const int N = 1000010;
int x, n;
int r[N];
int cur, down, k = -1, up, sum;
int main() {
    cin >> x >> n;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    int m;
    cin >> m;
    up = x;
    while (m--) {
        int t, a;
        cin >> t >> a;
        while (cur < n && r[cur + 1] <= t) {
            down = min(x, max(0, down + k * (r[cur + 1] - r[cur])));
            up   = min(x, max(0, up + k * (r[cur + 1] - r[cur])));
            sum  = sum + k * (r[cur + 1] - r[cur]);
            k    = -k;
            cur++;
        }
        int downnow = min(x, max(0, down + k * (t - r[cur])));
        int upnow   = min(x, max(0, up + k * (t - r[cur])));
        int sumnow  = sum + k * (t - r[cur]);
        cout << min(upnow, max(downnow, sumnow + a)) << endl;
    }
}
// Asusetic eru quionours
```

