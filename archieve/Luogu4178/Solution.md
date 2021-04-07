### P4178 Tree

淀粉质

对于不合法的方案（即不经过的当前根的方案），容斥减去

就是统计自己的，减去子树的

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 4e4 + 5;
struct Edge {
    int v;
    int w, nxt;
} edge[N * 2];
int head[N], ecnt;
void add(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, k;
int siz[N], dp[N], rt;
int cnt;
bool vis[N];
void getrt(int x, int fa) {
    siz[x] = 1;
    dp[x]  = 0;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v != fa || vis[v]) {
            continue;
        }
        siz[x] += siz[v];
        dp[x] = max(dp[x], siz[v]);
    }
    dp[x] = max(dp[x], cnt - siz[x]);
    if (dp[x] < dp[rt]) {
        rt = x;
    }
}
int ans, tot, pdis[N], dis[N];
void getdis(int x, int fa) {
    pdis[++tot] = dis[x];
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa || vis[v]) {
            continue;
        }
        dis[v] = dis[x] + edge[i].w;
        getdis(v, x);
    }
}
int calc(int x, int w) {
    tot    = 0;
    dis[x] = w;
    getdis(x, 0);
    sort(pdis + 1, pdis + 1 + tot);
    int l = 1, r = tot, ans = 0;
    while (l <= r) {
        if (pdis[l] + pdis[r] <= k) {
            ans += (r - l);
            l++;
        } else {
            r--;
        }
    }
    return ans;
}
void solve(int x) {
    vis[x] = 1;
    ans += calc(x, 0);
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (vis[v]) {
            continue;
        }
        ans -= calc(v, edge[i].w);
        cnt   = siz[v];
        dp[0] = n;
        rt    = 0;
        getrt(v, x);
        solve(rt);
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    cin >> k;
    dp[0] = cnt = n;
    getrt(1, 0);
    solve(rt);
    cout << ans << endl;
    return 0;
}
```