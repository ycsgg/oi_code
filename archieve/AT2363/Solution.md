
### AT2363 [AGC012C] Tautonym Puzzle

思路很巧妙的一个题

考虑如果串的右边是一个上升的序列

那左边每一个上升的排列都贡献了一个答案，并且不存在其他的好串

那么每一个放前面会+1，最后会*2

```cpp
#include <iostream>
using namespace std;
int p[202], q[202], cnt;
long long n;
void base2(long long n) {
    if (!n)
        return;
    if (~n & 1) {
        q[++q[0]] = cnt++;
        base2(n - 1);
    } else {
        p[++p[0]] = cnt++;
        base2(n >> 1);
    }
}

int main() {
    cin >> n;
    base2(n);
    printf("%d\n", cnt + 100);
    for (int i = 1; i <= q[0]; ++i)
        printf("%d ", cnt - q[i]);
    for (int i = p[0]; i; --i)
        printf("%d ", cnt - p[i]);
    for (int i = 1; i <= 100; ++i)
        printf("%d ", i);
    return 0;
}
```

