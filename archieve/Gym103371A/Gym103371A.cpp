#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1005;
int n;
ll E[N][N], A[N][N];
ll row[N], col[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> E[i][j];
        }
    }
    ll sumir = 0, sum1r = 0;
    ll sumic = 0, sum1c = 0;
    for (int i = 2; i < n; i++) {
        row[i] = (E[i + 1][1] - E[i][1] - E[i][1] + E[i - 1][1]) / 2;
        col[i] = (E[1][i + 1] - E[1][i] - E[1][i] + E[1][i - 1]) / 2;
        sumir = sumir + 1ll * (n - i) * row[i];
        sumic = sumic + 1ll * (n - i) * col[i];
        sum1r = sum1r + 1ll * (i - 1) * row[i];
        sum1c = sum1c + 1ll * (i - 1) * col[i];
    }
    ll x = (E[n][n] - sumir - sumic) / (n - 1);
    ll y = (E[n][1] - sumir - sum1c) / (n - 1);
    ll z = (E[1][n] - sum1r - sumic) / (n - 1);
    ll w = accumulate(row + 2, row + n, 0ll);
    ll v = accumulate(col + 2, col + n, 0ll);
    row[1] = (v - w + 2ll * x + y - z) / 4;
    col[1] = x - row[1];
    col[n] = y - row[1];
    row[n] = z - col[1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A[i][j] = min(row[i], col[j]);
            row[i] -= A[i][j];
            col[j] -= A[i][j];
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
// Asusetic eru quionours.