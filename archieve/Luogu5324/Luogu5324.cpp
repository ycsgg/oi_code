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
