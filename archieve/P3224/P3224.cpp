
#include <iostream>
using namespace std;
const int N = 1e5 + 5;

struct Node {
    int val, fa, siz, ch[2];
} tr[N * 5];
int fa[N], rt[N], rk[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int n, m, tot, q;
void pushup(int x) {
    tr[x].siz = tr[tr[x].ch[0]].siz + tr[tr[x].ch[1]].siz + 1;
}
bool identity(int x) {
    return tr[tr[x].fa].ch[1] == x;
}
void rotate(int x) {
    int k = identity(x);
    int f = tr[x].fa, son = tr[x].ch[k ^ 1];
    tr[x].ch[k ^ 1] = f;
    tr[f].ch[k]     = son;
    if (son) {
        tr[son].fa = f;
    }
    tr[x].fa = tr[f].fa;
    if (tr[x].fa) {
        tr[tr[f].fa].ch[identity(f)] = x;
    }
    tr[f].fa = x;
    pushup(f);
    pushup(x);
}
void splay(int x, int target) {
    while (tr[x].fa != target) {
        int y = tr[x].fa;
        int z = tr[y].fa;
        if (z != target) {
            (tr[z].ch[0] == y) ^ (tr[y].ch[0] == x) ? rotate(x) : rotate(y);
            //identity(x) == identity(tr[x].fa) ? rotate(tr[x].fa) : rotate(x);
        }
        rotate(x);
    }
    if (target <= n) {
        rt[target] = x;
    }
}
void insert(int x, int id) {
    int u = rt[id], f = id;
    while (u && tr[u].val != x) {
        f = u;
        u = tr[u].ch[x > tr[u].val ? 1 : 0];
    }
    u         = ++tot;
    tr[u].siz = 1;
    tr[u].fa  = f;
    if (f > n) {
        tr[f].ch[x > tr[f].val] = u;
    }
    tr[u].val   = x;
    tr[u].ch[0] = tr[u].ch[1] = 0;
    splay(u, id);
}
void _merge(int u, int id) {
    if (tr[u].ch[0])
        _merge(tr[u].ch[0], id);
    if (tr[u].ch[1])
        _merge(tr[u].ch[1], id);
    insert(tr[u].val, id);
}
void merge(int a, int b) {
    int x = find(a), y = find(b);
    if (x == y) {
        return;
    }
    if (tr[rt[x]].siz > tr[rt[y]].siz) {
        swap(x, y);
    }
    fa[x] = y;
    _merge(rt[x], y);
}
int kth(int id, int rk) {
    int u = rt[id];
    if (tr[u].siz < rk) {
        return -1;
    }
    while (1) {
        if (tr[tr[u].ch[0]].siz + 1 < rk) {
            rk -= tr[tr[u].ch[0]].siz + 1;
            u = tr[u].ch[1];
        } else if (tr[tr[u].ch[0]].siz >= rk) {
            u = tr[u].ch[0];
        } else {
            return tr[u].val;
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        rt[i] = i + n;
        int x;
        cin >> x;
        rk[x]         = i;
        tr[rt[i]].val = x;
        tr[rt[i]].siz = 1;
        tr[rt[i]].fa  = i;
    }
    tot = n * 2;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        merge(x, y);
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        char ch;
        int x, y;
        cin >> ch >> x >> y;
        if (ch == 'Q') {
            int d = kth(find(x), y);
            cout << (d == -1 ? -1 : rk[d]) << endl;
        } else {
            merge(x, y);
        }
    }
    return 0;
}
