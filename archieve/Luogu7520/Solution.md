### P7520 [省选联考 2021 A 卷] 支配

~~2021省选A卷最后一块拼图~~

显然支配关系会构成一个树，假如我们通过奥妙重重的方法拿到了这个树

考虑加入边 $(u,v)$ 的影响，可以发现若 $x$ 的受支配集变化当且仅当 $fa_x$ 的受支配集变化或者 $fa_x$ 不支配 $x$

直接枚举点判断，从根节点向下找虽然也行，不过按 $bfs$ 序更好写

建树可以用 $O(n^2)$ 的算法，也就是枚举每个点删除后 $1$ 到其他点的连通性即可

总复杂度 $O(n^2+qn)$

```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N = 3005;
struct Graph {
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
} G, rG;
int n, m, q;
bool dom[N][N], qaq[N][N];
int in[N], fa[N], id[N];
void build() {
    for (int i = 1; i <= n; i++) {
        dom[1][i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            dom[i][j] = 1;
        }
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int _i = G.head[x]; _i; _i = G.edge[_i].nxt) {
                int v = G.edge[_i].v;
                if (dom[i][v] && (i != v)) {
                    dom[i][v] = 0;
                    q.push(v);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            in[j] += dom[i][j];
        }
    }
    queue<int> q;
    q.push(1);
    static int que[N], head;
    que[++head] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 1; i <= n; i++) {
            if (dom[x][i]) {
                --in[i];
                if (in[i] == 1) {
                    fa[i] = x;
                    q.push(i);
                    que[++head] = i;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        id[i] = que[i];
    }
    for (int i = 2; i <= n; i++) {
        queue<int> q;
        q.push(i);
        qaq[i][i] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int j = rG.head[x]; j; j = rG.edge[j].nxt) {
                int v = rG.edge[j].v;
                if (!qaq[i][v] && (v != fa[i])) {
                    qaq[i][v] = 1;
                    q.push(v);
                }
            }
        }
    }
}
int main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G.add(u, v);
        rG.add(v, u);
    }
    build();
    while (q--) {
        static bool vis[N];
        int a, b;
        scanf("%d%d", &a, &b);
        int ans = 0;
        for (int i = 2; i <= n; i++) {
            vis[id[i]] =
                ((!dom[fa[id[i]]][a] && qaq[id[i]][b]) || (vis[fa[id[i]]]));
            ans += vis[id[i]];
        }
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours

```

