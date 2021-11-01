#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
ll a[20];
ll dfs(int l, int r, int L, int R) {
    if (r - l <= 1) {
        return 0;
    }
    ll ans = 1e18;
    for (int i = l + 1; i <= r - 1; i++) {
        ans = min(ans,
                  dfs(l, i, L, L + R) + dfs(i, r, L + R, R) + a[i] * (L + R));
    }
    return ans;
}
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << dfs(1, n, 1, 1) + a[1] + a[n];
    return 0;
}
// Asusetic eru quionours.
