#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1 << 20;
const int INF = 0x3f3f3f3f;
int n, k;
int ans[N], mmin[N], mmax[N];
int main() {
    cin >> n >> k;
    for (int i = 0; i < (1 << k); i++) {
        ans[i] = mmin[i] = INF;
        mmax[i] = -INF;
    }
    while (n--) {
        int x;
        cin >> x;
        mmin[x] = mmax[x] = 0;
    }
    for (int i = 0; i < k; i++) {
        for (int x = 0; x < (1 << k); x++) {
            if (x & (1 << i)) {
                auto y = x ^ (1 << i);
                ans[x] = ans[y] = min(ans[x], ans[y]);
                ans[x] = min(ans[x], mmin[y] - mmax[x] + (1 << i));
                ans[y] = min(ans[y], mmin[x] - mmax[y] + (1 << i));
                auto mminx = mmin[x], mminy = mmin[y];
                auto mmaxx = mmax[x], mmaxy = mmax[y];
                mmin[x] = min(mminx, mminy + (1 << i));
                mmin[y] = min(mminy, mminx + (1 << i));
                mmax[x] = max(mmaxx, mmaxy + (1 << i));
                mmax[y] = max(mmaxy, mmaxx + (1 << i));
            }
        }
    }
    for (int i = 0; i < (1 << k); i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}
// Asusetic eru quionours.
