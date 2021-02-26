### CF1041E Tree Reconstruction

好想难证

$b\ne n$必然无解

先考虑如果是一条链的话那么$a$排完序相当于前缀max

这个好搞

如果链搞不出来那么树也搞不出来

证明的话可以想一下

链构造不出来的情况只能是对于某个数字它的前缀max比他自己还多

这种情况下如果我们能找到一个合法的树

把$n$提出来当根，那么另一个最大值$k$的子树有超过$k$条边，根据抽屉原理必然有大于$k$的

证毕

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1005;
int n;
int a[N], e[N];
bool vis[N];
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int b;
        cin >> a[i] >> b;
        if (b != n) {
            cout << "NO" << endl;
            return 0;
        }
    }
    sort(a + 1, a + n);
    for (int i = 1; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            e[i]      = a[i];
            vis[a[i]] = 1;
        } else {
            bool f = 0;
            for (int j = 1; j <= a[i]; j++) {
                if (!vis[j]) {
                    e[i]   = j;
                    vis[j] = 1;
                    f      = 1;
                    break;
                }
            }
            if (!f) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl;
    e[n] = n;
    for (int i = 1; i < n; i++) {
        cout << e[i] << " " << e[i + 1] << endl;
    }
}
```

