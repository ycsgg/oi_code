### CF575B Bribes

松鼠的新家类似，但是是有向的

两个方向互不不干扰，所以可以两个差分分别记录一个点到根节点方向，和根节点到某个点的

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N   = 1e5 + 5;
const ll mod = 1e9 + 7;
struct Edge {
    int v, u;
    int direct, nxt;
} edge[N * 2];
int head[N], ecnt;
int diffA[N], diffB[N];
void add(int u, int v, int w) {
    edge[++ecnt].v    = v;
    edge[ecnt].u      = u;
    edge[ecnt].direct = w;
    edge[ecnt].nxt    = head[u];
    head[u]           = ecnt;
}
int n, k;
void pushdown(int x, int f) {
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == f)
            continue;
        pushdown(v, x);
        diffA[x] += diffA[v];
        diffB[x] += diffB[v];
    }
}
long long qpow(int a, int b) {
    long long res = 1, base = a % mod;
    while (b) {
        if (b & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        b /= 2;
    }
    return res;
}
int siz[N], fa[N], dep[N], son[N];
void dfs1(int x, int f) {
    siz[x] = 1;
    fa[x]  = f;
    dep[x] = dep[f] + 1;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == f)
            continue;
        dfs1(v, x);
        siz[x] += siz[v];
        if (siz[v] > siz[son[x]]) {
            son[x] = v;
        }
    }
}
int top[N];
void dfs2(int x, int topf) {
    top[x] = topf;
    if (!son[x])
        return;
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa[x] || v == son[x]) {
            continue;
        }
        dfs2(v, v);
    }
}
int getlca(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) {
            swap(a, b);
        }
        a = fa[top[a]];
    }
    return dep[a] < dep[b] ? a : b;
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, x;
        scanf("%d%d%d", &u, &v, &x);
        if (x == 1) {
            add(u, v, 1);
            add(v, u, 0);   
        } else {
            add(u, v, 0);
            add(v, u, 0);
        }
    }
    dfs1(1, 0);
    dfs2(1, 1);
    cin >> k;
    int now = 1;
    for (int i = 1; i <= k; i++) {
        int v;
        scanf("%d", &v);
        int lca = getlca(now, v);
        diffA[now]++;
        diffA[lca]--;
        diffB[v]++;
        diffB[lca]--;
        now = v;
    }
    pushdown(1, 0);
    long long ans = 0;
    for (int i = 1; i <= ecnt; i++) {
        if (edge[i].direct) {
            if (dep[edge[i].u] > dep[edge[i].v]) {
                ans = ((ans + qpow(2, diffB[edge[i].u]) % mod) + mod - 1) % mod;
            } else {
                ans = ((ans + qpow(2, diffA[edge[i].v]) % mod) + mod - 1) % mod;
            }
        }
    }
    cout << ans << endl;
}
```

