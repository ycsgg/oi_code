### AT2689 [ARC080D] Prime Flip

~~哥德巴赫猜想之应用~~

区间反转就套路差分

所以就是每次选俩位置 $x,y$ 使得 $y-x \in \mathrm{Primes},y-x \neq 2$  取反，目标是差分数组全 $0$

分类讨论

如果 $y-x \in \mathrm{Primes}$ 需要一个操作

如果 $y-x \equiv 0 \bmod 2$ 需要两个操作，因为哥德巴赫猜想目前在很大的范围内成立(至少比数据范围大得多)

否则就是奇数，那我们随便选一个奇质数，然后就变成偶数了，三次操作

~~最大权匹配~~

权值仅有三个，贪心的让第一种最多，可以按奇偶建二分图，差为质数连边，然后跑最大匹配

然后剩余的图中尽可能匹配同奇偶的，也即第二种情况

剩下就是第三种，显然最多只能剩一个

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e7 + 10;
struct Edge {
    int v;
    int nxt;
} edge[200005];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n;
bool a[N];
vector<int> odds, evens;
int mmax;
int prime[2000006], pcnt;
bool vis[N];
void getprime() {
    for (int i = 2; i <= mmax; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > mmax) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int link[N];
bool match(int x) {
    for (int i = head[x]; i; i = edge[i].nxt) {
        if (!vis[edge[i].v]) {
            vis[edge[i].v] = 1;
            if (!link[edge[i].v] || match(link[edge[i].v])) {
                link[edge[i].v] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x] = 1;
        mmax = max(mmax, x + 1);
    }
    for (int i = mmax; i >= 1; i--) {
        a[i] ^= a[i - 1];
    }
    for (int i = 1; i <= mmax; i++) {
        if (a[i]) {
            if (i & 1) {
                odds.push_back(i);
            } else {
                evens.push_back(i);
            }
        }
    }
    vis[1] = 1;
    getprime();
    for (auto odd : odds) {
        for (auto even : evens) {
            if (!vis[abs(even - odd)]) {
                add(odd, even);
            }
        }
    }
    int ans = 0;
    for (auto odd : odds) {
        if (!link[odd]) {
            for (auto even : evens) {
                vis[even] = 0;
            }
            ans += match(odd);
        }
    }
    int p = ans;
    if ((odds.size() - p) & 1) {
        ans += (odds.size() - p) - 1;
    } else {
        ans += (odds.size() - p);
    }
    if ((evens.size() - p) & 1) {
        ans += (evens.size() - p) - 1;
    } else {
        ans += (evens.size() - p);
    }
    if ((odds.size() - p) & 1) {
        cout << ans + 3;
    } else {
        cout << ans;
    }
    return 0;
}
// Asusetic eru quionours
```