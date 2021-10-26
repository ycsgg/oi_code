#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
int n, m;
struct Line {
    int l, r, w;
};
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int l, r;
    int val, tag;
} tr[N * 4];
void build(int x, int l, int r) {
    tr[x].l = l;
    tr[x].r = r;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
}
void pushup(int x) {
    tr[x].val = min(tr[ls(x)].val, tr[rs(x)].val);
}
void pushdown(int x) {
    if (tr[x].tag) {
        tr[ls(x)].val += tr[x].tag;
        tr[rs(x)].val += tr[x].tag;
        tr[ls(x)].tag += tr[x].tag;
        tr[rs(x)].tag += tr[x].tag;
        tr[x].tag = 0;
    }
}
void update(int x, int L, int R, int v) {
    auto l = tr[x].l;
    auto r = tr[x].r;
    if (L <= l && r <= R) {
        tr[x].val += v;
        tr[x].tag += v;
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
#undef ls
#undef rs
} // namespace SegmentTree
int main() {
    cin >> n >> m;
    vector<Line> a(n);
    for (auto &v : a) {
        cin >> v.l >> v.r >> v.w;
        v.r = v.r - 1;
    }

    SegmentTree::build(1, 1, m - 1);

    sort(a.begin(), a.end(), [&](const auto &A, const auto &B) -> bool {
        return A.w < B.w;
    });

    auto l = a.begin();
    auto r = l;
    SegmentTree::update(1, r->l, r->r, 1);
    int res = 0x3f3f3f3f;
    while (1) {
        while (!SegmentTree::tr[1].val) {
            r++;
            if (r == a.end()) {
                cout << res << '\n';
                return 0;
            }
            SegmentTree::update(1, r->l, r->r, 1);
        }
        res = min(res, r->w - l->w);
        SegmentTree::update(1, l->l, l->r, -1);
        l++;
    }
    return 0;
}
// Asusetic eru quionours.