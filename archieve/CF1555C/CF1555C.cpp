#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        vector<int> sa(n), sb(n);
        for (auto &v : a) {
            cin >> v;
        }
        for (auto &v : b) {
            cin >> v;
        }
        auto fsum = accumulate(a.begin(), a.end(), 0);
        auto rsum = 0;
        int ans = 1e9 + 10;
        for (int i = 0; i < n; i++) {
            fsum -= a[i];
            ans = min(ans, max(fsum, rsum));
            rsum += b[i];
        }
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.