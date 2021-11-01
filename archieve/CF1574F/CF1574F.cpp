#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 3e5 + 10;
int n, m, k;
int pre[N], nxt[N];
namespace DSU {
int fa[N], siz[N];
bool ban[N];
void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        siz[i] = 1;
    }
}
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        ban[x] = 1;
        return;
    }
    if (siz[x] > siz[y]) {
        swap(x, y);
    }
    fa[x] = y;
    siz[y] += siz[x];
    ban[y] |= ban[x];
}
} // namespace DSU
int cnt[N];
int tot[N], id;
ll dp[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    DSU::init(k);
    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        vector<int> a(c + 1);
        for (int j = 1; j <= c; j++) {
            cin >> a[j];
        }
        for (int j = 2; j <= c; j++) {
            if ((pre[a[j]] && pre[a[j]] != a[j - 1]) ||
                (nxt[a[j - 1]] && nxt[a[j - 1]] != a[j])) {
                DSU::merge(a[j - 1], a[j]);
                DSU::ban[DSU::find(a[j])] = 1;
            } else if (!nxt[a[j - 1]]) {
                pre[a[j]] = a[j - 1];
                nxt[a[j - 1]] = a[j];
                DSU::merge(a[j], a[j - 1]);
            }
        }
    }
    for (int i = 1; i <= k; i++) {
        if (DSU::find(i) != i || DSU::ban[i]) {
            continue;
        }
        ++cnt[DSU::siz[i]];
    }
    for (int i = 1; i <= k; i++) {
        if (cnt[i]) {
            tot[++id] = i;
        }
    }
    dp[0] = 1;
    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= id && i + tot[j] <= m; j++) {
            dp[i + tot[j]] = (dp[i + tot[j]] + dp[i] * cnt[tot[j]] % mod) % mod;
        }
    }
    cout << dp[m];
    return 0;
}
// Asusetic eru quionours.
