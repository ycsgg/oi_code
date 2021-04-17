#include <cstring>
#include <iostream>
using namespace std;
const int N = 25;
int A[N][N], B[N][N];
int lx[N], ly[N], p[N], slack[N], linky[N];
bool visy[N];
int n;
int G[N][N];
int ans;
void bfs(int u) {
    int x, v = 0, vl = 0, mmin;
    for (int i = 1; i <= n; i++) {
        p[i]     = 0;
        slack[i] = 0x7f7f7f7f;
    }
    linky[v] = u;
    do {
        x = linky[v], mmin = 0x7f7f7f7f, visy[v] = 1;
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
int KM(int s) {
    for (int i = 1; i <= n; i++) {
        memset(visy, 0, sizeof(visy));
        for (int j = 1; j <= n; j++) {
            G[i][j] = ((1 << i - 1) & s) ? A[i][j] : B[i][j];
        }
        bfs(i);
    }
    int res = 0;
    for (int y = 1; y <= n; y++) {
        res += G[linky[y]][y];
    }
    return res;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> A[i][j];
            A[i][0] = max(A[i][0], A[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> B[i][j];
            B[i][0] = max(B[i][0], B[i][j]);
        }
    }
    int S = (1 << n) - 1;
    for (int s = 0; s <= S; s++) {
        if (__builtin_popcount(s) != n / 2) {
            continue;
        }
        for (int i = 1; i <= n; i++) {
            lx[i] = ((1 << (i - 1)) & s) ? A[i][0] : B[i][0];
            ly[i] = visy[i] = linky[i] = 0;
        }
        ans = max(ans, KM(s));
    }
    cout << ans;
    return 0;
}