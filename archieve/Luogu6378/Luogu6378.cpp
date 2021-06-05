#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 5;
#define tr(x)    x
#define fs(x)    x + n
#define pretr(x) x + 2 * n
#define prefs(x) x + 3 * n
struct Graph {
    vector<vector<int>> edge;
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
};
namespace Two_SAT {
int dfn[N * 4], low[N * 4], scc[N * 4];
bool vis[N * 4];
int st[N * 4], top;
int dfn_id, scc_cnt;
void tarjan(int x, const Graph &G) {
    dfn[x] = low[x] = ++dfn_id;
    st[++top]       = x;
    vis[x]          = 1;
    for (auto v : G.edge[x]) {
        if (!dfn[v]) {
            tarjan(v, G);
            low[x] = min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = min(low[x], dfn[v]);
        }
    }
    if (low[x] == dfn[x]) {
        scc_cnt++;
        int now = 0;
        do {
            now      = st[top];
            vis[now] = 0;
            scc[now] = scc_cnt;
            top--;
        } while (now != x);
    }
}
bool Two_SAT(const Graph &G, int n) {
    top = 0;
    for (int i = 1; i < G.edge.size(); i++) {
        if (!dfn[i]) {
            tarjan(i, G);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[i + n] || scc[i + 2 * n] == scc[i + 4 * n]) {
            return false;
        }
    }
    return true;
}
} // namespace Two_SAT
int n, m, k;
Graph G;
int a[N];
int main() {
    cin >> n >> m >> k;
    G.edge.resize(4 * n + 2);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        G.add(fs(a), tr(b));
        G.add(fs(b), tr(a));
    }
    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        for (int j = 1; j <= x; j++) {
            cin >> a[j];
            G.add(tr(a[j]), pretr(a[j]));
            G.add(prefs(a[j]), fs(a[j]));
        }
        for (int j = 2; j <= x; j++) {
            G.add(pretr(a[j - 1]), pretr(a[j]));
            G.add(prefs(a[j]), prefs(a[j - 1]));
            G.add(pretr(a[j - 1]), fs(a[j]));
            G.add(tr(a[j]), prefs(a[j - 1]));
        }
    }
    cout << (Two_SAT::Two_SAT(G, n) ? "TAK" : "NIE") << endl;
    return 0;
}
// Asusetic eru quionours