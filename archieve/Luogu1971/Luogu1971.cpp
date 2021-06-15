#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int N = 45, K = 1005;
int n, m;
struct Graph {
    vector<int> edge[N * N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
    void add_two(int u, int v) {
        add(u, v);
        add(v, u);
    }
} G;
const array<int, 4> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};
array<char, N> s;
array<array<int, N>, N> mp;
array<bool, N * N> ban;
array<int, N * N> vis, link;
array<bool, 2 * K> win;
array<int, K> ans;
int vistim;
int sx, sy;
bool match(int x, const Graph &G) {
    if (ban[x]) {
        return false;
    }
    for (auto v : G.edge[x]) {
        if (vis[v] == vistim || ban[v]) {
            continue;
        }
        vis[v] = vistim;
        if (!link[v] || match(link[v], G)) {
            link[v] = x;
            link[x] = v;
            return true;
        }
    }
    return false;
}
int id(int x, int y) {
    return (x - 1) * m + y;
}
bool check_bound(int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (s.data() + 1);
        for (int j = 1; j <= m; j++) {
            if (s[j] == 'O') {
                mp[i][j] = 0;
            } else if (s[j] == 'X') {
                mp[i][j] = 1;
            } else {
                mp[i][j] = 1;
                sx       = i;
                sy       = j;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!mp[i][j]) {
                continue;
            }
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (check_bound(nx, ny) && !mp[nx][ny]) {
                    G.add_two(id(i, j), id(nx, ny));
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]) {
                ++vistim;
                match(id(i, j), G);
            }
        }
    }
    int k;
    cin >> k;
    k *= 2;
    for (int i = 1; i <= k; i++) {
        int now  = id(sx, sy);
        ban[now] = 1;
        if (link[now]) {
            int y     = link[now];
            link[now] = link[y] = 0;
            ++vistim;
            win[i] = !match(y, G);
        }
        cin >> sx >> sy;
    }
    k /= 2;
    int tot = 0;
    for (int i = 1; i <= k; ++i) {
        if (win[i * 2 - 1] && win[i * 2]) {
            ans[++tot] = i;
        }
    }
    cout << tot << endl;
    for (int i = 1; i <= tot; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
// Asusetic eru quionours
