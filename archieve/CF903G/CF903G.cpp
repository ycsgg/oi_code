#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
using ll    = long long;
namespace SegmentTree {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
struct Node {
    ll v, tag;
    int l, r;
};
array<Node, N << 2> tr;
void pushup(int x) {
    tr[x].v = min(tr[ls(x)].v, tr[rs(x)].v);
}
void pushdown(int x) {
    if (tr[x].tag) {
        tr[ls(x)].tag += tr[x].tag;
        tr[rs(x)].tag += tr[x].tag;
        tr[ls(x)].v += tr[x].tag;
        tr[rs(x)].v += tr[x].tag;
        tr[x].tag = 0;
    }
}
void build(int x, int l, int r, const array<ll, N> &v) {
    tr[x].l   = l;
    tr[x].r   = r;
    tr[x].tag = tr[x].v = 0;
    if (l == r) {
        tr[x].v = v[l];
        return;
    }
    int mid = (l + r) / 2;
    build(ls(x), l, mid, v);
    build(rs(x), mid + 1, r, v);
    pushup(x);
}
void update(int x, int L, int R, ll v) {
    int &l = tr[x].l;
    int &r = tr[x].r;
    if (l >= L && r <= R) {
        tr[x].tag += v;
        tr[x].v += v;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x);
    if (L <= mid) {
        update(ls(x), L, R, v);
    }
    if (mid < R) {
        update(rs(x), L, R, v);
    }
    pushup(x);
}
void update(int pos, ll v) {
    update(1, pos, pos, v);
}
} // namespace SegmentTree
int n, m, q;
array<ll, N> a, b;
struct Graph {
    struct Node {
        int v;
        ll w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
void build() {
    array<ll, N> tmp;
    SegmentTree::build(1, 1, n, b);
    for (int i = 1; i <= n; i++) {
        for (auto e : G.edge[i]) {
            SegmentTree::update(1, 1, e.v, e.w);
        }
        tmp[i] = SegmentTree::tr[1].v;
        tmp[i] += a[i];
    }
    SegmentTree::build(1, 1, n, tmp);
}
int main() {
    cin >> n >> m >> q;
    for (int i = 2; i <= n; i++) {
        cin >> a[i - 1] >> b[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add(u, v, w);
    }
    build();
    cout << SegmentTree::tr[1].v << endl;
    while (q--) {
        int x, v;
        cin >> x >> v;
        SegmentTree::update(x, v - a[x]);
        a[x] = v;
        cout << SegmentTree::tr[1].v << endl;
    }
    return 0;
}
// Asusetic eru quionours.