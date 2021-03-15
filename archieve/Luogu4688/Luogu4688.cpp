#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, M = 2e4, BLOCK_SIZE = 320;
ll n, m, a[N], b[N], lm_cnt[N];
ll vis[N], len[N];
int belong[N];
bitset<N> num[M + 5], cur;
struct Node {
    ll l, r, id;
    friend bool operator<(const Node &a, const Node &b) {
        ll x = belong[a.l], y = belong[b.l];
        if (x == y)
            return a.r < b.r;
        return x < y;
    }
} q[N];
void modify(ll x, ll y) {
    ll z = a[x];
    if (y == -1) {
        lm_cnt[z]--;
        cur[z + lm_cnt[z]] = 0;
    } else {
        cur[z + lm_cnt[z]] = 1;
        lm_cnt[z]++;
    }
}
void solve(int tot) {
    if (tot < 0)
        exit(0);
    int cnt = 0;
    memset(lm_cnt, 0, sizeof(lm_cnt));
    for (int i = 1; i <= tot; i++) {
        len[i] = vis[i] = 0;
        for (int j = 1; j <= 3; j++) {
            q[++cnt].id = i;
            scanf("%lld%lld", &q[cnt].l, &q[cnt].r);
            len[i] += q[cnt].r - q[cnt].l + 1;
        }
    }
    sort(q + 1, q + 1 + cnt);
    ll l = 1, r = 0;
    cur.reset();
    for (int i = 1; i <= cnt; i++) {
        while (l > q[i].l) {
            l--;
            modify(l, 1);
        }
        while (r < q[i].r) {
            r++;
            modify(r, 1);
        }
        while (l < q[i].l) {
            modify(l, -1);
            l++;
        }
        while (r > q[i].r) {
            modify(r, -1);
            r--;
        }
        if (vis[q[i].id]) {
            num[q[i].id] &= cur;
        } else {
            vis[q[i].id] = 1;
            num[q[i].id] = cur;
        }
    }
    for (int i = 1; i <= tot; i++) {
        printf("%lld\n", len[i] - 3ll * (ll)num[i].count());
    }
}
int main() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    for (ll i = 1; i <= n; i++) {
        a[i]      = ll(lower_bound(b + 1, b + 1 + n, a[i]) - b);
        belong[i] = ((i - 1) / BLOCK_SIZE + 1);
    }
    while ("qwq") {
        solve(min(m, (ll)20000));
        m -= 20000;
    }
}