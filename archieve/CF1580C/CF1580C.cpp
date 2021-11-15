#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, m;
int x[N], y[N];
int op[N], k[N];
int exist[N], cnt[N];
int f[503][504];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int B = sqrt(m);
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> op[i] >> k[i];
        if (x[k[i]] + y[k[i]] > B) {
            if (op[i] == 1) {
                exist[k[i]] = i;
            } else {
                for (int j = exist[k[i]] + x[k[i]]; j <= i;
                     j += x[k[i]] + y[k[i]]) {
                    cnt[j]++;
                    cnt[min(i, j + y[k[i]])]--;
                }
                exist[k[i]] = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (exist[i]) {
            for (int j = exist[i] + x[i]; j <= m; j += x[i] + y[i]) {
                cnt[j]++;
                cnt[min(m + 1, j + y[i])]--;
            }
            exist[i] = 0;
        }
    }
    for (int i = 1; i <= m; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 1; i <= m; i++) {
        if (x[k[i]] + y[k[i]] <= B) {
            if (op[i] == 1) {
                exist[k[i]] = i;
                auto X = x[k[i]];
                auto Y = y[k[i]];
                for (int j = X; j < X + Y; j++) {
                    f[X + Y][(j + i) - (j + i) / (X + Y) * (X + Y)]++;
                }
            } else {
                auto X = x[k[i]];
                auto Y = y[k[i]];
                auto st = exist[k[i]];
                for (int j = X; j < X + Y; j++) {
                    f[X + Y][(j + st) - (j + st) / (X + Y) * (X + Y)]--;
                }
            }
        }
        for (int j = 1; j <= B; j++) {
            cnt[i] += f[j][i - i / j * j];
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << cnt[i] << '\n';
    }
    return 0;
}
// Asusetic eru quionours.