#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 3e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G, TrG;
int tot, n, m;
int id[N];
namespace DSU {
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
} // namespace DSU
int fa[N][20], siz[N];
void dfs(int x, int _fa) {
    fa[x][0] = _fa;
    for (int i = 1; i <= 19; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    int flag = 1;
    for (auto v : TrG.edge[x]) {
        flag = 0;
        if (v == _fa)
            continue;
        dfs(v, x);
        siz[x] += siz[v];
    }
    siz[x] += flag;
}
int check(int x, int y, int mid) {
    for (int i = 19; ~i; i--) {
        if (id[fa[x][i]] <= mid) {
            x = fa[x][i];
        }
        if (id[fa[y][i]] <= mid) {
            y = fa[y][i];
        }
    }
    if (x == y)
        return siz[x];
    else
        return siz[x] + siz[y];
}
int main() {
    cin >> n >> m;
    tot = n;
    for (int i = 1; i <= 2 * n; i++) {
        DSU::fa[i] = i;
    }
    id[0] = 0x7f7f7f7f;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        x = DSU::find(x);
        y = DSU::find(y);
        if (x != y && tot < n * 2 - 1) {
            id[++tot] = i;
            DSU::fa[x] = tot;
            DSU::fa[y] = tot;
            TrG.add(tot, x);
            TrG.add(tot, y);
        }
    }
    dfs(tot, 0);
    int q;
    cin >> q;
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        int l = 0, r = m, ans = m;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(x, y, mid) < z) {
                l = mid + 1;
                ans = l;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours
