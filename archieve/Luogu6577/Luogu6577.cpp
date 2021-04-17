#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N  = 500;
const ll INF = 2e18;
int n, m;
ll G[N + 7][N + 7];
int linky[N + 7], visy[N + 7];
ll lx[N + 7], ly[N + 7], p[N + 7], slack[N + 7];
void bfs(int u) {
    int x, v = 0, vl = 0, mmin;
    for (int i = 1; i <= n; i++) {
        p[i]     = 0;
        slack[i] = INF;
    }
    linky[v] = u;
    do {
        x = linky[v], mmin = INF, visy[v] = 1;
        for (int y = 1; y <= n; y++) {
            if (!visy[y]) {
                if (slack[y] > lx[x] + ly[y] - G[x][y]) {
                    slack[y] = lx[x] + ly[y] - G[x][y];
                    p[y]     = v;
                }
                if (slack[y] < mmin) {
                    mmin = slack[y];
                    vl   = y;
                }
            }
        }
        for (int y = 0; y <= n; y++) {
            if (visy[y]) {
                lx[linky[y]] -= mmin;
                ly[y] += mmin;
            } else {
                slack[y] -= mmin;
            }
        }
        v = vl;
    } while (linky[v]);
    while (v) {
        linky[v] = linky[p[v]];
        v        = p[v];
    }
}
ll KM() {
    memset(linky, 0, sizeof(linky));
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= n; i++) {
        memset(visy, 0, sizeof(visy));
        bfs(i);
    }
    ll res = 0;
    for (int y = 1; y <= n; y++) {
        res += G[linky[y]][y];
    }
    return res;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G[i][j] = -INF;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        G[u][v] = max(G[u][v], w);
    }
    printf("%lld\n", KM());
    for (int i = 1; i <= n; i++) {
        printf("%d ", linky[i]);
    }
    return 0;
}