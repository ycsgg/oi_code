#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 100005;
using ll    = long long;
array<ll, N> s, cnt, tot, dp;
int n;
vector<ll> st[N];
ll X(int i) {
    return cnt[i];
}
ll Y(int i) {
    return dp[i - 1] + s[i] * cnt[i] * cnt[i] - 2 * s[i] * cnt[i];
}
double slope(int i, int j) {
    return 1.0 * (Y(i) - Y(j)) / (X(i) - X(j));
}
ll calc(int i, int j) {
    return dp[j - 1] + s[i] * (cnt[i] - cnt[j] + 1) * (cnt[i] - cnt[j] + 1);
}
#define top(x) max((int)x.size() - 1, 0)
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        cnt[i] = ++tot[s[i]];
    }
    for (int i = 1; i <= n; i++) {
        int t     = s[i];
        auto &stk = st[t];
        // cout << top(stk) << endl;
        while (top(stk) >= 1 && slope(stk[top(stk) - 1], i) >=
                                    slope(stk[top(stk) - 1], stk[top(stk)])) {
            stk.pop_back();
        }
        st[t].push_back(i);
        while (top(stk) >= 1 &&
               calc(i, stk[top(stk)]) <= calc(i, stk[top(stk) - 1])) {
            stk.pop_back();
        }
        dp[i] = calc(i, stk[top(stk)]);
    }
    cout << dp[n] << endl;
    return 0;
}
// Asusetic eru quionours