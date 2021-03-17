#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n;
ll mods[N];
ll tmp[N];
map<ll, ll, greater<ll>> dp;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> mods[i];
    }
    dp[mods[1] - 1] = 0;
    for (int i = 1; i < n; i++) {
        int cnt = 0;
        for (auto data : dp) {
            ll j = data.first;
            ll b = data.second;
            if (j < mods[i + 1]) {
                break;
            }
            dp[mods[i + 1] - 1] =
                max(dp[mods[i + 1] - 1],
                    b + (ll)i * (mods[i + 1] * ((j + 1) / mods[i + 1]) -
                                 mods[i + 1]));
            dp[j % mods[i + 1]] =
                max(dp[j % mods[i + 1]], (b + (ll)i * (j - j % mods[i + 1])));
            tmp[cnt++] = j;
        }
        while (cnt--) {
            dp.erase(tmp[cnt]);
        }
    }
    ll ans  = 0;
    ll mmax = 0;
    for (auto i : dp) {
        ans = max(ans, i.first * n + i.second);
    }
    cout << ans << endl;
    return 0;
}