#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
struct Data {
    int x, y, typ;
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> x_axis(n), y_axis(m);
        map<int, int> sumy, sumx;
        map<pair<int, int>, int> cnty, cntx;
        set<int> yc, xc;
        for (auto &v : x_axis) {
            cin >> v;
            xc.insert(v);
        }
        for (auto &v : y_axis) {
            cin >> v;
            yc.insert(v);
        }
        for (int i = 1; i <= k; i++) {
            int x, y;
            cin >> x >> y;
            if (xc.count(x) && yc.count(y)) {
                continue;
            }
            if (xc.count(x)) {
                auto pos = *(yc.lower_bound(y));
                sumy[pos]++;
                cnty[make_pair(x, pos)]++;
            }
            if (yc.count(y)) {
                auto pos = *(xc.lower_bound(x));
                sumx[pos]++;
                cntx[make_pair(pos, y)]++;
            }
        }
        long long ans = 0;
        for (auto [_, v] : sumx) {
            ans += 1ll * v * (v - 1) / 2;
        }
        for (auto [_, v] : sumy) {
            ans += 1ll * v * (v - 1) / 2;
        }
        for (auto [_, v] : cntx) {
            ans -= 1ll * v * (v - 1) / 2;
        }
        for (auto [_, v] : cnty) {
            ans -= 1ll * v * (v - 1) / 2;
        }
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.