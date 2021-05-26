### CF802H Fake News (medium)

经典看数据猜复杂度

$10^6$ 出现次数和 52 个字符只能用 $\log$ 级的复杂度

~~于是使用神仙的构造方法~~

$A=c+A+c+c \ (\bmod 2 =0 )$

$A=A+c+c \ (\bmod 2 =1)$

$B=B+c$

发现完全符合

思路上大概是考虑怎么才能让一个子序列出现次数 $\times 2$ ，显然可以 $A+c+c$ $B+c$ $c$ 是个未出现过的字符

然后考虑怎么加一

在 $A$ 前面加 $B$ 是个很自然的思路，但是其实是错的

原因是前面加的 $B$ 会和后面组成新的等于 $B$ 的子序列

尝试消去这个影响就能得到啦

```cpp
#include <iostream>
#include <string>
using namespace std;
int n;
string a, b;
char c;
void solve(int x) {
    if (x == 1) {
        c = 'A';
        a.clear();
        b = c;
        return;
    }
    if (x == 2) {
        c = 'B';
        a = "B";
        b = "AB";
        return;
    }
    if (x & 1) {
        solve(x / 2);
        c++;
        a = a + c + c;
        b = b + c;
    } else {
        solve(x / 2 - 1);
        c++;
        a = c + a + c + c;
        b = b + c;
    }
}
int main() {
    cin >> n;
    solve(n);
    cout << b + a << ' ' << b;
    return 0;
}
// Asusetic eru quionours

```

