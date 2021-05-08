#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int n, k;
ll a[N];
ll dp[N][2];
int now;
int ql = 1, qr;
ll res, _cnt[N];
void add(int x) {
    res += _cnt[x];
    ++_cnt[x];
}
void del(int x) {
    --_cnt[x];
    res -= _cnt[x];
}
ll cnt(int l, int r) {
    while (ql > l) {
        add(a[--ql]);
    }
    while (ql < l) {
        del(a[ql++]);
    }
    while (qr > r) {
        del(a[qr--]);
    }
    while (qr < r) {
        add(a[++qr]);
    }
    return res;
}
void solve(int l, int r, int L, int R) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    int cur = L;
    for (int i = min(mid, R); i >= L; i--) {
        ll tmp = dp[i - 1][now ^ 1] + cnt(i, mid);
        if (dp[mid][now] >= tmp) {
            dp[mid][now] = tmp;
            cur          = i;
        }
    }
    solve(l, mid - 1, L, cur);
    solve(mid + 1, r, cur, R);
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(dp, 0x7f, sizeof(dp));
    dp[0][0] = 0;
    now      = 1;
    while (k--) {
        solve(1, n, 1, n);
        now ^= 1;
    }
    cout << dp[n][now ^ 1];
    return 0;
}
// Asusetic eru quionours