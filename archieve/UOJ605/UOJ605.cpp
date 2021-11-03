#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ull = unsigned long long;
using ll = long long;
const int N = 5e4 + 10;
const int K = 155;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G;
int n, m, k;
int p[N];
vector<int> tag[K];
ll ans[2 * K];
void ShortestPath(int s) {
    vector<int> dis(n + 1, -1);
    queue<int> q;
    for (auto v : tag[s]) {
        dis[v] = 0;
        q.push(v);
    }
    vector<int> vis(k + 1, -1);
    vector<int> topo;
    while (!q.empty()) {
        auto now = q.front();
        topo.push_back(now);
        q.pop();
        if (p[now] != s) {
            ans[dis[now] + 1] += 1ll * tag[s].size();
        }
        if (vis[p[now]] == -1) {
            vis[p[now]] = now;
            for (auto v : tag[p[now]]) {
                if (dis[v] == -1) {
                    dis[v] = dis[now] + 1;
                    q.push(v);
                }
            }
        }
        for (auto v : G.edge[now]) {
            if (dis[v] == -1) {
                dis[v] = dis[now] + 1;
                q.push(v);
            }
        }
    }
    ans[2 * k] += 1ll * (count(dis.begin(), dis.end(), -1) - 1) * tag[s].size();
    ans[1] += 1ll * tag[s].size() * (tag[s].size() - 1);
    for (int i = 0; i < (int)(tag[s].size()); i += 64) {
        vector<ull> pre(n + 1), suf(n + 1);
        for (int j = 0; j < 64 && i + j < (int)(tag[s].size()); j++) {
            pre[tag[s][i + j]] = 1ull << j;
        }
        for (auto v : topo) {
            if (p[v] != s) {
                if (dis[v] == dis[vis[p[v]]]) {
                    suf[p[v]] |= pre[v];
                } else {
                    pre[v] |= suf[p[v]];
                }
                int c = __builtin_popcountll(pre[v]);
                ans[dis[v] + 1] -= 1ll * c;
                ans[dis[v]] += 1ll * c;
            }
            for (auto k : G.edge[v]) {
                if (dis[k] == dis[v] + 1) {
                    pre[k] |= pre[v];
                }
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        tag[p[i]].push_back(i);
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u);
    }
    for (int s = 1; s <= k; s++) {
        ShortestPath(s);
    }
    for (int i = 0; i <= 2 * k; i++) {
        cout << ans[i] / 2 << ' ';
    }
    return 0;
}
// Asusetic eru quionours.