### P5244 [USACO19FEB] Mowing Mischief P

先对$x$排序然后对$y$求 LIS

之后考虑对于点$i$的LIS是$l_i$  枚举所有左下角的点LIS长度为$l_i-1$，可以得到

$f_i=\min\limits_{l_i=l_j+1,j<i,y_j<y_i} f_j+(x_i-x_j)(y_i-y_j)$

$f_i=\min\limits_{l_i=l_j+1,j<i,y_j<y_i} f_j+x_iy_i-x_iy_j-x_jy_i+x_jy_j$

$f_j+x_iy_i-x_iy_j-x_jy_i+x_jy_j \le f_k+x_iy_i-x_iy_k-x_ky_i+x_ky_k$

$(y_k-y_j)x_i+(x_k-x_j)y_i\le f_k-f_j+x_ky_k-x_jy_j$

显然$y_k-y_j$和$x_k-x_j$必然一正一负

如果钦定$j<k$那么，$j$优于$k$的情况是一个半平面，且平面边界斜率必为正

也就是如果$i$时$j$优于$k$那么大于$i$的$j$也优于$k$

所以对于$l$相同的转移，最优决策是单调不增的

而对于$x_j\le x_i,y_j \le y_i$的限制，能从上一个$l$转移来的都是一段连续的区间，放到线段树处理

对于一个询问直接挂到对应节点

线段树上的一个节点$[l,r]$代表能从上一层$[l,r]$转移

区间询问区间选择答案，可以线段树上分治

```cpp
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
```