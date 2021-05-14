### AT2656 [ARC078C] Awkward Response

好耶，是交互

仔细思考一下发现可以先得把位数确定下来，字典序就可以完成

从 $1$ 开始往后加 $0$ 返回 $N$ 了说明位数超了，因为 $10000\dots$ 一直是字典序最小的，如果字典序和数字顺序不匹配说明字典序小了而数字顺序大了

位数如果确定了那么就可以二分了

考虑如果在中间值后面加个 $0$ ，那么字典序这时候就是数字顺序

而实际的 $mid\times10$ 数字顺序肯定是大于，就可以找到数字的大小关系了

坑：如果这个数字真的是 $1000\dots$ 还需要特判一下的

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
bool query(ll x) {
    cout << "? " << x << endl;
    char s[5];
    cin >> s;
    return (s[0] == 'Y');
}
void output(ll x) {
    cout << "! " << x << endl;
    exit(0);
}
int main() {
    ll x = 1;
    if (query(1000000000)) {
        x = 1e9;
        for (int i = 9; i; i--) {
            if (!query(x - 1)) {
                break;
            }
            x /= 10;
        }
        output(x);
        return 0;
    }
    while (query(x)) {
        x *= 10;
    }
    x /= 10;
    ll l = x, r = x * 10 - 1, ans;
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (query(mid * 10)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    output(ans);
}
// Asusetic eru quionours
```