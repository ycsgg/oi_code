#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 3005;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} Tr;
int n;
int st[N], top, path[N], tot;
bool vis[N], mark[N];
bool flag;
void FindCycle(int x, int pre) {
    if (vis[x]) {
        int v = st[top];
        do {
            v = st[top--];
            path[++tot] = v;
            mark[v] = 1;
        } while (x != v);
        flag = 1;
        return;
    }
    st[++top] = x;
    vis[x] = 1;
    for (auto v : Tr.edge[x]) {
        if (flag) {
            return;
        }
        if (v != pre) {
            FindCycle(v, x);
        }
    }
    vis[x] = 0;
    top--;
}
int fa[N][12], dep[N], id[N];
void dfs(int x, int _fa, int _id) {
    id[x] = _id;
    dep[x] = dep[_fa] + 1;
    fa[x][0] = _fa;
    for (int i = 1; i <= 11; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (auto v : Tr.edge[x]) {
        if (v != _fa && !mark[v]) {
            dfs(v, x, _id);
        }
    }
}
int LCA(int x, int y) {
    if (dep[x] > dep[y]) {
        swap(x, y);
    }
    for (int i = 11; ~i; i--) {
        if (dep[fa[y][i]] >= dep[x]) {
            y = fa[y][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 11; ~i; i--) {
        if (fa[y][i] != fa[x][i]) {
            y = fa[y][i];
            x = fa[x][i];
        }
    }
    return fa[x][0];
}
int dis(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[LCA(x, y)];
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    FindCycle(1, 0);
    for (int i = 1; i <= tot; i++) {
        dfs(path[i], 0, i);
    }
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                ans += 1;
                continue;
            }
            if (id[i] == id[j]) {
                ans += 1.0 / (dis(i, j) + 1);
            } else {
                int x = dep[i] + dep[j];
                int y = abs(id[i] - id[j]) - 1;
                int z = tot - 2 - y;
                ans += 1.0 / (x + y) + 1.0 / (x + z) - 1.0 / (x + y + z);
            }
        }
    }
    printf("%.10lf", ans);
    return 0;
}
// Asusetic eru quionours.