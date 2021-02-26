### CF550D 【Regular Bridge】

首先是$k$是偶数的时候一定会有一个欧拉回路，所以显然不成立

当$k$是奇数的时候可以如下构造

先把桥拆掉，剩下的两个连通块可以是完全对称的连通块

每一个联通块里有一个度数为$k-1$的点用来连桥

为了达到这个目的，新建$k-1$个点用来连这个点，记作$V_1$

这新建的$k-1$个点现在各需要$k-1$条连边，再新建$k-1$个点，记作$V_2$

让$V_1$中每个点都向$V_2$中每个点连边，此时$V_2$中每个点还需要$1$条连边，因为$k-1$是偶数，所以每两个点连边即可

![当k=5的时候的一个连通块](https://cdn.luogu.com.cn/upload/image_hosting/0fcbwfja.png)
当$k=5$的时候一个连通块

```cpp
#include <iostream>
using namespace std;
int k;
struct RevEdge {
    int u, v;
    RevEdge(int a, int b) {
        u = a;
        v = b;
    }
};
int n, m;
ostream &operator<<(ostream &os, const RevEdge e) {
    os << e.u << " " << e.v << endl;
    os << e.u + n / 2 << " " << e.v + n / 2;
    return os;
}
int main() {
    cin >> k;
    if (!(k & 1)) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    n = 4 * k - 2;
    m = n * k / 2;
    cout << n << " " << m << endl;
    cout << 1 << " " << n / 2 + 1 << endl;
    for (int i = 2; i <= k; i++) {
        cout << RevEdge(1, i) << endl;
    }
    for (int i = 2; i <= k; i++) {
        for (int j = k + 1; j <= 2 * k - 1; j++) {
            cout << RevEdge(i, j)<<endl;
        }
    }
    for (int j = k + 1; j <= 2 * k - 1;j+=2){
        cout << RevEdge(j, j + 1) << endl;
    }
    return 0;
}
```