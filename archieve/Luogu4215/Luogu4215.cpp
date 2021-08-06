#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
int w[N], num[N];
int ans = 0;
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int val;
    vector<int> id;
};
array<Node, N * 4> tr;
void build(int rt, int l, int r) {
    if (l == r) {
        tr[rt].val = w[l];
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    tr[rt].val = tr[ls(rt)].val + tr[rs(rt)].val;
}
void update(int rt, int l, int r, int pos) {
    if (l == r) {
        tr[rt].val--;
        if (!tr[rt].val) {
            for (auto i : tr[rt].id) {
                num[i]--;
                if (!num[i]) {
                    ans++;
                }
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(ls(rt), l, mid, pos);
    } else {
        update(rs(rt), mid + 1, r, pos);
    }
    tr[rt].val = tr[ls(rt)].val + tr[rs(rt)].val;
    if (!tr[rt].val) {
        for (auto i : tr[rt].id) {
            num[i]--;
            if (!num[i]) {
                ans++;
            }
        }
    }
}
void nya(int rt, int l, int r, int L, int R, int id) {
    if (L <= l && r <= R) {
        tr[rt].id.push_back(id);
        num[id]++;
        return;
    }
    int mid = (l + r) / 2;
    if (L <= mid) {
        nya(ls(rt), l, mid, L, R, id);
    }
    if (mid < R) {
        nya(rs(rt), mid + 1, r, L, R, id);
    }
}
#undef ls
#undef rs
} // namespace SegmentTree
int n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    SegmentTree::build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        SegmentTree::nya(1, 1, n, l, r, i);
    }
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        x = (x + ans - 1) % n + 1;
        SegmentTree::update(1, 1, n, x);
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours