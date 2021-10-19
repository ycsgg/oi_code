#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 5e6 + 10;
int n, m;
int prufer[N], fa[N], deg[N];
namespace Tree2Prufer {
void solve() {
    for (int i = 1; i < n; i++) {
        cin >> fa[i];
        deg[fa[i]]++;
    }
    for (int i = 1, j = 1; i <= n - 2; i++, j++) {
        while (deg[j]) {
            ++j;
        }
        prufer[i] = fa[j];
        while (i <= n - 2 && !--deg[prufer[i]] && prufer[i] < j) {
            prufer[i + 1] = fa[prufer[i]];
            i++;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n - 2; i++) {
        ans ^= 1ll * i * prufer[i];
    }
    cout << ans;
}
} // namespace Tree2Prufer
namespace Prufer2Tree {
void solve() {
    for (int i = 1; i <= n - 2; i++) {
        cin >> prufer[i];
        ++deg[prufer[i]];
    }
    prufer[n - 1] = n;
    for (int i = 1, j = 1; i < n; i++, j++) {
        while (deg[j]) {
            ++j;
        }
        fa[j] = prufer[i];
        while (i < n && !--deg[prufer[i]] && prufer[i] < j) {
            fa[prufer[i]] = prufer[i + 1];
            i++;
        }
    }
    long long ans = 0;
    for (int i = 1; i < n; i++)
        ans ^= 1ll * i * fa[i];
    cout << ans;
}
} // namespace Prufer2Tree

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    if (m == 1) {
        Tree2Prufer::solve();
    } else {
        Prufer2Tree::solve();
    }
    return 0;
}
// Asusetic eru quionours.