### P3069 [USACO13JAN]Cow Lineup G

转化下题意

能删$k$种牛

就是只能留$k+1$种

```cpp
#include <iostream>
#include <map>
using namespace std;
const int N = 1e5 + 7;
int n, k;
int a[N];
map<int, int> cnt;
int ans = 0;
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int l = 1, r = 0, kind = 0;
    while (r <= n) {
        ++r;
        cnt[a[r]]++;
        if (cnt[a[r]] == 1) {
            kind++;
        }
        while (kind == k + 2) {
            cnt[a[l]]--;
            if (cnt[a[l]] == 0) {
                kind--;
            }
            l++;
        }
        ans = max(ans, cnt[a[r]]);
    }
    cout << ans;
}
```

