#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, q;
int a[N];
ll s[N];
namespace ST {
int lg[N];
ll mmax[N][20], mmin[N][20];
void init() {
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        mmax[i][0] = mmin[i][0] = s[i];
    }
    for (int j = 1; j <= 19; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            mmax[i][j] = max(mmax[i][j - 1], mmax[i + (1 << j - 1)][j - 1]);
            mmin[i][j] = min(mmin[i][j - 1], mmin[i + (1 << j - 1)][j - 1]);
        }
    }
}
ll querymin(int l, int r) {
    int k = lg[r - l + 1];
    return min(mmin[l][k], mmin[r - (1 << k) + 1][k]);
}
ll querymax(int l, int r) {
    int k = lg[r - l + 1];
    return max(mmax[l][k], mmax[r - (1 << k) + 1][k]);
}
} // namespace ST

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = x - a[i];
        s[i] = s[i - 1] + a[i];
    }
    ST::init();
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (s[r] - s[l - 1] != 0 || ST::querymin(l, r) < s[l - 1]) {
            cout << -1 << endl;
            continue;
        }
        cout << ST::querymax(l, r) - s[l - 1] << endl;
    }
    return 0;
}
// Asusetic eru quionours.