#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1005;
int n, m, q;
int f[N][N][2], lock[N][N];
int ans;
void change(int x, int y, int s) {
    if (s == 0) {
        x--;
    } else {
        y--;
    }
    while (x && y) {
        if (lock[x][y]) {
            break;
        }
        ans -= f[x][y][0] - f[x][y + 1][1] - 1;
        ans -= f[x][y][1] - f[x + 1][y][0] - 1;
        f[x][y][0] = f[x][y + 1][1] + 1;
        f[x][y][1] = f[x + 1][y][0] + 1;
        if (s) {
            x--;
        } else {
            y--;
        }
        s ^= 1;
    }
}
int main() {
    cin >> n >> m >> q;
    int tot = n * m;
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            f[i][j][0] = f[i][j + 1][1] + 1;
            f[i][j][1] = f[i + 1][j][0] + 1;
            ans += f[i][j][0] + f[i][j][1];
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (lock[x][y]) {
            tot++;
            lock[x][y] = 0;
            ans += (f[x][y + 1][1] + 1 - f[x][y][0]);
            ans += (f[x + 1][y][0] + 1 - f[x][y][1]);
            f[x][y][0] = f[x][y + 1][1] + 1;
            f[x][y][1] = f[x + 1][y][0] + 1;
            change(x, y, 0);
            change(x, y, 1);
        } else {
            lock[x][y] = 1;
            tot--;
            ans -= f[x][y][0] + f[x][y][1];
            f[x][y][0] = f[x][y][1] = 0;
            change(x, y, 0);
            change(x, y, 1);
        }
        cout << ans - tot << '\n';
    }
    return 0;
}
// Asusetic eru quionours.