#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 200005;
vector<int> pos[N];
int b[N], sum[N];
int n, m;
namespace SegmentTree {
int val[N * 4], tag[N * 4];
void update(int x, int l, int r, int pos, int v) {
    if (l == r) {
        val[x] = min(val[x], v);
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(x * 2, l, mid, pos, v);
    } else {
        update(x * 2 + 1, mid + 1, r, pos, v);
    }
    val[x] = min(val[x * 2], val[x * 2 + 1]);
}
int query(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return val[x];
    }
    int mid = (l + r) / 2;
    int res = 1e9 + 7;
    if (L <= mid) {
        res = min(res, query(x * 2, l, mid, L, R));
    }
    if (R > mid) {
        res = min(res, query(x * 2 + 1, mid + 1, r, L, R));
    }
    return res;
}

void build(int x, int l, int r) {
    val[x] = 1e9;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}
} // namespace SegmentTree
int dp[N];
using namespace SegmentTree;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        sum[i] = sum[i - 1] + (b[i] == 0);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        pos[l].push_back(r);
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        for (auto r : pos[i]) {
            int p = dp[i - 1];
            p     = min(p, query(1, 1, n, i - 1, r));
            if (p < dp[r]) {
                dp[r] = p;
                update(1, 1, n, r, dp[r]);
            }
        }
        dp[i] = min(dp[i], dp[i - 1] + 2 * b[i] - 1);
    }
    cout << dp[n] + sum[n];
    return 0;
}
// Asusetic eru quionours