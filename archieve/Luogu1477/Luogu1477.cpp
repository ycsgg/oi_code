#include <iostream>
#include <map>
#include <vector>
using namespace std;
int n, m;
const int N = 1e5 + 5;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
map<pair<int, int>, bool> mp;
bool vis[N];
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int dep[N], ans = 0;
int maxl, minl;
void dfs(int x, int d) {
    // cout << x << " " << d << endl;
    if (dep[x]) {
        // cout << d - dep[x] << endl;
        ans = gcd(ans, abs(d - dep[x]));
        return;
    }
    dep[x] = d;
    vis[x] = 1;
    maxl   = max(maxl, dep[x]);
    minl   = min(minl, dep[x]);
    for (auto e : G.edge[x]) {
        dfs(e.v, d + e.w);
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        if (!mp.count(make_pair(a, b))) {
            mp[make_pair(a, b)] = 1;
            G.add(a, b, 1);
            G.add(b, a, -1);
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            maxl = -0x3f3f3f3f;
            minl = -maxl;
            dfs(i, 1);
            res += maxl - minl + 1;
        }
    }
    if (!ans) {
        if (res < 3) {
            cout << "-1 -1" << endl;
            exit(0);
        }
        cout << res << " 3" << endl;
        return 0;
    } else {
        if (ans < 3) {
            cout << "-1 -1" << endl;
            exit(0);
        }
        for (int i = 3; i <= ans; i++) {
            if (ans % i == 0) {
                cout << ans << " " << i << endl;
                return 0;
            }
        }
    }
    return 0;
}
// Asusetic eru quionours