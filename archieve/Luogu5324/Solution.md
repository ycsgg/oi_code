### P5324 [BJOI2019]删数

显然与顺序无关，那就是对一个多重集进行的操作

考虑如果那这个东西扔进桶里，那么每次删除的时候就是把这个桶"推倒"，然后继续删这个桶倒下的位置的桶(有点抽象)

就是说如果 $n$ 有 $c_n$ 个，那么删完 $n$ 就要删 $n-c_n$ 的数字，如果没这个数字就需要用与上一个数字间隔的空位的操作去补上

也就是如果我们把 $x$ “平铺” 到 $[x-c_x+1,x]$ 的位置，让这些位置都是 $1$

那么我们就是要数 $0$ 的个数（画图理解）

那么用线段树维护数轴就相当于单点加减和移动零点啦，只需要查是 $0$ 的个数即可

```cpp
#include <array>
#include <iostream>
using namespace std;
const int N = 5e5 + 10;
namespace SegmentTree {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
struct Node {
    int mmin, cnt, tag;
    int l, r;
};
array<Node, N * 4> tr;
void pushup(int x) {
    if (tr[ls(x)].mmin == tr[rs(x)].mmin) {
        tr[x].mmin = tr[ls(x)].mmin;
        tr[x].cnt  = tr[ls(x)].cnt + tr[rs(x)].cnt;
    }
    if (tr[ls(x)].mmin < tr[rs(x)].mmin) {
        tr[x].mmin = tr[ls(x)].mmin;
        tr[x].cnt  = tr[ls(x)].cnt;
    }
    if (tr[ls(x)].mmin > tr[rs(x)].mmin) {
        tr[x].mmin = tr[rs(x)].mmin;
        tr[x].cnt  = tr[rs(x)].cnt;
    }
}
void pushdown(int x) {
    if (tr[x].tag) {
        tr[ls(x)].tag += tr[x].tag;
        tr[rs(x)].tag += tr[x].tag;
        tr[ls(x)].mmin += tr[x].tag;
        tr[rs(x)].mmin += tr[x].tag;
        tr[x].tag = 0;
    }
}
void build(int x, int l, int r) {
    tr[x].l = l;
    tr[x].r = r;
    if (l == r) {
        tr[x].cnt = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
    pushup(x);
}
void update(int x, int L, int R, int v) {
    auto &l = tr[x].l;
    auto &r = tr[x].r;
    if (l >= L && r <= R) {
        tr[x].tag += v;
        tr[x].mmin += v;
        return;
    }
    pushdown(x);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(x), L, R, v);
    }
    if (mid < R) {
        update(rs(x), L, R, v);
    }
    pushup(x);
}
void update(int pos, int v) {
    update(1, pos, pos, v);
}
int query(int x, int L, int R) {
    auto &l = tr[x].l;
    auto &r = tr[x].r;
    if (l >= L && r <= R) {
        return tr[x].mmin == 0 ? tr[x].cnt : 0;
    }
    pushdown(x);
    int mid = (l + r) / 2;
    int res = 0;
    if (L <= mid) {
        res += query(ls(x), L, R);
    }
    if (mid < R) {
        res += query(rs(x), L, R);
    }
    return res;
}
#undef ls
#undef rs
} // namespace SegmentTree
int ZERO = 150005;
int n, m;
array<int, N> a, cnt;
void add(int x) {
    if (x <= ZERO + n) {
        SegmentTree::update(x - cnt[x], 1);
    }
    cnt[x]++;
}
void del(int x) {
    cnt[x]--;
    if (x <= ZERO + n) {
        SegmentTree::update(x - cnt[x], -1);
    }
}
void addp(int x) {
    SegmentTree::update(1, x - cnt[x] + 1, x, 1);
}
void delp(int x) {
    SegmentTree::update(1, x - cnt[x] + 1, x, -1);
}
int main() {
    cin >> n >> m;
    SegmentTree::build(1, 1, N);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += ZERO;
        add(a[i]);
    }
    while (m--) {
        int pos, x;
        cin >> pos >> x;
        if (pos >= 1) {
            x += ZERO;
            del(a[pos]);
            add(x);
            a[pos] = x;
        } else {
            if (~x) {
                delp(ZERO + n);
                ZERO--;
            } else {
                ZERO++;
                addp(ZERO + n);
            }
        }
        cout << SegmentTree::query(1, ZERO + 1, ZERO + n) << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

#线段树
#思维