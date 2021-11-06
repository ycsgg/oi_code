#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
#define int ll
const int N = 1e5 + 10;
struct Item {
    int d, p, l;
} a[N];
int n, q;
int root[N];
namespace PSegmentTree {
struct Node {
    int ls, rs;
    ll s, sum;
} tr[N * 20];
int tot;
void insert(int &now, int pre, int l, int r, int x, int v) {
    if (!now) {
        now = ++tot;
    }
    tr[now].s = tr[pre].s + v;
    tr[now].sum = 1ll * tr[pre].sum + 1ll * x * v;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) {
        insert(tr[now].ls, tr[pre].ls, l, mid, x, v);
        tr[now].rs = tr[pre].rs;
    } else {
        insert(tr[now].rs, tr[pre].rs, mid + 1, r, x, v);
        tr[now].ls = tr[pre].ls;
    }
}

ll query(int x, int l, int r, int k) {
    if (l == r) {
        return l * k;
    }
    int mid = (l + r) / 2;
    if (tr[tr[x].ls].s >= k) {
        return query(tr[x].ls, l, mid, k);
    } else {
        return tr[tr[x].ls].sum +
               query(tr[x].rs, mid + 1, r, k - tr[tr[x].ls].s);
    }
}
} // namespace PSegmentTree
signed main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].d >> a[i].p >> a[i].l;
    }
    sort(a + 1, a + 1 + n, [&](const auto &A, const auto &B) -> bool {
        return A.d > B.d;
    });
    for (int i = 1; i <= n; i++) {
        PSegmentTree::insert(root[i], root[i - 1], 1, 1e5, a[i].p, a[i].l);
    }
    while (q--) {
        ll g, L;
        cin >> g >> L;
        int l = 1, r = n, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto tmp = PSegmentTree::query(root[mid], 1, 1e5, L);
            if (tmp <= g && PSegmentTree::tr[root[mid]].s >= L) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << (res == -1 ? -1 : a[res].d) << '\n';
    }
}