#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
const int N = 3e5 + 10;
namespace DSU {
int fa[N], siz[N];
void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        siz[i] = 1;
    }
}
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
} // namespace DSU
int n, m, k;
unordered_map<int, int> e[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    queue<pair<int, int>> q;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (e[v].count(w)) {
            q.push(make_pair(u, e[v][w]));
        } else {
            e[v][w] = u;
        }
    }
    DSU::init(n);
    while (!q.empty()) {
        using DSU::fa;
        using DSU::siz;
        auto [u, v] = q.front();
        q.pop();
        u = DSU::find(u);
        v = DSU::find(v);
        if (u == v) {
            continue;
        }
        if (siz[u] < siz[v]) {
            swap(u, v);
        }
        fa[v] = u;
        siz[u] += siz[v];
        for (auto p : e[v]) {
            if (e[u][p.first]) {
                q.push(make_pair(p.second, e[u][p.first]));
            } else {
                e[u][p.first] = p.second;
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i == DSU::find(i)) {
            ans += 1ll * DSU::siz[i] * (DSU::siz[i] - 1) / 2;
        }
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours.