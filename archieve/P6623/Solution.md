### P6623 [省选联考 2020 A 卷] 树

套路考虑贡献

如果向上增加一级祖先，考虑二进制位的变化，会发现随着$+1$的变化，二进制上会是$2^k$个零与$2^k$个一（$k$是位数）的序列

手玩一下发现，对一个节点它的$k$位二进制位，就是把$[m2^{k+1}+c,m2^{k+1}+2^k+c]$的祖先全异或上$2^k$

差分的话就是在$2m2^k+c,(2m+1)2^k+c$上异或，因为差分的区间太多了，观察性质，发现这个差分的点$\bmod 2^k$相等，所以记$c_{k,i}$表示当前深度$\bmod 2^k=i$的点，这样就能$O(1)$修改

查询就是处理这个点前和处理后的异或，显然（大概

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int p = 21;
const int N = 1 << 21;
struct Edge {
    int v;
    int nxt;
} edge[N];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
unsigned long long ans = 0;
ll a[N];
ll c[p][N];
ll dfs(int x, int dep) {
    ll res = a[x];
    for (int i = 0; i < p; i++) {
        c[i][(dep + a[x]) & ((1ll << i) - 1)] ^= (1ll << i);
    }
    for (int i = 0; i < p; i++) {
        res ^= c[i][dep & ((1ll << i) - 1)];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        res ^= dfs(v, dep + 1);
    }
    for (int i = 0; i < p; i++) {
        res ^= c[i][dep & ((1ll << i) - 1)];
    }
    ans += res;
    return res;
}
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        add(x, i);
    }
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}
```