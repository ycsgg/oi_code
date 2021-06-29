### P4172 [WC2006]水管局长
类似　[[P6664 清华集训2016 温暖会指引我们前行]]

只要把删边倒过来变成加边就是动态维护最小生成树

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
const int N = 2e5 + 5;
namespace LCT {
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
array<int, N> fa, tag, val, sum;
array<array<int, 2>, N> ch;
void pushup(int x) {
    sum[x] = max(val[x], max(sum[ls(x)], sum[rs(x)]));
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
    for (auto i = st.rbegin(); i != st.rend(); i++) {
        pushdown(*i);
    }
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
int find(int k, int x) {
    if (val[k] == x)
        return k;
    if (sum[ls(k)] == x)
        return find(ls(k), x);
    return find(rs(k), x);
}
#undef ls
#undef rs
} // namespace LCT
namespace DSU {
array<int, N> fa;
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        fa[x] = y;
    }
}
} // namespace DSU

struct Edge {
    int u, v, w;
    bool del;
};
struct Oper {
    int opt, u, v;
};
// unordered_map<pair<int, int>, bool> G;
int G[1005][1005];
int n, m, q;
void Kruskal(const vector<Edge> &edge) {
    for (int i = 1; i <= n; i++) {
        DSU::fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        if (!edge[i].del) {
            if (DSU::find(edge[i].u) != DSU::find(edge[i].v)) {
                DSU::merge(edge[i].u, edge[i].v);
                LCT::link(edge[i].u, i + n);
                LCT::link(edge[i].v, i + n);
            }
        }
    }
}
int main() {
    cin >> n >> m >> q;
    vector<Edge> edge(m + 1);
    vector<Oper> op(q + 1);
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    sort(edge.begin() + 1, edge.end(),
         [&](const Edge &A, const Edge &B) -> bool {
             return A.w < B.w;
         });
    for (int i = 1; i <= m; i++) {
        auto &e     = edge[i];
        G[e.u][e.v] = G[e.v][e.u] = i;
        LCT::val[i + n]           = e.w;
    }
    for (int i = 1; i <= q; i++) {
        cin >> op[i].opt >> op[i].u >> op[i].v;
        if (op[i].opt == 2) {
            edge[G[op[i].u][op[i].v]].del = 1;
        }
    }
    Kruskal(edge);
    vector<int> ans;
    for (int i = q; i >= 1; i--) {
        if (op[i].opt == 1) {
            LCT::split(op[i].u, op[i].v);
            ans.push_back(LCT::sum[op[i].v]);
        } else {
            LCT::split(op[i].u, op[i].v);
            int id = LCT::find(op[i].v, LCT::sum[op[i].v]) - n;
            if (LCT::val[G[op[i].u][op[i].v] + n] < LCT::sum[op[i].v]) {
                LCT::cut(edge[id].u, id + n);
                LCT::cut(edge[id].v, id + n);
                LCT::link(op[i].u, G[op[i].u][op[i].v] + n);
                LCT::link(op[i].v, G[op[i].u][op[i].v] + n);
            }
        }
    }
    for (auto i = ans.rbegin(); i != ans.rend(); i++) {
        cout << *i << endl;
    }
    return 0;
}
// Asusetic eru quionours

```

#LCT 