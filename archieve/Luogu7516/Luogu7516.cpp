#include <iostream>
using namespace std;
const int N = 1005;
int G[N][N];
int tim[N * N];
int n, m, ans[N * N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = i;
    }
    for (int k = n; k >= 1; k--) {
        for (int i = k + 1; i <= n; i++) {
            tim[min(G[k][i], G[i][k])]++;
        }
        for (int i = 1; i <= n; i++) {
            if (!G[i][k]) {
                continue;
            }
            int nowid = G[i][k];
            if (i > k) {
                for (int j = 1; j < k; j++) {
                    G[i][j] = max(G[i][j], min(nowid, G[k][j]));
                }
            } else {
                for (int j = 1; j <= n; j++) {
                    G[i][j] = max(G[i][j], min(nowid, G[k][j]));
                }
            }
        }
    }
    ans[m + 1] = n;
    for (int i = m; i >= 1; i--) {
        ans[i] = ans[i + 1] + tim[i];
    }
    for (int i = 1; i <= m + 1; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
