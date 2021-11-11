#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 100010, mod = 1000000007;
int n, m, a[N], b[N], cnt, bk[N];
pair<int, int> q[N];

namespace BIT {
int c[N];
int lowbit(int x) {
    return x & (-x);
}
void add(int x, int d) {
    while (x <= cnt) {
        c[x] = (c[x] + d) % mod;
        x += lowbit(x);
    }
}
int query(int x) {
    int res = 0;
    while (x) {
        res = (res + c[x]) % mod;
        x -= lowbit(x);
    }
    return res;
}
} // namespace BIT

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
    }

    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        int pos = lower_bound(b + 1, b + m + 1, a[i]) - b;
        if (pos == 1 || pos > m) {
            continue;
        }
        q[++tot] = make_pair(a[i] - b[pos - 1], -(b[pos] - a[i]));
        bk[tot] = -q[tot].second;
    }

    sort(q + 1, q + tot + 1);
    for (int i = 1; i <= tot; ++i) {
        q[i].second *= -1;
    }
    sort(bk + 1, bk + tot + 1);
    cnt = unique(bk + 1, bk + tot + 1) - bk;
    for (int i = 1; i <= tot; ++i) {
        q[i].second = lower_bound(bk + 1, bk + cnt, q[i].second) - bk + 1;
    }

    BIT::add(1, 1);
    for (int i = 1; i <= tot; ++i) {
        if (q[i].first == q[i - 1].first && q[i].second == q[i - 1].second) {
            continue;
        }
        int t = BIT::query(q[i].second - 1);
        BIT::add(q[i].second, t);
    }

    cout << BIT::query(cnt);

    return 0;
}

// Asusetic eru quionours.