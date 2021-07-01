###　P4219 [BJOI2014]大融合

不 要 L C T

仅需维护每个点所在树的根和当前子树的大小即可

先把最终形态建出来，对于加入的边 $(x,y) $

不妨设 $y$ 是 $x$ 的父亲，我们需要将 $(y,rt_y)$ 链上加上 $siz_x$ 

查询就是 $siz_x(siz_y-siz_x)$ 

dfs序+树状数组维护即可

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll    = long long;
const int N = 1e5 + 10;
int n, q;
namespace DSU {
array<int, N> fa;
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
} // namespace DSU
namespace BIT {
array<int, N> c;
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int v) {
    if (!pos)
        return ;
    while (pos <= n) {
        c[pos] += v;
        pos += lowbit(pos);
    }
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
int query(int l, int r) {
    return query(r) - query(l - 1);
}
} // namespace BIT

struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
    auto &operator[](const int &x) const {
        return edge[x];
    }
} Tr;
struct Oper {
    int opt, u, v;
};
array<int, N> in, out, fa;
int idcnt;
array<Oper, N> qr;
void dfs(int x, int _fa) {
    fa[x] = _fa;
    in[x] = ++idcnt;
    for (auto v : Tr[x]) {
        if (v != _fa) {
            dfs(v, x);
        }
    }
    out[x] = idcnt;
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        char opt;
        cin >> opt >> qr[i].u >> qr[i].v;
        qr[i].opt = (opt == 'Q');
        if (!qr[i].opt) {
            Tr.add(qr[i].u, qr[i].v);
            Tr.add(qr[i].v, qr[i].u);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            dfs(i, 0);
        }
        DSU::fa[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        BIT::add(in[i], 1);
        BIT::add(in[fa[i]], -1);
    }
    for (int i = 1; i <= q; i++) {
        int u = qr[i].u, v = qr[i].v;
        if (in[u] < in[v]) {
            swap(u, v);
        }
        int fv  = DSU::find(v);
        int siz = BIT::query(in[u], out[u]);
        if (qr[i].opt) {
            cout << siz * (BIT::query(in[fv], out[fv]) - siz) << endl;
        } else {
            BIT::add(in[v], siz);
            BIT::add(in[fa[fv]], -siz);
            DSU::fa[u] = fv;
        }
    }
    return 0;
}
// Asusetic eru quionours.
```

#树状数组