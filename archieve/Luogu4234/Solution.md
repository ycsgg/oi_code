### P4234 最小差值生成树

直接将边从大到小排序，依次加入，维护最小生成树

然后用LCT来动态维护即可

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 3e5 + 5;
typedef long long ll;
struct Edge {
    int v, u;
    ll w;
} edge[N * 2];
ll ans = 2e9;
namespace LCT {
ll val[N];
int ch[N][2], fa[N], rev[N], maxid[N];
bool isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}
void pushup(int x) {
    if (val[x] > val[maxid[ch[x][0]]] && val[x] > val[maxid[ch[x][1]]]) {
        maxid[x] = x;
    } else if (val[maxid[ch[x][0]]] > val[maxid[ch[x][1]]]) {
        maxid[x] = maxid[ch[x][0]];
    } else {
        maxid[x] = maxid[ch[x][1]];
    }
}
void pushdown(int x) {
    if (rev[x]) {
        swap(ch[x][0], ch[x][1]);
        rev[ch[x][0]] ^= 1;
        rev[ch[x][1]] ^= 1;
        rev[x] = 0;
    }
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
void pushpush(int x) {
    if (!isroot(x)) {
        pushpush(fa[x]);
    }
    pushdown(x);
}
void splay(int x) {
    pushpush(x);
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
        ch[x][1] = y;
        pushup(x);
        y = x;
        x = fa[x];
    }
}
void makeroot(int x) {
    access(x);
    splay(x);
    rev[x] ^= 1;
}
int findroot(int x) {
    access(x);
    splay(x);
    pushdown(x);
    while (ch[x][0]) {
        x = ch[x][0];
        pushdown(x);
    }
    splay(x);
    return x;
}
void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        fa[x] = y;
    }
}
void cut(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
    if ((findroot(y) == x) && (fa[y] == x) && (!ch[y][0])) {
        fa[y]    = 0;
        ch[x][1] = 0;
        pushup(x);
    }
}
bool query(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
    return findroot(y) == x;
}
void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
}
} // namespace LCT
int n, m;
bool is_cut[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    sort(edge + 1, edge + 1 + m, [&](const Edge &A, const Edge &B) -> bool {
        return A.w > B.w;
    });
    for (int i = 1; i <= m; i++) {
        LCT::val[i + n] = edge[i].w;
    }
    int cnt = 0, pos = 1;
    for (int i = 1; i <= m; i++) {
        int x = edge[i].u, y = edge[i].v;
        if (x == y) {
            is_cut[i] = 1;
            continue;
        }
        if (LCT::query(x, y)) {
            LCT::split(x, y);
            int now = LCT::maxid[y];
            LCT::cut(edge[now - n].u, now);
            LCT::cut(edge[now - n].v, now);
            is_cut[now - n] = 1;
            LCT::link(edge[i].u, i + n);
            LCT::link(edge[i].v, i + n);
        } else {
            LCT::link(edge[i].u, i + n);
            LCT::link(edge[i].v, i + n);
            cnt++;
        }
        if (cnt == n - 1) {
            while (is_cut[pos]) {
                pos++;
            }
            ans = min(ans, (ll)edge[pos].w - edge[i].w);
        }
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours
```

