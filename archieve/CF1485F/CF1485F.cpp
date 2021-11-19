#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<int> b(n);
        unordered_map<ll, ll> dp;
        dp[0] = 1;
        ll offset = 0, ans = 1;
        for (auto &v : b) {
            cin >> v;
        }
        for (auto v : b) {
            ll tmp = (ans - dp[-offset] + mod) % mod;
            ans = (ans + tmp) % mod;
            dp[-offset] = (dp[-offset] + tmp) % mod;
            offset += v;
        }
        ans = (ans + mod) % mod;
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.