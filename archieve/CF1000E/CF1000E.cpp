#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
const int N = 3e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G, Tr;
vector<pair<int, int>> e;
int n, m;
int dfn[N], low[N], tim;
int st[N], top, scc[N], scctot;
unordered_set<int> exist[N];
void Tarjan(int x, int pre, const Graph &G) {
    dfn[x] = low[x] = ++tim;
    st[++top] = x;
    for (auto v : G.edge[x]) {
        if (v == pre) {
            continue;
        }
        if (!dfn[v]) {
            Tarjan(v, x, G);
            low[x] = min(low[x], low[v]);
        } else if (!scc[v]) {
            low[x] = min(low[x], dfn[v]);
        }
    }
    if (low[x] == dfn[x]) {
        ++scctot;
        int now = 0;
        do {
            now = st[top--];
            scc[now] = scctot;
        } while (now != x);
    }
}
int dep[N];
void dfs(int now, int fa, const Graph &G) {
    dep[now] = dep[fa] + 1;
    for (auto v : G.edge[now]) {
        if (v != fa) {
            dfs(v, now, G);
        }
    }
}
int diameter(const Graph &G) {
    dfs(1, 0, G);
    int maxid = 1;
    for (int i = 1; i <= n; i++) {
        if (dep[i] > dep[maxid]) {
            maxid = i;
        }
    }
    dfs(maxid, 0, G);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, dep[i]);
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back(make_pair(u, v));
        e.push_back(make_pair(v, u));
        G.add(u, v);
        G.add(v, u);
    }
    Tarjan(1, 0, G);
    for (auto p : e) {
        int x = scc[p.first];
        int y = scc[p.second];
        if (x != y && !exist[x].count(y)) {
            Tr.add(x, y);
            exist[x].insert(y);
        }
    }
    cout << diameter(Tr) - 1;
    return 0;
}
// Asusetic eru quionours.
