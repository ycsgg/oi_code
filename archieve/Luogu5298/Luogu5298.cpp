#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int N  = 3e5 + 5;
const ll mod = 998244353;
const ll inv = 796898467;
int n;
int son[N][2], fa[N], val[N];
int w[N], cnt;
int rt[N];
int p[N];
int id[N];
namespace SegmentTree {
struct Node {
    int val, tag;
    int ls, rs;
} tr[N << 5];
int tot;
int mul(int a, int b) {
    return 1ll * a * b % mod;
}
void push(int x) {
    if (tr[x].tag != 1) {
        tr[tr[x].ls].val = mul(tr[tr[x].ls].val, tr[x].tag);
        tr[tr[x].ls].tag = mul(tr[tr[x].ls].tag, tr[x].tag);
        tr[tr[x].rs].val = mul(tr[tr[x].rs].val, tr[x].tag);
        tr[tr[x].rs].tag = mul(tr[tr[x].rs].tag, tr[x].tag);
        tr[x].tag        = 1;
    }
}
void pushup(int x) {
    tr[x].val = 1ll * (tr[tr[x].ls].val + tr[tr[x].rs].val) % mod;
}
void insert(int &rt, int l, int r, int pos) {
    if (!rt) {
        rt         = ++tot;
        tr[rt].tag = 1;
    }
    if (l == r) {
        tr[rt].val = 1;
        return;
    }
    push(rt);
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(tr[rt].ls, l, mid, pos);
    } else {
        insert(tr[rt].rs, mid + 1, r, pos);
    }
    pushup(rt);
}
int merge(int x, int y, int tagx, int tagy, int v) {
    if (!x && !y) {
        return 0;
    }
    if (!x) {
        tr[y].val = mul(tr[y].val, tagy);
        tr[y].tag = mul(tr[y].tag, tagy);
        return y;
    }
    if (!y) {
        tr[x].val = mul(tr[x].val, tagx);
        tr[x].tag = mul(tr[x].tag, tagx);
        return x;
    }
    push(x);
    push(y);

    int slx = tr[tr[x].ls].val, srx = tr[tr[x].rs].val;
    int sly = tr[tr[y].ls].val, sry = tr[tr[y].rs].val;
    tr[x].ls = merge(tr[x].ls, tr[y].ls,
                     (tagx + 1ll * (1 - v + mod) % mod * sry) % mod,
                     (tagy + 1ll * (1 - v + mod) % mod * srx) % mod, v);
    tr[x].rs = merge(tr[x].rs, tr[y].rs, (tagx + 1ll * v * sly) % mod,
                     (tagy + 1ll * v * slx) % mod, v);
    pushup(x);
    return x;
}
void solve(int x, int l, int r) {
    if (l == r) {
        p[l] = tr[x].val;
        return;
    }
    push(x);
    int mid = (l + r) / 2;
    if (tr[x].ls) {
        solve(tr[x].ls, l, mid);
    }
    if (tr[x].rs) {
        solve(tr[x].rs, mid + 1, r);
    }
}
} // namespace SegmentTree
void pre(int x) {
    if (son[x][1]) {
        pre(son[x][0]);
        pre(son[x][1]);
        rt[x] = SegmentTree::merge(rt[son[x][0]], rt[son[x][1]], 0, 0, val[x]);
    } else if (son[x][0]) {
        pre(son[x][0]);
        rt[x] = rt[son[x][0]];
    } else {
        SegmentTree::insert(rt[x], 1, cnt, id[x]);
    }
}
ll ans = 0;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> fa[i];
        if (!son[fa[i]][0]) {
            son[fa[i]][0] = i;
        } else {
            son[fa[i]][1] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i <= n; i++) {
        if (son[i][0]) {
            val[i] = (1ll * val[i] * inv) % mod;
        } else {
            w[++cnt] = val[i];
        }
    }
    sort(w + 1, w + 1 + cnt);
    for (int i = 1; i <= n; ++i) {
        if (!son[i][0]) {
            id[i] = lower_bound(w + 1, w + cnt + 1, val[i]) - w;
        }
    }
    pre(1);
    SegmentTree::solve(rt[1], 1, cnt);
    for (int i = 1; i <= cnt; i++) {
        ans = (ans + 1ll * i * p[i] % mod * p[i] % mod * w[i] % mod) % mod;
    }
    cout << ans << endl;
}