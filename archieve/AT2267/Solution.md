### AT2267 [AGC008E] Next or Nextnext

因为我是从图论题单发现的所以就按图论思考了

先按套路 $i \rightarrow p_i$ 连边，会构成若干个环

[Case 0]

发现没啥能用的性质

然后 $a_i$ 的个很好的东西，因为 $p_i$ 要么是 $a_i$ 要么下一个是 $a_i$ 图上表示就类似

[Case 1]

如果每个 $p_i=a_i$ 都成立，那就是原图了

同样的每个 $p_{p_i}=a_i$ 都成立就是

[Case 1]

这里需要讨论一下，环长位偶数的话像上图会把原图拆成两个大小为一半的环

如果是奇数则

[Case 3.1]

拉平看一下

[Case 3.2]

可以发现这个结构和原图是一样的

最后如果既有 $p_i=a_i$ $p_{p_i}=a_i$ 就是

[Case 4.1]

拉直

[Case 4.2]

是一个内向基环树

现在我们拿到了变换完的 $i \rightarrow a_i$ 的图，求原图的方案数

环和基环树没啥关系也不能相互作用

所以分别处理

环的部分考虑dp

 $dp_{s,k}$ 表示大小为 $s$ 的环考虑到第 $k$ 个，如果 $s$ 是奇数那么可以有一个和原图同构的图和原图，即 $dp_{s,k-1}+dp_{s,k-1}$

同时也可以向上合并成大环，最后乘起来

基环树的部分

基环树上的链肯定是得压到环里的，对着图手玩一会就能发现

这个链长度为 $l_1$ ，到下一个链长度为 $l_2$

如果 $l_2 < l_1$ 必然塞不下

如果 $l_1=l_2$ 刚刚好一种方案

否则的话第一个点隔一个点链和直接连有两种方案

```cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
const int N  = 1e5 + 5;
const ll mod = 1e9 + 7;
int n;
int a[N], in[N], st[N], top;
bool inst[N], vis[N], cyc[N];
int len[N];
void dfs(int x) {
    if (vis[x]) {
        if (inst[x]) {
            for (int i = top; i >= 1; i--) {
                cyc[st[i]] = 1;
                if (st[i] == x) {
                    return;
                }
            }
        }
        return;
    }
    vis[x] = inst[x] = 1;
    st[++top]        = x;
    dfs(a[x]);
    inst[x] = 0;
}
int cnt[N];
ll ans = 1;
void pre(int x) {
    int tot = 0, fr = 0, ed = 0, frid;
    while (cyc[x]) {
        ++tot;
        cyc[x] = 0;
        if (len[x]) {
            if (!fr) {
                fr   = tot;
                ed   = tot;
                frid = x;
            } else {
                int pm = (len[x] < tot - ed) + (len[x] <= tot - ed);
                ans    = 1ll * ans * pm % mod;
                ed     = tot;
            }
        }
        x = a[x];
    }
    if (!fr) {
        ++cnt[tot];
    } else {
        int kl = (len[frid] < tot - ed + fr) + (len[frid] <= tot - ed + fr);
        ans    = 1ll * ans * kl % mod;
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ++in[a[i]];
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i);
        if (!in[i]) {
            q.push(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if ((cyc[i] && in[i] > 2) || (!cyc[i] && in[i] > 1)) {
            cout << 0;
            exit(0);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        len[a[x]] = len[x] + 1;
        if (!cyc[a[x]]) {
            q.push(a[x]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cyc[i]) {
            pre(i);
        }
    }
    static ll num[N];
    for (int i = 1; i <= n; i++) {
        if (cnt[i]) {
            num[0] = 1;
            for (int j = 1; j <= cnt[i]; j++) {
                if (i > 1 && i % 2 != 0) {
                    num[j] = (num[j - 1] + num[j - 1]) % mod;
                } else {
                    num[j] = num[j - 1];
                }
                if (j > 1) {
                    num[j] =
                        (1ll * num[j] + 1ll * num[j - 2] * 1ll * (j - 1ll) %
                                            mod * 1ll * i % mod) %
                        mod;
                }
            }
            ans = 1ll * ans * num[cnt[i]] % mod;
        }
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours
```

