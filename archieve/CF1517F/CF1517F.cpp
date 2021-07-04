#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N   = 305;
const int mod = 998244353;
int n;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} Tr;
int OFFSET;
array<array<int, N * 2>, N> f;
// negative : dis
void Add(int &x, int y) {
    if ((x += y) > mod)
        x -= mod;
}
void dp(int x, int fa, int r) {
    f[x].fill(0);
    bool cnt = 0;
    for (auto v : Tr.edge[x]) {
        if (v != fa) {
            dp(v, x, r);
            cnt = 1;
        }
    }
    f[x][r + OFFSET] = f[x][OFFSET - 1] = 1;
    if (!cnt) {
        return;
    }
    for (auto v : Tr.edge[x]) {
        if (v == fa)
            continue;
        vector<pair<int, int>> tmp1, tmp2;
        for (int i = 0; i <= n * 2; i++) {
            if (f[x][i]) {
                tmp1.push_back({i - OFFSET, f[x][i]});
                f[x][i] = 0;
            }
        }
        for (int i = 0; i <= n * 2; i++) {
            if (f[v][i]) {
                tmp2.push_back({i - OFFSET, f[v][i]});
            }
        }
        for (auto p1 : tmp1) {
            for (auto p2 : tmp2) {
                auto px = p1.first, py = p2.first;
                int w = 1ll * p1.second * p2.second % mod;
                if (px < 0 && py < 0) {
                    f[x][min(px, py - 1) + OFFSET] += w;
                    f[x][min(px, py - 1) + OFFSET] %= mod;
                }
                if (px < 0 && py >= 0) {
                    f[x][(px + py >= 0 ? py - 1 : px) + OFFSET] += w;
                    f[x][(px + py >= 0 ? py - 1 : px) + OFFSET] %= mod;
                }
                if (px >= 0 && py < 0) {
                    f[x][(px + py >= 0 ? px : py - 1) + OFFSET] += w;
                    f[x][(px + py >= 0 ? px : py - 1) + OFFSET] %= mod;
                }
                if (px >= 0 && py >= 0) {
                    f[x][max(px, py - 1) + OFFSET] += w;
                    f[x][max(px, py - 1) + OFFSET] %= mod;
                }
                // printf("%d %d %d\n", px, py, w);
            }
        }
    }
}
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        b /= 2;
    }
    return res;
}
int main() {
    cin >> n;
    OFFSET = n + 1;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    int ans = 0;
    for (int r = 1; r < n; r++) {
        dp(1, 0, r);
        for (int i = 0; i < OFFSET; i++) {
            ans += f[1][i];
            ans %= mod;
        }
    }
    ans = 1ll * ans * qpow(qpow(2, mod - 2), n) % mod;  
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours