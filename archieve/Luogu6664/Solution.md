### P6664 [清华集训2016] 温暖会指引我们前行

其实就是动态维护最大生成树

用LCT维护边的最小值和长度，所以可以考虑给边新建一个节点来记录信息

这样删加都很方便

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int N   = 300005;
const int INF = 0x3f3f3f3f;
array<int, N> len, pos, val;
namespace LCT {
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
array<int, N> fa, minval, minid, tag, sum;
array<array<int, 2>, N> ch;
void pushup(int x) {
    sum[x]  = sum[ls(x)] + sum[rs(x)] + len[x];
    int tmp = val[x];
    int id  = pos[x];
    if (ls(x) && tmp > minval[ls(x)]) {
        tmp = minval[ls(x)];
        id  = minid[ls(x)];
    }
    if (rs(x) && tmp > minval[rs(x)]) {
        tmp = minval[rs(x)];
        id  = minid[rs(x)];
    }
    minval[x] = tmp;
    minid[x]  = id;
}
void pushdown(int x) {
    if (!tag[x])
        return;
    if (ls(x))
        tag[ls(x)] ^= 1;
    if (rs(x))
        tag[rs(x)] ^= 1;
    tag[x] = 0;
    swap(ls(x), rs(x));
}

bool isroot(int x) {
    return ls(fa[x]) != x && rs(fa[x]) != x;
}
bool identity(int x) {
    return x == ch[fa[x]][1];
}
void rotate(int x) {
    int y = fa[x], z = fa[y];
    int k = identity(x);
    if (!isroot(y)) {
        ch[z][identity(y)] = x;
    }
    fa[x]            = z;
    ch[y][k]         = ch[x][k ^ 1];
    fa[ch[x][k ^ 1]] = y;
    ch[x][k ^ 1]     = y;
    fa[y]            = x;
    pushup(y);
    pushup(x);
}
void splay(int x) {
    vector<int> st;
    int tmp = x;
    while (!isroot(tmp)) {
        st.push_back(tmp);
        tmp = fa[tmp];
    }
    st.push_back(tmp);
    ranges::reverse(st);
    ranges::for_each(st, [&](auto p) -> void {
        pushdown(p);
    });
    while (!isroot(x)) {
        int y = fa[x];
        if (!isroot(y)) {
            rotate(identity(x) ^ identity(y) ? x : y);
        }
        rotate(x);
    }
    pushup(x);
}
void access(int x) {
    int y = 0;
    while (x) {
        splay(x);
        rs(x) = y;
        pushup(x);
        y = x;
        x = fa[x];
    }
}
void makeroot(int x) {
    access(x);
    splay(x);
    tag[x] ^= 1;
}
int findroot(int x) {
    access(x);
    splay(x);
    while (ls(x)) {
        x = ls(x);
    }
    return x;
}
void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        fa[x] = y;
    }
}
void cut(int x, int y) {
    split(x, y);
    if (ls(y) == x && !rs(x)) {
        fa[x] = ls(y) = 0;
    }
}
#undef ls
#undef rs
} // namespace LCT
namespace DSU {
array<int, N> fa, siz;
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (siz[x] > siz[y]) {
        swap(x, y);
    }
    fa[x] = y;
    siz[y] += siz[x];
}
} // namespace DSU
int n, m;
struct Edge {
    int u, v;
};
array<bool, N> vis;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        DSU::fa[i]  = i;
        DSU::siz[i] = 1;
        val[i] = LCT::minval[i] = INF;
    }
    vector<Edge> e(m + 1);
    for (int i = 1; i <= m; i++) {
        char opt[8];
        cin >> opt;
        if (opt[0] == 'f') {
            int id, u, v, t, l;
            cin >> id >> u >> v >> t >> l;
            ++id;
            ++u;
            ++v;
            e[id]       = Edge{u, v};
            len[id + n] = l;
            val[id + n] = t;
            pos[id + n] = id;
            // printf("%d %d %d %d %d\n", id, DSU::find(u), DSU::find(v), t, l);
            if (DSU::find(u) == DSU::find(v)) {
                LCT::split(u, v);
                if (t <= LCT::minval[v])
                    continue;
                int lid = LCT::minid[v];
                LCT::cut(e[lid].u, lid + n);
                LCT::cut(e[lid].v, lid + n);
                vis[lid] = 0;
            } else {
                DSU::merge(u, v);
            }
            LCT::link(u, id + n);
            LCT::link(v, id + n);
            vis[id] = 1;
        } else if (opt[0] == 'm') {
            int u, v;
            cin >> u >> v;
            ++u, ++v;
            if (DSU::find(u) != DSU::find(v)) {
                cout << -1 << endl;
                continue;
            }
            LCT::split(u, v);
            cout << LCT::sum[v] << endl;
        } else {
            int id, l;
            cin >> id >> l;
            ++id;
            if (vis[id]) {
                LCT::access(id + n);
                LCT::splay(id + n);
                len[id + n] = l;
                LCT::pushup(id + n);
            }
        }
    }
    return 0;
}
// Asusetic eru quionours
```

#LCT