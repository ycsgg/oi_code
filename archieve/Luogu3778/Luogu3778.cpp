#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1005;
const ll INF = (1ll << 30);
ll dis[N][N], w[N][N];
ll B[N][N], S[N][N];
ll Q[N][N];
int n, m, K;
bool check(int x) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                Q[i][j] = -INF;
                continue;
            }
            Q[i][j] = w[i][j] - x * dis[i][j];
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                Q[i][j] = max(Q[i][j], Q[i][k] + Q[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (Q[i][i] >= 0) {
            return true;
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> K;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= K; j++) {
            cin >> B[i][j] >> S[i][j];
            if (B[i][j] == -1) {
                B[i][j] = INF;
            }
            if (S[i][j] == -1) {
                S[i][j] = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= K; k++) {
                w[i][j] = max(w[i][j], S[j][k] - B[i][k]);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = w;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!dis[i][j]) {
                dis[i][j] = INF;
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    ll l = 1, r = 1e9, res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << res;
    return 0;
}
// Asusetic eru quionours.