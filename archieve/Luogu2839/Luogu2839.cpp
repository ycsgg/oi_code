#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
const int N = 20005;
int lastans;
int n, m;
auto getQuery(int a, int b, int c, int d) {
    array q = {a, b, c, d};
    for_each(q.begin(), q.end(), [](auto &x) -> void {
        x = (x + lastans) % n + 1;
    });
    sort(q.begin(), q.end());
    return tuple(q[0], q[1], q[2], q[3]);
}
namespace SegmentTree {
struct Data {
    int sum, lx, rx;
    auto operator+(const Data &B) const {
        return Data{sum + B.sum, max(lx, B.lx + sum), max(B.rx, B.sum + rx)};
    }
    void operator()(const int &_s, const int &_l, const int &_r) {
        sum = _s;
        lx  = _l;
        rx  = _r;
    }
};

struct Node {
    int ls, rs;
    Data val;
    int l, r;
};
array<Node, N * 40> tr;
int tot;
#define ls(x) (tr[x].ls)
#define rs(x) (tr[x].rs)
void pushup(int x) {
    tr[x].val = tr[ls(x)].val + tr[rs(x)].val;
}
void build(int &rt, int l, int r) {
    rt       = ++tot;
    tr[rt].l = l;
    tr[rt].r = r;
    if (l == r) {
        tr[rt].val(1, 1, 1);
        return;
    }
    int mid = (l + r) / 2;
    build(tr[rt].ls, l, mid);
    build(tr[rt].rs, mid + 1, r);
    pushup(rt);
}
void insert(int &rt, int pre, int l, int r, int pos, int v) {
    rt     = ++tot;
    tr[rt] = tr[pre];
    if (l == r) {
        tr[rt].val(v, v, v);
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(tr[rt].ls, tr[pre].ls, l, mid, pos, v);
    } else {
        insert(tr[rt].rs, tr[pre].rs, mid + 1, r, pos, v);
    }
    pushup(rt);
}
auto query(int rt, int L, int R) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (l >= L && r <= R) {
        return tr[rt].val;
    }
    int mid = (l + r) / 2;
    if (R <= mid) {
        return query(ls(rt), L, R);
    } else if (mid < L) {
        return query(rs(rt), L, R);
    } else {
        return query(ls(rt), L, mid) + query(rs(rt), mid + 1, R);
    }
}
#undef ls
#undef rs
} // namespace SegmentTree
array<int, N> root;
bool check(int id, int a, int b, int c, int d) {
    int res = 0;
    if (c - 1 >= b + 1) {
        res += SegmentTree::query(root[id], b + 1, c - 1).sum;
    }
    res += SegmentTree::query(root[id], a, b).rx;
    res += SegmentTree::query(root[id], c, d).lx;
    return (res >= 0);
}
struct Data {
    int num, id;
};
int main() {
    cin >> n;
    vector<Data> qb(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> qb[i].num;
        qb[i].id = i;
    }
    sort(qb.begin() + 1, qb.end(), [&](const Data &A, const Data &B) -> bool {
        return A.num < B.num;
    });
    SegmentTree::build(root[1], 1, n);
    for (int i = 2; i <= n; i++) {
        SegmentTree::insert(root[i], root[i - 1], 1, n, qb[i - 1].id, -1);
    }
    cin >> m;
    while (m--) {
        int _a, _b, _c, _d;
        cin >> _a >> _b >> _c >> _d;
        auto [a, b, c, d] = getQuery(_a, _b, _c, _d);
        int l = 1, r = n, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid, a, b, c, d)) {
                ans = mid;
                l   = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        lastans = qb[ans].num;
        cout << qb[ans].num << endl;
    }
    return 0;
}
// Asusetic eru quionours