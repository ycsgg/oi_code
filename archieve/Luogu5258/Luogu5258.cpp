#include <array>
#include <iostream>
#include <vector>

using namespace std;
const int N = 1e5 + 10;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
};
Graph G;
int n;
array<int, N> g, d;
int ans;
void dfs(int x, int fa) {
    int cnt[2] = {0, 0};
    for (auto e : G.edge[x]) {
        if (e.v == fa)
            continue;
        d[e.v] = e.w;
        dfs(e.v, x);
        cnt[d[e.v]] += g[e.v];
    }
    if (x == 1) {
        ans += max(cnt[1], cnt[0]);
        return;
    }
    ans += min(cnt[0], cnt[1]);
    if (cnt[d[x]] > cnt[d[x] ^ 1]) {
        g[x] = cnt[d[x]] - cnt[d[x] ^ 1];
    } else if (cnt[d[x] ^ 1] > cnt[d[x]]) {
        ans += cnt[d[x] ^ 1] - cnt[d[x]];
    }
}
int main() {
    cin >> n;
    g.fill(1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ++x, ++y;
        G.add(x, y, 1);
        G.add(y, x, 0);
    }
    dfs(1, 0);
    cout << ans << endl;
}
// Asusetic eru quionours
