#include <iostream>
using namespace std;
const int N = 1e5 + 5;
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int f[N][50];
int ans[N];
int n, k;
void dfs1(int x, int fa) {
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) {
            continue;
        }
        dfs1(v, x);
        for (int j = 1; j <= k; j++) {
            f[x][j] += f[v][j - 1];
        }
    }
}
void calc(int x, int y) {
    for (int i = 1; i <= k; i++) {
        f[x][i] -= f[y][i - 1];
    }
    for (int i = 1; i <= k; i++) {
        f[y][i] += f[x][i - 1];
    }
}
void dfs2(int x, int fa) {
    for (int i = 0; i <= k; i++) {
        ans[x] += f[x][i];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa)
            continue;
        calc(x, v);
        dfs2(v, x);
        calc(v, x);
    }
}
int main() {
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> f[i][0];
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}