### P4384 [八省联考2018]制胡窜

~~除了代码有点难调还是挺妙的~~

题意：将一个字符串$S$分为三段$[1,i],[i+1,j-1],[j,n]$ 至少有一段包含了子串$S_{l,r}$的方案数

至少有一段不太好统计，考虑总共的方案数是$\binom{n-1}{2}$，如果能减去三段全不包含的就能得到答案

至少我们得知道$S_{l,r}$的所有位置，那假设我们就知道了（？）所有形如$[l_i,r_i]$的区间是$S_{l,r}$的位置，为了方便设有$m$个区间且按$l$从小到大排序

首先可以发现如果有三个子串不重叠必然为$0$

否则分类讨论

#### Case 1:

如果最左的子串和最右的子串重叠，即$r_1>l_{m}$

那么我们对$i$的选取讨论一下首先肯定是在$[1,r_1)$

如果$i\in[1,l_1)$那么$j$只能选$(l_m,r_1]$，贡献为$(l_1-1)(r_1-l_m)$

如果$i\in[l_i,l_{i+1})$，此时$j$的限制是$(l_m,r_{i+1}]$，贡献为$\sum(l_{i+1}-l_i)(r_{i+1}-l_m)$

如果$i\in[l_{i+1},r_1)$ 仅需保证$i+1<j$，贡献为$\binom{r1-l_m}{2}+(r_1-l_m)(n-r_1)$

#### Case 2:

如果最左的子串和最右的子串不交，即$r_1<l_m$

首先如果$i \in [1,l_1)$是没法选的

当$i\in[l_i,l_{i+1}]$略麻烦，实际上也能写出这个式子$\sum(r_{i+1}-r_i)(r_{i+1}-l_m)$ 要求是$l_m<r_{i+1}$ 且$l_{i+1}<r_1$

但实际上会漏掉一些答案，还需要找到$r_1+len-1$在$endpos$中的前驱和后继$p_1,p_2$（建议画图理解）贡献为$(r_1-l_{p1})(r_{p2}-l_m)$

所以最终我们要维护区间最大最小，和$(r_{i+1}-r_i)r_{i+1}$与$(r_{i+1}-r_i)$（Case1中求和也可以改成这样）

对于询问先判断是否有三个相交的区间，然后讨论

前后缀可以利用最大最小来查询

至于$endpos$集合（也就是$[l_i,r_i]$），虽然在SAM定义里有这个东西，但实际上建出来的SAM是没有的

但是可以考虑每一个状态的$endpos$是他的$link$的所有点的$endpos$并集，这个东西可以跑线段树合并

具体来说是对于每一个前缀$i$插入到权值线段树里，然后$dfs$搞出来所有的$endpos$ 

找$S_{l,r}$在SAM上的位置可以倍增

```cpp
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 2e5 + 6;
char s[N];
int n, q;
struct Edge {
    int v;
    int nxt;
} edge[N * 4];
int head[N * 2], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
namespace SegmentTree {
const int maxn = 2e5 + 6;
struct Node {
    int mmin, mmax;
    long long s1, s2;
    int ls, rs;
} tr[maxn * 40];
int tot;
Node merge(const Node &a, const Node &b) {
    Node c;
    c.mmin = min(a.mmin, b.mmin);
    c.mmax = max(a.mmax, b.mmax);
    c.s1   = a.s1 + b.s1 + b.mmin * 1LL * (b.mmin - a.mmax);
    c.s2   = a.s2 + b.s2 + b.mmin - a.mmax;
    return c;
}
void pushup(int x) {
    if (tr[x].ls && tr[x].rs) {
        tr[x].mmin = min(tr[tr[x].ls].mmin, tr[tr[x].rs].mmin);
        tr[x].mmax = max(tr[tr[x].ls].mmax, tr[tr[x].rs].mmax);
        tr[x].s1 =
            tr[tr[x].ls].s1 + tr[tr[x].rs].s1 +
            tr[tr[x].rs].mmin * 1LL * (tr[tr[x].rs].mmin - tr[tr[x].ls].mmax);
        tr[x].s2 = tr[tr[x].ls].s2 + tr[tr[x].rs].s2 + tr[tr[x].rs].mmin -
                   tr[tr[x].ls].mmax;
    } else if (tr[x].ls) {
        int t_ls = tr[x].ls;
        int t_rs = tr[x].rs;
        tr[x]    = tr[tr[x].ls];
        tr[x].ls = t_ls;
        tr[x].rs = t_rs;
    } else {
        int t_ls = tr[x].ls;
        int t_rs = tr[x].rs;
        tr[x]    = tr[tr[x].rs];
        tr[x].ls = t_ls;
        tr[x].rs = t_rs;
    }
}
int querymax(int rt, int l, int r, int L, int R) {
    if (!rt)
        return 0;
    if (L <= l && r <= R)
        return tr[rt].mmax;
    int mid = l + r >> 1, ans = 0;
    if (L <= mid)
        ans = querymax(tr[rt].ls, l, mid, L, R);
    if (R > mid)
        ans = max(ans, querymax(tr[rt].rs, mid + 1, r, L, R));
    return ans;
}
int querymin(int rt, int l, int r, int L, int R) {
    if (!rt)
        return 0x3f3f3f3f;
    if (L <= l && r <= R)
        return tr[rt].mmin;
    int mid = l + r >> 1, ans = 0x3f3f3f3f;
    if (L <= mid)
        ans = querymin(tr[rt].ls, l, mid, L, R);
    if (R > mid)
        ans = min(ans, querymin(tr[rt].rs, mid + 1, r, L, R));
    return ans;
}
Node c_res;
void cquery(int rt, int l, int r, int L, int R) {
    if (!rt)
        return;
    if (L <= l && r <= R) {
        if (c_res.mmin == 0)
            c_res = tr[rt];
        else
            c_res = merge(c_res, tr[rt]);
        return;
    }
    int mid = l + r >> 1;
    if (L <= mid)
        cquery(tr[rt].ls, l, mid, L, R);
    if (R > mid)
        cquery(tr[rt].rs, mid + 1, r, L, R);
}
void update(int &rt, int l, int r, int p) {
    if (!rt)
        rt = ++tot;
    if (l == r) {
        tr[rt].mmin = tr[rt].mmax = p;
        tr[rt].s1 = tr[rt].s2 = 0;
        tr[rt].ls = tr[rt].rs = 0;
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid)
        update(tr[rt].ls, l, mid, p);
    else
        update(tr[rt].rs, mid + 1, r, p);
    pushup(rt);
}
int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    int rt    = ++tot;
    tr[rt].ls = merge(tr[x].ls, tr[y].ls);
    tr[rt].rs = merge(tr[x].rs, tr[y].rs);
    pushup(rt);
    return rt;
}
} // namespace SegmentTree

int rt[N], dep[N], fa[N * 2][19];
int pos[N];
namespace SAM {
int nxt[N * 2][10], link[N * 2], len[N * 2];
int cnt, last;
void insert(int c, int id) {
    int cur = ++cnt;
    int p   = last;
    last    = cur;
    pos[id] = cur;
    while (p && !nxt[p][c]) {
        nxt[p][c] = cur;
        p         = link[p];
    }
    if (!p) {
        link[cur] = 1;
    } else {
        int q = nxt[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
        } else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[q], sizeof(nxt[q]));
            link[cq] = link[q];
            link[q] = link[cur] = cq;
            while (p && nxt[p][c] == q) {
                nxt[p][c] = cq;
                p         = link[p];
            }
        }
    }
}
void dfs(int x);
void build() {
    for (int i = 1; i <= cnt; i++) {
        if (link[i]) {
            add(link[i], i);
        }
    }
    for (int i = 1; i <= n; i++) {
        SegmentTree::update(rt[pos[i]], 1, n, i);
    }
    dfs(1);
}
void dfs(int x) {
    fa[x][0] = link[x];
    for (int i = 1; i <= 18; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v  = edge[i].v;
        dep[v] = dep[x] + 1;
        dfs(v);
        if (x != 1) {
            rt[x] = SegmentTree::merge(rt[x], rt[v]);
        }
    }
}
} // namespace SAM
ll C2(int n) {
    if (n < 2) {
        return 0;
    }
    return 1ll * n * (n - 1) / 2;
}
long long querym(int l, int r) {
    using SAM::len;
    using namespace SegmentTree;
    int plen = r - l + 1, x = pos[r];
    for (int i = 18; i >= 0; i--) {
        if (len[fa[x][i]] >= plen) {
            x = fa[x][i];
        }
    }
    int L = tr[rt[x]].mmin, R = tr[rt[x]].mmax;
    if (L < R - plen * 2 + 1 &&
        querymax(rt[x], 1, n, L, R - plen) - plen + 1 > L)
        return C2(n - 1);
    if (R - plen + 1 <= L) {
        Node now = tr[rt[x]];
        int lm   = R - plen + 1;
        long long ans =
            now.s1 - now.s2 * lm + C2(L - lm) + (L - lm) * 1LL * (n - plen);
        return C2(n - 1) - ans;
    } else {
        c_res  = (Node){0, 0, 0, 0, 0, 0};
        int lm = R - plen + 1, poslm = querymax(rt[x], 1, n, 1, lm);
        cquery(rt[x], 1, n, poslm, L + plen - 1);
        Node now      = c_res;
        int p1        = querymax(rt[x], 1, n, 1, L + plen - 1);
        int p2        = querymin(rt[x], 1, n, L + plen, n);
        long long ans = now.s1 - now.s2 * lm +
                        (p2 > lm ? (L - (p1 - plen + 1)) * 1LL * (p2 - lm) : 0);
        return C2(n - 1) - ans;
    }
}
int main() {
    cin >> n >> q;
    cin >> s + 1;
    SAM::last = SAM::cnt = 1;
    for (int i = 1; i <= n; i++) {
        SAM::insert(s[i] - '0', i);
    }
    SAM::build();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << querym(l, r) << endl;
    }
    return 0;
}
```