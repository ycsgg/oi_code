#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N   = 35005;
const int INF = 0x3f3f3f3f;
int n, k;
array<int, N> a, pre, last, nxt;
array<array<int, 2>, N> dp;
int now;
int pl = 1, pr = 0, sum = 0;
int calc(int l, int r) {
    while (pl < l) {
        if (nxt[pl] <= pr) {
            sum -= nxt[pl] - pl;
        }
        ++pl;
    }
    while (pl > l) {
        --pl;
        if (nxt[pl] <= pr) {
            sum += nxt[pl] - pl;
        }
    }
    while (pr < r) {
        ++pr;
        if (pre[pr] >= pl) {
            sum += pr - pre[pr];
        }
    }
    while (pr > r) {
        if (pre[pr] >= pl) {
            sum -= pr - pre[pr];
        }
        --pr;
    }
    return sum;
}
void solve(int l, int r, int x, int y) {
    if (l > r || x > y) {
        return;
    }
    int mid = (l + r) / 2;
    int val = INF, pos;
    for (int i = x; i < mid && i <= y; i++) {
        int tmp = dp[i][now ^ 1] + calc(i + 1, mid);
        if (tmp < val) {
            pos = i;
            val = tmp;
        }
    }
    dp[mid][now] = val;
    solve(l, mid - 1, x, pos);
    solve(mid + 1, r, pos, y);
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i]     = last[a[i]];
        last[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        last[a[i]] = n + 1;
    }
    for (int i = n; ~i; i--) {
        nxt[i]     = last[a[i]];
        last[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][now] = INF;
    }
    while (k--) {
        now ^= 1;
        solve(1, n, 0, n);
    }
    cout << dp[n][now] << endl;
    return 0;
}
// Asusetic eru quionours