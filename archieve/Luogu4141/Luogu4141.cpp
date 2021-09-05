#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2005;
int n, m;
int w[N];
int f[N], g[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    f[0] = 1;
    g[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= w[i]; j--) {
            f[j] = (f[j] + f[j - w[i]]) % 10;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j >= w[i]) {
                g[j] = (f[j] - g[j - w[i]] + 10) % 10;
            } else {
                g[j] = f[j] % 10;
            }
            cout << g[j];
        }
        cout << '\n';
    }
    return 0;
}
// Asusetic eru quionours.
