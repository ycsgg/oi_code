### P4926 [1007]倍杀测量者

二分+差分约束

虽然可以用乘积最长路做，但是其实还能取个对数变成加法

还是常用套路

```cpp
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, s, t;
const int N      = 1005;
const double eps = 1e-8;
struct Data {
    int opt, a, b, k;
} q[N];
int p[N];
struct Edge {
    int v;
    int nxt;
    int tag;
    double w;
} edge[N * 3];
int head[N], ecnt;
void add(int u, int v, double w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
queue<int> qaq;
int cnt[N];
bool vis[N];
double dis[N];
bool check(double T) {
    memset(head, 0, sizeof(head));
    ecnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        dis[i] = 2e18 + 7;
    }
    while (!qaq.empty()) {
        qaq.pop();
    }
    for (int i = 1; i <= n; i++) {
        if (p[i]) {
            add(i, 0, -log((double)p[i]));
            add(0, i, log((double)p[i]));
        }
    }
    for (int i = 1; i <= s; i++) {
        int a = q[i].a, b = q[i].b, opt = q[i].opt, k = q[i].k;
        if (p[a] && p[b] &&
            ((opt == 1 && p[a] < p[b] * (k - T)) ||
             (opt == 2 && p[a] * (k + T) < p[b]))) {
            return 1;
        }
        if (opt == 1) {
            add(a, b, -log((double)(k - T)));
        } else {
            add(a, b, log((double)(k + T)));
        }
    }
    qaq.push(0);
    vis[0] = 1;
    cnt[0] = 1;
    while (!qaq.empty()) {
        int x = qaq.front();
        qaq.pop();
        vis[x] = 0;
        for (int i = head[x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dis[v] > dis[x] + edge[i].w) {
                dis[v] = dis[x] + edge[i].w;
                cnt[v] = cnt[x] + 1;
                if (cnt[v] == n + 2) {
                    return 1;
                }
                if (!vis[v]) {
                    qaq.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return false;
}
double l = 0, r = 1e18, ans = -1;
int main() {
    cin >> n >> s >> t;
    for (int i = 1; i <= s; i++) {
        int o, a, k, b;
        cin >> o >> a >> b >> k;
        q[i] = {o, a, b, k};
        if (o == 1) {
            r = min(r, (double)(k - eps));
        }
    }
    for (int i = 1; i <= t; i++) {
        int x, v;
        cin >> x >> v;
        p[x] = v;
    }
    while (r - l > eps) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            l   = mid;
            ans = mid;
        } else {
            r = mid;
        }
    }
    if (ans == -1) {
        cout << -1 << endl;
    } else {
        printf("%.10lf", ans);
    }
    return 0;
}
```