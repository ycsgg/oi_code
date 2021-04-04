### [IOI2008] Pyramid Base 金字塔基

~~考点分类讨论~~

大力分类讨论

#### $B=0$

此时就是找最大无障碍**正方形**（一开始找的矩形十分迷惑orz）

双指针扫描线，对于确定的$i$另一个指针$j$，我们仅需选出以$i,j$为边的最大的矩形，$i-j$减小时，另一方向长度不减

所以只需扫出竖向的长度大于等于横向的长度即可

可以用线段树维护区间加减最长字段

#### $B\neq0$

数据小，二分边长$l$，对于一个障碍会对它左上$l$的位置产生影响

于是现在就是最小矩形覆盖的问题，线段树解决

```cpp
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
int n, m, b, p;
namespace Subtask1 {
vector<pair<int, int>> st[N], ed[N];
namespace SegmentTree {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
struct Node {
    int lmax, rmax, mmax, tag, len;
} tr[N * 4];
void pushup(int x) {
    if (tr[x].tag) {
        tr[x].lmax = tr[x].rmax = tr[x].mmax = 0;
        return;
    }
    if (tr[x].len == 1) {
        tr[x].lmax = tr[x].rmax = tr[x].mmax = 1;
        return;
    }
    if (tr[ls(x)].lmax == tr[ls(x)].len) {
        tr[x].lmax = tr[ls(x)].lmax + tr[rs(x)].lmax;
    } else {
        tr[x].lmax = tr[ls(x)].lmax;
    }
    if (tr[rs(x)].rmax == tr[rs(x)].len) {
        tr[x].rmax = tr[rs(x)].rmax + tr[ls(x)].rmax;
    } else {
        tr[x].rmax = tr[rs(x)].rmax;
    }
    tr[x].mmax = max(tr[ls(x)].rmax + tr[rs(x)].lmax,
                     max(tr[ls(x)].mmax, tr[rs(x)].mmax));
}
void build(int rt, int l, int r) {
    tr[rt].lmax = tr[rt].rmax = tr[rt].len = tr[rt].mmax = r - l + 1;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
void update(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) {
        tr[rt].tag += v;
        pushup(rt);
        return;
    }
    int mid = (l + r) / 2;
    if (mid >= L) {
        update(ls(rt), l, mid, L, R, v);
    }
    if (mid < R) {
        update(rs(rt), mid + 1, r, L, R, v);
    }
    pushup(rt);
}
#undef ls
#undef rs
} // namespace SegmentTree
void solve() {
    for (int i = 1; i <= p; i++) {
        int x1, y1, x2, y2, tmp;
        cin >> x1 >> y1 >> x2 >> y2 >> tmp;
        st[x1].push_back(make_pair(y1, y2));
        ed[x2].push_back(make_pair(y1, y2));
    }
    SegmentTree::build(1, 1, m);
    int ans = 0;
    int j   = 0;
    for (int i = 1; i <= n; i++) {
        while (SegmentTree::tr[1].mmax >= j - i + 1 && j <= n) {
            j++;
            for (auto d : st[j]) {
                SegmentTree::update(1, 1, m, d.first, d.second, 1);
            }
        }
        for (auto d : ed[i]) {
            SegmentTree::update(1, 1, m, d.first, d.second, -1);
        }
        ans = max(ans, j - i);
    }
    cout << ans << endl;
}
#undef ls
#undef rs
} // namespace Subtask1

namespace Subtask2 {
typedef long long ll;
namespace SegmentTree {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
struct Node {
    ll val, tag;
} tr[N * 4];
void pushdown(int x) {
    if (tr[x].tag) {
        tr[ls(x)].tag += tr[x].tag;
        tr[ls(x)].val += tr[x].tag;
        tr[rs(x)].tag += tr[x].tag;
        tr[rs(x)].val += tr[x].tag;
        tr[x].tag = 0;
    }
}
void clear() {
    memset(tr, 0, sizeof(tr));
}
void pushup(int x) {
    tr[x].val = min(tr[ls(x)].val, tr[rs(x)].val);
}
void update(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) {
        tr[rt].tag += v;
        tr[rt].val += v;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (mid >= L) {
        update(ls(rt), l, mid, L, R, v);
    }
    if (mid < R) {
        update(rs(rt), mid + 1, r, L, R, v);
    }
    pushup(rt);
}
} // namespace SegmentTree
struct Rectangle {
    int x1, y1, x2, y2;
    ll c;
} a[N];
struct Data {
    int l, r;
    ll c;
};
vector<Data> st[N], ed[N];
bool check(int len) {
    for (int i = 1; i <= n - len + 1; i++) {
        st[i].clear();
        ed[i].clear();
    }
    SegmentTree::clear();
    for (int i = 1; i <= p; i++) {
        int x1 = a[i].x1 - len + 1, y1 = a[i].y1 - len + 1, x2 = a[i].x2,
            y2 = a[i].y2;
        x1     = max(x1, 1);
        y1     = max(y1, 1);
        x2     = min(x2, n - len + 1);
        y2     = min(y2, m - len + 1);
        if (x1 > x2 || y1 > y2)
            continue;
        st[x1].push_back((Data){y1, y2, a[i].c});
        ed[x2].push_back((Data){y1, y2, -a[i].c});
    }
    for (int i = 1; i <= n - len + 1; i++) {
        for (auto d : st[i]) {
            SegmentTree::update(1, 1, m - len + 1, d.l, d.r, d.c);
        }
        if (SegmentTree::tr[1].val <= b) {
            return true;
        }
        for (auto d : ed[i]) {
            SegmentTree::update(1, 1, m - len + 1, d.l, d.r, d.c);
        }
    }
    return false;
}
void solve() {
    for (int i = 1; i <= p; i++) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2 >> a[i].c;
    }
    int l = 1, r = min(n, m), ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l   = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
}
} // namespace Subtask2

int main() {
    cin >> n >> m;
    cin >> b >> p;
    if (b == 0) {
        Subtask1::solve();
        return 0;
    } else {
        Subtask2::solve();
        return 0;
    }
    return 0;
}
```

