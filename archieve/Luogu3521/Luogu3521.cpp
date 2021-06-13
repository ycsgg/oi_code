#include <iostream>
using namespace std;
int n;
const int N = 4e5 + 5;
struct Node {
    int ls, rs, val;
} tr[N << 4];
int tot;
void update(int &rt, int l, int r, int v) {
    if (!rt) {
        rt = ++tot;
    }
    tr[rt].val++;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (v <= mid) {
        update(tr[rt].ls, l, mid, v);
    } else {
        update(tr[rt].rs, mid + 1, r, v);
    }
}
long long u, v;
void merge(int &x, int y) {
    if (!x || !y) {
        x = x + y;
        return;
    }
    tr[x].val += tr[y].val;
    u += 1ll * tr[tr[x].ls].val * tr[tr[y].rs].val;
    v += 1ll * tr[tr[x].rs].val * tr[tr[y].ls].val;
    merge(tr[x].ls, tr[y].ls);
    merge(tr[x].rs, tr[y].rs);
}
long long ans = 0;
void dfs(int &x) {
    int tmp;
    cin >> tmp;
    x = 0;
    if (!tmp) {
        int ls, rs;
        dfs(ls);
        dfs(rs);
        x = ls;
        u = 0, v = 0;
        merge(x, rs);
        ans += min(u, v);
    } else {
        update(x, 1, n, tmp);
    }
}
int main() {
    cin >> n;
    int rt;
    dfs(rt);
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours
