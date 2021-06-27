#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
namespace SegmentTree {
struct Node {
    int ls, rs, v;
};
array<Node, N * 404> tr;
array<int, N * 20> root;
int tot;
void update(int &rt, int l, int r, int pos, int v) {
    if (!rt) {
        rt = ++tot;
    }
    tr[rt].v += v;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(tr[rt].ls, l, mid, pos, v);
    } else {
        update(tr[rt].rs, mid + 1, r, pos, v);
    }
}
int query(int l, int r, int k, vector<int> &q1, vector<int> &q2) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    int sum = 0;
    for (auto p : q1) {
        sum -= tr[tr[p].ls].v;
    }
    for (auto p : q2) {
        sum += tr[tr[p].ls].v;
    }
    if (k <= sum) {
        for (auto &x : q1) {
            x = tr[x].ls;
        }
        for (auto &x : q2) {
            x = tr[x].ls;
        }
        return query(l, mid, k, q1, q2);
    } else {
        for (auto &x : q1) {
            x = tr[x].rs;
        }
        for (auto &x : q2) {
            x = tr[x].rs;
        }
        return query(mid + 1, r, k - sum, q1, q2);
    }
}
}; // namespace SegmentTree
struct Oper {
    int typ;
    int l, r, k;
};
int n, m;
array<int, N> a;
array<Oper, N> q;
int b[N * 2];
int tot, cnt;
namespace BIT {
using namespace SegmentTree;
int lowbit(int x) {
    return x & (-x);
}
void update(int x, int v) {
    int pos = lower_bound(b + 1, b + 1 + cnt, a[x]) - b;
    while (x <= n) {
        SegmentTree::update(root[x], 1, cnt, pos, v);
        x += lowbit(x);
    }
}
int query(int l, int r, int k) {
    vector<int> q1, q2;
    while (r) {
        q2.emplace_back(root[r]);
        r -= lowbit(r);
    }
    l--;
    while (l) {
        q1.emplace_back(root[l]);
        l -= lowbit(l);
    }
    return SegmentTree::query(1, cnt, k, q1, q2);
}
} // namespace BIT
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[++tot] = a[i];
    }
    for (int i = 1; i <= m; i++) {
        char opt;
        cin >> opt;
        if (opt == 'Q') {
            cin >> q[i].l >> q[i].r >> q[i].k;
            q[i].typ = 1;
        } else {
            cin >> q[i].l >> q[i].k;
            b[++tot] = q[i].k;
        }
    }
    sort(b + 1, b + 1 + tot);
    cnt = unique(b + 1, b + 1 + tot) - b - 1;
    for (int i = 1; i <= n; i++) {
        BIT::update(i, 1);
    }
    for (int i = 1; i <= m; i++) {
        if (q[i].typ == 1) {
            cout << b[BIT::query(q[i].l, q[i].r, q[i].k)] << endl;
        } else {
            BIT::update(q[i].l, -1);
            a[q[i].l] = q[i].k;
            BIT::update(q[i].l, 1);
        }
    }
    return 0;
}
// Asusetic eru quionours