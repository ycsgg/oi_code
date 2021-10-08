#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 3 * 1e5 + 5;
const int LIM = 1e5;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
};
namespace Tarjan {
int dfn[N], low[N], st[N], top, id, scctot;
int scc[N];
void _Tarjan(int x, const Graph &G) {
    dfn[x] = low[x] = ++id;
    st[++top] = x;
    for (auto v : G.edge[x]) {
        if (!dfn[v]) {
            _Tarjan(v, G);
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
void Tarjan(const Graph &G) {
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
    memset(low, 0, sizeof(low));
    id = top = scctot = 0;
    for (int i = 1; i <= LIM; i++) {
        if (!dfn[i]) {
            _Tarjan(i, G);
        }
    }
}
bool in_scc(int x, int y) {
    return scc[x] == scc[y];
}
} // namespace Tarjan

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        Graph G;
        vector<int> w(n), e(n);
        for (auto &v : w) {
            cin >> v;
        }
        for (auto &v : e) {
            cin >> v;
        }
        for (int i = 0; i < n; i++) {
            G.add(w[i], e[i]);
        }
        for (int i = 1; i <= LIM; i++) {
            for (int j = 2 * i; j <= LIM; j += i) {
                G.add(i, j);
            }
        }
        Tarjan::Tarjan(G);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (Tarjan::in_scc(w[i], e[i])) {
                ans++;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.
