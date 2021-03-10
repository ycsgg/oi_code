
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N       = 1e5 + 10;
const int MAXNODE = N << 6;
int n, m;
vector<int> st[N], ed[N];
int a[N], b[N];
int rt[MAXNODE], lson[MAXNODE], rson[MAXNODE], cnt[MAXNODE], tot;
long long sum[MAXNODE];
void insert(int &u, int pre, int l, int r, int pos, int v) {
    u       = ++tot;
    lson[u] = lson[pre];
    rson[u] = rson[pre];
    sum[u]  = sum[pre] + (v * b[pos]);
    cnt[u]  = cnt[pre] + v;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(lson[u], lson[pre], l, mid, pos, v);
    } else {
        insert(rson[u], rson[pre], mid + 1, r, pos, v);
    }
    return;
}
long long query(int u, int l, int r, int k) {
    int num = cnt[lson[u]];
    if (l == r) {
        return sum[u] / (1ll * cnt[u]) * 1ll * k;
    }
    int mid = (l + r) / 2;
    if (k <= num) {
        return query(lson[u], l, mid, k);
    } else {
        return query(rson[u], mid + 1, r, k - num) + sum[lson[u]];
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y >> a[i];
        b[i] = a[i];
        st[x].push_back(i);
        ed[y + 1].push_back(i);
    }
    sort(b + 1, b + 1 + n);
    int tot_b = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= m; i++) {
        rt[i] = rt[i - 1];
        for (auto j : st[i]) {
            int p = lower_bound(b + 1, b + 1 + tot_b, a[j]) - b;
            insert(rt[i], rt[i], 1, tot_b, p, 1);
        }
        for (auto j : ed[i]) {
            int p = lower_bound(b + 1, b + 1 + tot_b, a[j]) - b;
            insert(rt[i], rt[i], 1, tot_b, p, -1);
        }
    }
    long long ans = 1;
    for (int i = 1; i <= m; i++) {
        int x, a, b, c, k;
        cin >> x >> a >> b >> c;
        k = (1ll * ans * a + b) % c + 1;
        if (k > cnt[rt[x]]) {
            ans = sum[rt[x]];
        } else {
            ans = query(rt[x], 1, tot_b, k);
        }
        cout << ans << endl;
    }
}


