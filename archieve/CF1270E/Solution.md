### CF1270E Divide Points

比较妙的题

#### Solution

奇偶分类

把点按照奇偶性分类为
$$
(2k_1,2k_2),(2k_1,2k_1+1),(2k_1+1,2k_2),(2k_1+1,2k_2+2)
$$
能够发现同奇偶放入一组，那么一组内距离平方为偶数，不同组之间为奇数

如果某一组没点

那就平移

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1005;
int n;
int x[N], y[N];
vector<int> ans;
int main() {
    cin >> n;
    int a, b;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        if (i == 1) {
            a = x[i];
            b = y[i];
        }
        x[i] -= a;
        y[i] -= b;
    }
    while ("qwq") {
        int flag = 0;
        for (int i = 1; i <= n; i++) {
            if ((x[i] & 1) || (y[i] & 1)) {
                flag = 1;
                break;
            }
        }
        if(flag)
            break;
        for (int i = 1; i <= n; i++) {
            x[i] /= 2;
            y[i] /= 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (x[i] % 2 == 0 && y[i] % 2 == 0) {
            ans.push_back(i);
        }
    }
    bool flag = 0;
    for (int i = 1; i <= n; i++) {
        if ((x[i] & 1) != (y[i] & 1)) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        for (int i = 1; i <= n; i++) {
            if ((x[i] & 1) && (y[i] & 1)) {
                ans.push_back(i);
            }
        }
    }
    cout << ans.size() << endl;
    for(auto k:ans){
        cout << k << endl;
    }
}
```

