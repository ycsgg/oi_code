#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} Tr;
int n, m;
bool vis[N], flag;
int pos;
int son[N];
int fa[N];
double down[N], up[N];
void dp_down(int x, int _fa) {
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        auto w = e.w;
        if (v != _fa && !vis[v]) {
            fa[v] = 1;
            dp_down(v, x);
            son[x]++;
            down[x] += down[v] + e.w;
        }
    }
    if (son[x]) {
        down[x] /= son[x];
    }
}
void dp_up(int x, int _fa, int w) {
    up[x] = w;
    if (fa[_fa] + son[_fa] - 1 != 0) {
        up[x] += (up[_fa] * fa[_fa] + down[_fa] * son[_fa] - down[x] - w) /
                 (fa[_fa] + son[_fa] - 1);
    }
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        auto w = e.w;
        if (v != _fa) {
            dp_up(v, x, w);
        }
    }
}
namespace Tree {
void solve() {
    dp_down(1, 0);
    for (auto e : Tr.edge[1]) {
        auto v = e.v;
        auto w = e.w;
        dp_up(v, 1, w);
    }
}
} // namespace Tree
namespace CycleTree {
void FindCycle(int x, int pre) {
    vis[x] = 1;
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        if (v != pre) {
            if (vis[v]) {
                pos = v;
                return;
            }
            FindCycle(v, x);
            if (!flag && pos) {
                if (pos == x) {
                    flag = 1;
                }
                return;
            }
            if (flag) {
                break;
            }
        }
    }
    vis[x] = false;
}
int path[220], dfn[220], tot;
int disl[220], disr[220];
void SplitCycle(int x, int pre) {
    dfn[x] = ++tot;
    path[tot] = x;
    ::fa[x] = 2;
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        auto w = e.w;
        if (v != pre && vis[v]) {
            if (!dfn[v]) {
                SplitCycle(v, x);
            }
            disr[dfn[x]] = disl[dfn[v]] = w;
            break;
        }
    }
}
void solve() {
    FindCycle(1, 0);
    SplitCycle(pos, 0);
    for (int i = 1; i <= tot; i++) {
        dp_down(path[i], 0);
    }
    static auto getnxt = [&](int x) -> int {
        return x % tot + 1;
    };
    static auto getpre = [&](int x) -> int {
        if (x == 1) {
            return tot;
        } else {
            return x - 1;
        }
    };
    for (int i = 1; i <= tot; i++) {
        auto now = path[i];
        auto P = 0.5;
        for (int j = getnxt(i); i != j; j = getnxt(j)) {
            auto v = path[j];
            if (getnxt(j) == i) {
                up[now] += P * (disl[j] + down[v]);
            } else {
                up[now] += P * (down[v] * son[v] / (son[v] + 1) + disl[j]);
            }
            P /= (son[v] + 1);
        }
        P = 0.5;
        for (int j = getpre(i); i != j; j = getpre(j)) {
            auto v = path[j];
            if (getpre(j) == i) {
                up[now] += P * (disr[j] + down[v]);
            } else {
                up[now] += P * (down[v] * son[v] / (son[v] + 1) + disr[j]);
            }
            P /= (son[v] + 1);
        }
        for (auto e : Tr.edge[now]) {
            auto v = e.v;
            auto w = e.w;
            if (!vis[v]) {
                dp_up(v, now, e.w);
            }
        }
    }
}
} // namespace CycleTree

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Tr.add(u, v, w);
        Tr.add(v, u, w);
    }
    if (n == m) {
        CycleTree::solve();
    } else {
        Tree::solve();
    }
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        // printf("%lf | %d | %lf | %d\n", down[i], son[i], up[i], fa[i]);
        ans += (down[i] * son[i] + up[i] * fa[i]) / (son[i] + fa[i]);
    }
    printf("%.5lf", ans / n);
    return 0;
}
// Asusetic eru quionours.
