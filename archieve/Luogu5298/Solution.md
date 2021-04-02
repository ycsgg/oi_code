### P5298 [PKUWC2018]Minimax

先考虑非常暴力的$dp$：

设$dp_{x,j}$为点$x$取值为$j$的概率，因为权值各不相同，那我们先钦定是左儿子取到的$j$

那么$dp_{x,j}=dp_{ls,j}\times(p_x\sum\limits_{k<j}dp_{rs,k}+(1-p_x)\sum\limits_{k>j}dp_{rs,k})$

但是发现一个个转移这个东西是比较亏的，很多东西没必要一次次统计

维护这个式子需要知道大于或小于某个权值所有数的和，也就是前后缀和，容易想到用线段树来维护

向上转移的过程就是两颗线段树合并的过程

一方无节点直接乘上后面的一坨系数就行，如果都有就需要递归下去合并左右儿子然后更新自己

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int N  = 3e5 + 5;
const ll mod = 998244353;
const ll inv = 796898467;
int n;
int son[N][2], fa[N], val[N];
int w[N], cnt;
int rt[N];
int p[N];
int id[N];
namespace SegmentTree {
struct Node {
    int val, tag;
    int ls, rs;
} tr[N << 5];
int tot;
int mul(int a, int b) {
    return 1ll * a * b % mod;
}
void push(int x) {
    if (tr[x].tag != 1) {
        tr[tr[x].ls].val = mul(tr[tr[x].ls].val, tr[x].tag);
        tr[tr[x].ls].tag = mul(tr[tr[x].ls].tag, tr[x].tag);
        tr[tr[x].rs].val = mul(tr[tr[x].rs].val, tr[x].tag);
        tr[tr[x].rs].tag = mul(tr[tr[x].rs].tag, tr[x].tag);
        tr[x].tag        = 1;
    }
}
void pushup(int x) {
    tr[x].val = 1ll * (tr[tr[x].ls].val + tr[tr[x].rs].val) % mod;
}
void insert(int &rt, int l, int r, int pos) {
    if (!rt) {
        rt         = ++tot;
        tr[rt].tag = 1;
    }
    if (l == r) {
        tr[rt].val = 1;
        return;
    }
    push(rt);
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(tr[rt].ls, l, mid, pos);
    } else {
        insert(tr[rt].rs, mid + 1, r, pos);
    }
    pushup(rt);
}
int merge(int x, int y, int tagx, int tagy, int v) {
    if (!x && !y) {
        return 0;
    }
    if (!x) {
        tr[y].val = mul(tr[y].val, tagy);
        tr[y].tag = mul(tr[y].tag, tagy);
        return y;
    }
    if (!y) {
        tr[x].val = mul(tr[x].val, tagx);
        tr[x].tag = mul(tr[x].tag, tagx);
        return x;
    }
    push(x);
    push(y);

    int slx = tr[tr[x].ls].val, srx = tr[tr[x].rs].val;
    int sly = tr[tr[y].ls].val, sry = tr[tr[y].rs].val;
    tr[x].ls = merge(tr[x].ls, tr[y].ls,
                     (tagx + 1ll * (1 - v + mod) % mod * sry) % mod,
                     (tagy + 1ll * (1 - v + mod) % mod * srx) % mod, v);
    tr[x].rs = merge(tr[x].rs, tr[y].rs, (tagx + 1ll * v * sly) % mod,
                     (tagy + 1ll * v * slx) % mod, v);
    pushup(x);
    return x;
}
void solve(int x, int l, int r) {
    if (l == r) {
        p[l] = tr[x].val;
        return;
    }
    push(x);
    int mid = (l + r) / 2;
    if (tr[x].ls) {
        solve(tr[x].ls, l, mid);
    }
    if (tr[x].rs) {
        solve(tr[x].rs, mid + 1, r);
    }
}
} // namespace SegmentTree
void pre(int x) {
    if (son[x][1]) {
        pre(son[x][0]);
        pre(son[x][1]);
        rt[x] = SegmentTree::merge(rt[son[x][0]], rt[son[x][1]], 0, 0, val[x]);
    } else if (son[x][0]) {
        pre(son[x][0]);
        rt[x] = rt[son[x][0]];
    } else {
        SegmentTree::insert(rt[x], 1, cnt, id[x]);
    }
}
ll ans = 0;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> fa[i];
        if (!son[fa[i]][0]) {
            son[fa[i]][0] = i;
        } else {
            son[fa[i]][1] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i <= n; i++) {
        if (son[i][0]) {
            val[i] = (1ll * val[i] * inv) % mod;
        } else {
            w[++cnt] = val[i];
        }
    }
    sort(w + 1, w + 1 + cnt);
    for (int i = 1; i <= n; ++i) {
        if (!son[i][0]) {
            id[i] = lower_bound(w + 1, w + cnt + 1, val[i]) - w;
        }
    }
    pre(1);
    SegmentTree::solve(rt[1], 1, cnt);
    for (int i = 1; i <= cnt; i++) {
        ans = (ans + 1ll * i * p[i] % mod * p[i] % mod * w[i] % mod) % mod;
    }
    cout << ans << endl;
}
```

