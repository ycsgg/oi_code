### P3527 [POI2011]MET-Meteors

整体二分

比较板

没啥可写的

```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int K = 3e5 + 5;
const int N = 3e5 + 5;
int n, m, k;
int ql[K], qr[K];
ll val[K];
struct Query {
    int id;
    ll cnt;
} q[N], tmpql[N], tmpqr[N], tmpq[N];
vector<int> S[N];
ll ans[N];
namespace BIT {
ll c[N * 2];
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, ll v) {
    while (pos <= 2 * m) {
        c[pos] += v;
        pos += lowbit(pos);
    }
}
void add(int l, int r, ll v) {
    if (l <= r) {
        add(l, v);
        add(r + 1, -v);
    } else {
        add(l, v);
        add(m + 1, -v);
        add(1, v);
        add(r + 1, -v);
    }
}
ll query(int pos) {
    ll res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
} // namespace BIT
void solve(int l, int r, int x, int y) {
    if (l == r) {
        for (int i = x; i <= y; i++) {
            ans[q[i].id] = l;
        }
        return;
    }
    int mid = (l + r) / 2;
    int tl = 0, tr = 0;
    for (int i = l; i <= mid; i++) {
        BIT::add(ql[i], qr[i], val[i]);
    }
    for (int i = x; i <= y; i++) {
        ll sum = 0;
        for (auto p : S[q[i].id]) {
            if (sum >= q[i].cnt) {
                break;
            }
            sum += BIT::query(p);
        }
        if (sum >= q[i].cnt) {
            tmpql[++tl] = q[i];
        } else {
            tmpqr[++tr] = q[i];
            tmpqr[tr].cnt -= sum;
        }
    }
    for (int i = l; i <= mid; i++) {
        BIT::add(ql[i], qr[i], -val[i]);
    }
    for (int i = 1; i <= tl; i++) {
        q[x + i - 1] = tmpql[i];
    }
    for (int i = 1; i <= tr; i++) {
        q[x + i + tl - 1] = tmpqr[i];
    }
    solve(l, mid, x, x + tl - 1);
    solve(mid + 1, r, y - tr + 1, y);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        S[x].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> q[i].cnt;
        q[i].id = i;
    }
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> ql[i] >> qr[i] >> val[i];
    }
    solve(1, k + 1, 1, n);
    for (int i = 1; i <= n; i++) {
        if (ans[i] == k + 1) {
            cout << "NIE" << endl;
            continue;
        }
        cout << ans[i] << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

