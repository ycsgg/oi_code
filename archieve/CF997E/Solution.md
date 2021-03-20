### CF997E Good Subsegments

提供一个析合树做法

我们考虑如下的排列$\{3,2,1,8,5,6,4,7,9,10\}$

它的析合树建出来长这个样子

![析合树](https://cdn.luogu.com.cn/upload/image_hosting/kvg3w9t2.png)

橙色是合点，我们认为叶子也是析点

首先我们需要统计出来每个节点的 以自己为根的子树的连续段个数，自己所在的子树的从最左端到自己的前缀和，最右端到自己的后缀和

举个例子，比如我要查询$5,10$的答案，首先把最左边的点跳上去，一直跳到不是最左边的点，即$[5,8]$，这样跳上去是包含这一段的答案的，对于右节点也一同处理

随后我们继续往上跳，如果这个点的父节点是合点，那么它能和它右边的所有节点构成连续段

即```calc(son[fa[l]].size() - ind[l])``` （```calc(x)```是```x*(x-1)/2```，```ind[x]```是这个儿子在父节点的编号） 同时需要注意，除了第一次上跳，剩下的上跳因为本节点已经被计算过了，所以需要减一(参考代码食用)

对右节点也是同样的处理，跳到同一个子树后把剩下的一段区间处理掉就好

（即代码中的```rAns[son[p][rid]] + tAns[son[p][rid]] - rAns[son[p][lid]];```）

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 4e5;
int n, m;
int a[N];
int pow2[25];
struct RMQ {
    int lg[N], mmax[N][22], mmin[N][22];
    void build() {
        pow2[0] = 1;
        for (int i = 1; i < 23; i++) {
            pow2[i] = pow2[i - 1] * 2;
        }
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i >> 1] + 1;
        }
        for (int i = 1; i <= n; i++) {
            mmax[i][0] = mmin[i][0] = a[i];
        }
        for (int i = 1; i < 21; i++) {
            for (int j = 1; j + pow2[i] - 1 <= n; j++) {
                mmin[j][i] = min(mmin[j][i - 1], mmin[j + pow2[i - 1]][i - 1]);
                mmax[j][i] = max(mmax[j][i - 1], mmax[j + pow2[i - 1]][i - 1]);
            }
        }
    }
    int query_min(int l, int r) {
        int k = lg[r - l + 1];
        return min(mmin[l][k], mmin[r - pow2[k] + 1][k]);
    }
    int query_max(int l, int r) {
        int k = lg[r - l + 1];
        return max(mmax[l][k], mmax[r - pow2[k] + 1][k]);
    }
} Table;
struct SegmentTree {
#define ls x * 2
#define rs x * 2 + 1
    int mmin[N * 4], tag[N * 4];
    void pushup(int x) {
        mmin[x] = min(mmin[ls], mmin[rs]);
    }
    void pushdown(int x) {
        if (tag[x]) {
            mmin[ls] += tag[x];
            tag[ls] += tag[x];
            mmin[rs] += tag[x];
            tag[rs] += tag[x];
            tag[x] = 0;
        }
    }
    void update(int x, int l, int r, int L, int R, int v) {
        if (l > R || r < L) {
            return;
        }
        if (l >= L && r <= R) {
            mmin[x] += v;
            tag[x] += v;
            return;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (R <= mid) {
            update(ls, l, mid, L, R, v);
        } else if (L > mid) {
            update(rs, mid + 1, r, L, R, v);
        } else {
            update(ls, l, mid, L, R, v);
            update(rs, mid + 1, r, L, R, v);
        }
        pushup(x);
    }
    int query(int x, int l, int r) {
        if (l == r) {
            return l;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (mmin[ls] == 0) {
            return query(ls, l, mid);
        } else {
            return query(rs, mid + 1, r);
        }
    }
#undef ls
#undef rs
} Tr;
int top1, top2, st1[N], st2[N];
int top, st[N];
int id[N], lp[N], rp[N], cnt;
int typ[N], M[N];
int rt;
bool check(int l, int r) {
    return (Table.query_max(l, r) - Table.query_min(l, r)) == r - l;
}
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N * 2], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
vector<int> son[N];
void build() {
    for (int i = 1; i <= n; i++) {
        while (top1 && a[i] <= a[st1[top1]]) {
            Tr.update(1, 1, n, st1[top1 - 1] + 1, st1[top1], a[st1[top1]]);
            top1--;
        }
        while (top2 && a[i] >= a[st2[top2]]) {
            Tr.update(1, 1, n, st2[top2 - 1] + 1, st2[top2], -a[st2[top2]]);
            top2--;
        }
        Tr.update(1, 1, n, st1[top1] + 1, i, -a[i]);
        st1[++top1] = i;
        Tr.update(1, 1, n, st2[top2] + 1, i, a[i]);
        st2[++top2] = i;
        id[i]       = ++cnt;
        lp[cnt] = rp[cnt] = i;
        int ls = Tr.query(1, 1, n), now = cnt;
        while (top && lp[st[top]] >= ls) {
            if (typ[st[top]] && check(M[st[top]], i)) {
                rp[st[top]] = i;
                add(st[top], now);
                son[st[top]].push_back(now);
                now = st[top];
                top--;
            } else if (check(lp[st[top]], i)) {
                typ[++cnt] = 1;
                lp[cnt]    = lp[st[top]];
                rp[cnt]    = i;
                M[cnt]     = lp[now];
                add(cnt, st[top]);
                son[cnt].push_back(st[top]);
                add(cnt, now);
                son[cnt].push_back(now);
                top--;
                now = cnt;
            } else {
                add(++cnt, now);
                son[cnt].push_back(now);
                do {
                    add(cnt, st[top]);
                    son[cnt].push_back(st[top]);
                    top--;
                } while (top && !check(lp[st[top]], i));
                lp[cnt] = lp[st[top]];
                rp[cnt] = i;
                add(cnt, st[top]);
                son[cnt].push_back(st[top]);
                top--;
                now = cnt;
            }
        }
        st[++top] = now;
        Tr.update(1, 1, n, 1, i, -1);
    }
    rt = st[1];
}
int ans[N];
int dep[N];
int fa[N][22];
void dfs(int x) {
    for (int i = 1; (1 << i) <= dep[x]; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v    = edge[i].v;
        dep[v]   = dep[x] + 1;
        fa[v][0] = x;
        dfs(v);
    }
}
int jump(int u, int d) {
    for (int i = 0; i < 21 && d; ++i)
        if (pow2[i] & d) {
            d ^= pow2[i];
            u = fa[u][i];
        }
    return u;
}
int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    x = jump(x, dep[x] - dep[y]);
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
vector<bool> isLeft, isRight;
vector<ll> tAns, rAns, lAns, ind;
void dfsAns(int x) {
    tAns[x] = 1;
    ll sum  = 0;
    for (auto k : son[x]) {
        dfsAns(k);
        rAns[k] = sum;
        sum += tAns[k];
    }
    tAns[x] += sum;
    sum = 0;
    for (int i = son[x].size() - 1; i >= 0; i--) {
        int t   = son[x][i];
        lAns[t] = sum;
        sum += tAns[t];
    }
    if (typ[x]) {
        tAns[x] += 1ll * (son[x].size() - 2) * (son[x].size() + 1) / 2;
    }
}
void solve() {
    rAns.resize(cnt + 1);
    lAns.resize(cnt + 1);
    tAns.resize(cnt + 1);
    ind    = vector<ll>(cnt + 1, -1);
    ind[0] = 0;
    isLeft = isRight = vector<bool>(cnt + 1);
    for (int x = 1; x <= cnt; x++) {
        sort(son[x].begin(), son[x].end());
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 0; j < son[i].size(); j++) {
            ind[son[i][j]] = j;
        }
        if ((son[i].size())) {
            isLeft[son[i][0]]      = 1;
            isRight[son[i].back()] = 1;
        }
    }
    dfsAns(rt);
}
ll calc(ll x) {
    return 1ll * x * (x - 1) / 2;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    Table.build();
    build();
    dfs(rt);
    solve();
    /*for (auto oop : ind) {
        cout << oop << " ";
    }*/
    // cout << endl;
    cin >> m;
    print(rt, 0);
    while (m--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << 1 << endl;
            continue;
        }
        l = id[l], r = id[r];
        int p = lca(l, r);
        while (isLeft[l] && l != p) {
            l = fa[l][0];
        }
        while (isRight[r] && r != p) {
            r = fa[r][0];
        }
        if (l == p && r == p) {
            cout << tAns[p] << endl;
            continue;
        }
        if (l == p) {
            l = son[l][0];
        }
        if (r == p) {
            r = son[r].back();
        }
        ll ans  = 0;
        int lid = 0, rid = 0;
        if (fa[l][0] == p) {
            lid = ind[l];
        } else {
            ans += 1ll * tAns[l];
            bool fst = 1;
            while (fa[l][0] != p) {
                if (typ[fa[l][0]]) {
                    if (fst) {
                        ans += 1ll * calc(son[fa[l][0]].size() - ind[l]);
                    } else {
                        ans += 1ll * calc(son[fa[l][0]].size() - ind[l] - 1);
                    }
                }
                fst = 0;
                ans += 1ll * lAns[l];
                l = fa[l][0];
            }
            lid = ind[l] + 1;
        }
        if (fa[r][0] == p) {
            rid = ind[r];
        } else {
            ans += 1ll * tAns[r];
            bool fst = 1;
            while (fa[r][0] != p) {
                if (typ[fa[r][0]]) {
                    if (fst) {
                        ans += 1ll * calc(ind[r] + 1);
                    } else {
                        ans += 1ll * calc(ind[r]);
                    }
                }
                fst = 0;
                ans += 1ll * rAns[r];
                r = fa[r][0];
            }
            rid = ind[r] - 1;
        }
        int num = rid - lid + 1;
        if (num) {
            ans +=
                1ll * rAns[son[p][rid]] + tAns[son[p][rid]] - rAns[son[p][lid]];
        }
        if (typ[p]) {
            ans += 1ll * (num) * (num - 1) / 2;
        }
        cout << ans << endl;
    }
}
```