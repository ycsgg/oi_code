#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
const int N       = 3e5 + 5;
const int INF     = 0x3f3f3f3f;
const int NINF    = -0x3f3f3f3f;
const int CONNECT = 114514;
using namespace std;
int nxt[N], tail[N], a[N], pos[N], id[N], fa[N], siz[N], cnt, n, m;
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
struct Oper {
    int typ;
    int x, v;
} q[N];
namespace SegmentTree {
int mmax[N << 2], tag[N << 2];
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
void pushup(int x) {
    mmax[x] = max(mmax[ls(x)], mmax[rs(x)]);
}
void pushdown(int x) {
    if (!tag[x])
        return;
    mmax[ls(x)] += tag[x];
    tag[ls(x)] += tag[x];
    mmax[rs(x)] += tag[x];
    tag[rs(x)] += tag[x];
    tag[x] = 0;
}
void build(int rt, int l, int r) {
    if (l == r) {
        mmax[rt] = a[pos[l]];
        fa[l]    = l;
        siz[l]   = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
void update(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && R >= r) {
        mmax[rt] += v;
        tag[rt] += v;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid)
        update(ls(rt), l, mid, L, R, v);
    if (R > mid)
        update(rs(rt), mid + 1, r, L, R, v);
    pushup(rt);
}
int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return mmax[rt];
    }
    pushdown(rt);
    int mid = (l + r) / 2, ans = -INF;
    if (L <= mid) {
        ans = query(ls(rt), l, mid, L, R);
    }
    if (R > mid) {
        ans = max(ans, query(rs(rt), mid + 1, r, L, R));
    }
    return ans;
}
#undef ls
#undef rs
} // namespace SegmentTree
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        tail[i] = fa[i] = i;
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        char opt[5];
        scanf("%s", opt);
        if (opt[0] == 'A') {
            q[i].typ = -opt[1] + '0';
            if (opt[1] < '3') {
                cin >> q[i].x;
            }
            cin >> q[i].v;
        } else if (opt[0] == 'F') {
            q[i].typ = opt[1] - '0';
            if (opt[1] < '3') {
                cin >> q[i].x;
            }
        } else {
            q[i].typ = CONNECT;
            int x, y, u, v;
            cin >> x >> y;
            u      = find(x);
            v      = find(y);
            q[i].x = x, q[i].v = y;
            if (u == v) {
                continue;
            }
            nxt[tail[u]] = v;
            tail[u]      = tail[v];
            fa[v]        = u;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (fa[i] == i) {
            for (int j = i; j; j = nxt[j]) {
                id[j]    = ++cnt;
                pos[cnt] = j;
            }
        }
    }
    SegmentTree::build(1, 1, cnt);
    for (int i = 1; i <= m; ++i) {
        int typ = q[i].typ;
        if (typ == CONNECT) {
            int u = find(q[i].x), v = find(q[i].v);
            if (u == v)
                continue;
            siz[u] += siz[v];
            fa[v] = u;
        } else if (typ < 0) {
            if (typ == -1) {
                SegmentTree::update(1, 1, cnt, id[q[i].x], id[q[i].x], q[i].v);
            } else if (typ == -2) {
                int u = find(q[i].x);
                SegmentTree::update(1, 1, cnt, id[u], id[u] + siz[u] - 1,
                                    q[i].v);
            } else {
                SegmentTree::update(1, 1, cnt, 1, cnt, q[i].v);
            }
        } else {
            if (typ == 1) {
                printf("%d\n",
                       SegmentTree::query(1, 1, cnt, id[q[i].x], id[q[i].x]));
            } else if (typ == 2) {
                int u = find(q[i].x);
                printf("%d\n", SegmentTree::query(1, 1, cnt, id[u],
                                                  id[u] + siz[u] - 1));
            } else {
                printf("%d\n", SegmentTree::mmax[1]);
            }
        }
    }
}