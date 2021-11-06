#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 5e5 + 10;
vector<int> a[N], rmin[N], rmax[N];
int id[N], lmin[N], lmax[N], col[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        a[i].resize(m + 1);
        rmin[i].resize(m + 1);
        rmax[i].resize(m + 1);
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
        rmin[i][m] = rmax[i][m] = a[i][m];
        for (int j = m - 1; j >= 1; j--) {
            rmin[i][j] = min(rmin[i][j + 1], a[i][j]);
            rmax[i][j] = max(rmax[i][j + 1], a[i][j]);
        }
        id[i] = i;
    }
    sort(id + 1, id + 1 + n, [&](const auto &A, const auto &B) -> bool {
        return a[A][1] > a[B][1];
    });
    for (int k = 1; k <= m - 1; k++) {
        if (k == 1) {
            for (int i = 1; i <= n; i++) {
                lmin[i] = lmax[i] = a[id[i]][1];
            }
        } else {
            for (int i = 1; i <= n; i++) {
                lmin[i] = min(lmin[i], a[id[i]][k]);
                lmax[i] = max(lmax[i], a[id[i]][k]);
            }
        }
        vector<int> lk(n + 1), rk(n + 1);
        lk[n] = lmax[n];
        rk[n] = rmin[id[n]][k + 1];
        for (int i = n - 1; i >= 1; i--) {
            lk[i] = max(lk[i + 1], lmax[i]);
            rk[i] = min(rk[i + 1], rmin[id[i]][k + 1]);
        }

        int lm = lmin[1];
        int rm = rmax[id[1]][k + 1];
        for (int i = 1; i <= n - 1; i++) {
            lm = min(lm, lmin[i]);
            rm = max(rm, rmax[id[i]][k + 1]);
            if (lm > lk[i + 1] && rm < rk[i + 1]) {
                cout << "YES\n";
                for (int j = 1; j <= i; j++) {
                    col[id[j]] = 1;
                }
                for (int j = i + 1; j <= n; j++) {
                    col[id[j]] = 0;
                }
                for (int j = 1; j <= n; j++) {
                    if (col[j]) {
                        cout << 'R';
                    } else {
                        cout << 'B';
                    }
                }
                cout << ' ' << k << '\n';
                return;
            }
        }
    }
    cout << "NO\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int _ = 0;
    cin >> _;
    while (_--) {
        solve();
    }

    return 0;
}
// Asusetic eru quionours.