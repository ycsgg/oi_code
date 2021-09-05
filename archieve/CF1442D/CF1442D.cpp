#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
#define int ll
const int N = 3005;
vector<int> items[N];
vector<ll> dp;
ll w[N];
int cnt[N];
int n, k;
ll ans = 0;
void solve(int l, int r) {
    if (l == r) {
        int tot = 0;
        int sum = 0;
        for (int x : items[l]) {
            tot++;
            sum += x;
            ans = max(ans, dp[k - tot] + sum);
            if (tot >= k) {
                break;
            }
        }
        return;
    }
    auto tmp = dp;
    int mid = l + r >> 1;
    for (int i = l; i <= mid; i++) {
        for (int j = k; j >= cnt[i]; --j)
            dp[j] = max(dp[j], dp[j - cnt[i]] + w[i]);
    }
    solve(mid + 1, r);
    dp = tmp;
    for (int i = mid + 1; i <= r; i++) {
        for (int j = k; j >= cnt[i]; --j)
            dp[j] = max(dp[j], dp[j - cnt[i]] + w[i]);
    }
    solve(l, mid);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> cnt[i];
        items[i].resize(cnt[i]);
        for (auto &v : items[i]) {
            cin >> v;
            w[i] += v;
        }
    }
    dp.resize(k + 1);
    solve(1, k + 1);
    cout << ans << endl;    
    return 0;
}
// Asusetic eru quionours.