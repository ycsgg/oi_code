#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T, n, k;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        vector<int> a(n);
        for (auto &v : a) {
            cin >> v;
        }
        int l = 0, r = 1e9 + 10, ans = 0;
        static auto check = [&](int x) {
            int r = 0, res = 0, ans = 0;
            for (int i = 0; i < n; i++) {
                while (r < n && a[r] - a[i] <= x * 2) {
                    r++;
                }
                res = max(res, r - i);
                if (r - i >= k + 1) {
                    ans = (a[i] + a[r - 1]) / 2;
                }
            }
            if (res >= k + 1) {
                return make_pair(true, ans);
            } else {
                return make_pair(false, ans);
            }
        };
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid).first) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << check(ans).second << endl;
    }
    return 0;
}
// Asusetic eru quionours.