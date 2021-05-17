#include <cstring>
#include <iostream>
using namespace std;
const int N = 505;
int n, k;
char c[N][N];
int sum[N][N];
int id[N][N];
int vis[N * N];
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
bool checkbound(int x, int y) {
    return (x <= n) && (x >= 1) && (y <= n) && (y >= 1);
}
int tot;
int idcnt, cnt[N * N];
void dfs(int x, int y) {
    tot++;
    id[x][y] = idcnt;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (!checkbound(nx, ny) || id[nx][ny] || (c[nx][ny] != '.'))
            continue;
        dfs(nx, ny);
    }
}
void add(int x, int y) {
    if (!id[x][y])
        return;
    if (!vis[id[x][y]])
        tot += cnt[id[x][y]];
    vis[id[x][y]]++;
}
void del(int x, int y) {
    if (!id[x][y]) {
        return;
    }
    vis[id[x][y]]--;
    if (!vis[id[x][y]]) {
        tot -= cnt[id[x][y]];
    }
}
int calc(int x, int y) {
    return sum[x + k - 1][y + k - 1] - sum[x + k - 1][y - 1] -
           sum[x - 1][y + k - 1] + sum[x - 1][y - 1];
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
            if (c[i][j] == '.') {
                sum[i][j]++;
            }
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (c[i][j] == '.' && !id[i][j]) {
                idcnt++;
                tot = 0;
                dfs(i, j);
                cnt[idcnt] = tot;
            }
        }
    }
    int ans = -1;
    for (int i = 1; i <= n - k + 1; i++) {
        memset(vis, 0, sizeof(vis));
        tot = 0;
        for (int j = i - 1; j <= k + i; j++) {
            for (int p = 1; p <= k; p++) {
                add(j, p);
            }
        }
        for (int j = i; j < k + i; j++) {
            add(j, k + 1);
        }
        ans = max(ans, tot + k * k - calc(i, 1));
        for (int j = 2; j <= n - k + 1; ++j) {
            for (int l = i; l < i + k; ++l) {
                del(l, j - 2);
                add(l, j + k);
            }
            del(i - 1, j - 1);
            del(i + k, j - 1);
            add(i - 1, j + k - 1);
            add(i + k, j + k - 1);
            ans = max(ans, tot + k * k - calc(i, j));
        }
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours