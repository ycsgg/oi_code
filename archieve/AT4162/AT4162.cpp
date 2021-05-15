#include <bitset>
#include <iostream>
using namespace std;
struct Edge {
    int v;
    int nxt;
} edge[700 * 701];
int head[701], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, m;
bool G[707][707];
bool col[707], vis[707];
int cnt[2];
bool flag = 1;
void dfs(int x, int c) {
    vis[x] = 1;
    col[x] = c;
    cnt[c]++;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!vis[v]) {
            dfs(v, 1 - c);
        } else if (col[v] == c) {
            cout << "-1" << endl;
            exit(0);
        }
    }
}
int calc(int x) {
    return x * (x - 1) + (n - x) * (n - x - 1);
}
bool val[701 * 701];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = G[v][u] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && !G[i][j]) {
                add(i, j);
            }
        }
    }
    val[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cnt[0] = cnt[1] = 0;
            dfs(i, 0);
            for (int j = n; j >= 0; j--) {
                bool ans = 0;
                if (j >= cnt[0]) {
                    ans |= val[j - cnt[0]];
                }
                if (j >= cnt[1]) {
                    ans |= val[j - cnt[1]];
                }
                val[j] = ans;
            }
        }
    }
    int ans = 0x7f7f7f7f;
    for (int i = 1; i <= n; i++) {
        if (val[i]) {
            ans = min(ans, calc(i));
        }
    }
    cout << ans / 2 << endl;
    return 0;
}
// Asusetic eru quionours
