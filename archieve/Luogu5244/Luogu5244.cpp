#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 200015;
int n, T;
const long long INF = 2e18;
typedef long long ll;
int mmax = -1;
vector<ll> pos[N];
ll dp[N];
struct Node {
    int x, y, l;
} p[N];
bool operator<(const Node &a, const Node &b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}
namespace BIT {
int c[N * 5];
int lowbit(int x) {
    return x & (-x);
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res = max(res, c[pos]);
        pos -= lowbit(pos);
    }
    return res;
}
void update(int pos, int v) {
    while (pos <= T) {
        c[pos] = max(c[pos], v);
        pos += lowbit(pos);
    }
}
} // namespace BIT
namespace SegmentTree {
typedef long long ll;
struct Node {
    int ls, rs;
    vector<ll> trans;
} a[N * 2];
vector<ll> poll, tmp;
int rt, cnt;
void build(int &rt, int l, int r) {
    rt       = ++cnt;
    a[rt].ls = a[rt].rs = 0;
    a[rt].trans.clear();
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(a[rt].ls, l, mid);
    build(a[rt].rs, mid + 1, r);
}
void init(vector<ll> t) {
    poll = t;
    n    = t.size();
    rt = cnt = 0;
    build(rt, 0, n - 1);
}
void update(int rt, int l, int r, int x) {
    if (p[x].x >= p[poll[r]].x && p[x].y >= p[poll[l]].y) {
        a[rt].trans.push_back(x);
        return;
    }
    if (p[x].x <= p[poll[l]].x || p[x].y <= p[poll[r]].y) {
        return;
    }
    int mid = (l + r) / 2;
    update(a[rt].ls, l, mid, x);
    update(a[rt].rs, mid + 1, r, x);
}
inline void solve(ll l, ll r, ll L, ll R) {
    ll ans = INF, from = 0;
    int mid = (l + r) / 2, now = tmp[mid];
    for (ll i = L; i <= R; ++i) {
        ll pos = poll[i];
        ll res = dp[pos] + 1ll * (p[now].x - p[pos].x) * (p[now].y - p[pos].y);
        if (res < ans) {
            ans  = res;
            from = i;
        }
    }
    dp[now] = min(dp[now], ans);
    if (l < mid)
        solve(l, mid - 1, from, R);
    if (mid < r)
        solve(mid + 1, r, L, from);
}
void update(int x) {
    update(rt, 0, n - 1, x);
}
void solve(int rt, int l, int r) {
    if (a[rt].trans.size()) {
        tmp = a[rt].trans;
        solve(0, tmp.size() - 1, l, r);
    }
    if (l == r)
        return;
    int mid = (l + r) / 2;
    solve(a[rt].ls, l, mid);
    solve(a[rt].rs, mid + 1, r);
}
void solve() {
    solve(rt, 0, n - 1);
}
} // namespace SegmentTree

int main() {
    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++) {
        p[i].l = BIT::query(p[i].y) + 1;
        BIT::update(p[i].y, p[i].l);
        pos[p[i].l].push_back(i);
        mmax = max(mmax, p[i].l);
    }
    for (auto d : pos[1]) {
        dp[d] = 1ll * p[d].x * p[d].y;
    }
    for (int i = 2; i <= mmax; i++) {
        SegmentTree::init(pos[i - 1]);
        for (auto d : pos[i]) {
            dp[d] = INF;
            SegmentTree::update(d);
        }
        SegmentTree::solve();
    }
    ll ans = INF;
    for (auto d : pos[mmax]) {
        ans = min(ans, dp[d] + 1ll * (T - p[d].x) * (T - p[d].y));
    }
    cout << ans;
    return 0;
}