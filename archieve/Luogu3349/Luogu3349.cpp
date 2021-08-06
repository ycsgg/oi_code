#include <array>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 18;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} Tr;
int n, m;
int G[N][N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = G[v][u] = 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    int U = (1 << n) - 1;
    ll ans = 0;
    for (int S = 0; S <= U; S++) {
        vector<int> id;
        vector<vector<ll>> dpf(n + 1, vector<ll>(n + 1, 0));
        for (int i = 1; i <= n; i++) {
            if (S & (1 << i - 1)) {
                id.push_back(i);
            }
        }
        static function<void(int, int)> dp = [&](int x, int fa) -> void {
            for (auto v : Tr.edge[x]) {
                if (v == fa) {
                    continue;
                }
                dp(v, x);
            }
            for (auto i : id) {
                dpf[x][i] = 1;
                for (auto v : Tr.edge[x]) {
                    if (v == fa)
                        continue;
                    ll sum = 0;
                    for (auto j : id) {
                        if (!G[i][j])
                            continue;
                        sum += dpf[v][j];
                    }
                    dpf[x][i] *= sum;
                }
            }
        };
        dp(1, 0);
        ll sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += dpf[1][i];
        }
        ans += sum * (((n - __builtin_popcount(S)) & 1) ? -1 : 1);
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours