#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 105000;
typedef long long ll;
int f[N];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int x, int y) {
    x    = find(x);
    y    = find(y);
    f[x] = y;
}
vector<int> Tr[N], G[N];
ll dp[N], s[N];
int c[N], b[N];
void pre(int x) {
    s[x] = b[x];
    for (auto v : Tr[x]) {
        pre(v);
        s[x] += s[v];
    }
}
void dfs(int x) {
    if (!Tr[x].size())
        dp[x] = b[x] + c[x];
    else
        dp[x] = 2e19;
    for (auto v : Tr[x]) {
        dfs(v);
        dp[x] = min(dp[x], s[x] - s[v] + max((ll)c[x], dp[v]));
    }
}
bool cmp(const int &A, const int &B) {
    return c[A] < c[B];
}
int n, m, p[N];
bool vis[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> b[i];
        f[i] = i;
        c[i] = max(c[i] - b[i], 0);
        p[i] = i;
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    sort(p + 1, p + n + 1, cmp);
    for (int t = 1; t <= n; t++) {
        int u = p[t];
        for (auto v : G[u]) {
            if (vis[v]) {
                v = find(v);
                u = find(u);
                if (u != v) {
                    merge(v, u);
                    Tr[u].push_back(v);
                }
            }
        }
        vis[u] = 1;
    }
    pre(p[n]);
    dfs(p[n]);
    cout << dp[p[n]];
    return 0;
}
// Asusetic eru quionours
