### P5794 [THUSC2015]解密运算

先考虑 $O(n^2)$ 的暴力

对于 

```
5 3 
3 0 2 1 1 2
```
这个数据

```
0????3
1????0
1????2
2????1
2????1
3????2
```

因为第一列和最后一列确定，加密排序之后的矩阵大概长这个样子

因为原字符串当作环处理，所以可以确定一些关系 

上面的可以确定 ``` x -> y``` 代表 ```x ``` 后面可能是 ```y```

```
3 -> 0
0 -> 1
2 -> 1
2 -> 3
1 -> 2
```

然后因为是字典序排序，可以推出来第二列

```
01???3
12???0
12???2
21???1
23???1
30???2
```

然后大力递推就能得到整个矩阵

```
012123
121230
123012
212301
230121
301212
```

考虑优化这个过程

发现暴力递推的时候，每一个串一定是同一个串的可能关系推出来的

比如第四行全是由第三行给出的可能的顺序推出来的，这样如果我们知道他是从那个串递推就可以 $O(n)$ 解决了

画个图感性理解一下就是按照权值排序跳 $id$ 就是原串的递推过程

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, m;
struct Data {
    int val, rk;
} a[N];
int main() {
    cin >> n >> m;
    n++;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].rk = i;
    }
    sort(a + 1, a + 1 + n, [&](const Data &A, const Data &B) -> bool {
        if (A.val == B.val) {
            return A.rk < B.rk;
        }
        return A.val < B.val;
    });
    int now = a[1].rk;
    for (int i = 1; i < n; i++) {
        cout << a[now].val << " ";
        now = a[now].rk;
    }
    return 0;
}
//Asusetic eru quionours
```



