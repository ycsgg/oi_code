#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 5050;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
    vector<int> &operator[](const int &x) {
        return edge[x];
    }
    const vector<int> &operator[](const int &x) const {
        return edge[x];
    }
} Tr;
int n, m;
namespace SubtaskTree {
vector<int> ans;
void dfs(int x, int pre) {
    ans.push_back(x);
    for (auto v : Tr[x]) {
        if (v == pre) {
            continue;
        }
        dfs(v, x);
    }
}
void solve() {
    for (int i = 1; i <= n; i++) {
        sort(Tr[i].begin(), Tr[i].end());
    }
    dfs(1, 0);
    for (auto v : ans) {
        cout << v << ' ';
    }
}
} // namespace SubtaskTree
namespace SubtaskCycledTree {
int res[5050], cur;
int ans[5050];
bool vis[5050];
void dfs(int x, int pre, pair<int, int> &ban) {
    if (vis[x]) {
        return;
    }
    vis[x] = 1;
    res[++cur] = x;
    for (auto v : Tr[x]) {
        if (v == pre || (v == ban.second && x == ban.first) ||
            (v == ban.first && x == ban.second)) {
            continue;
        }
        dfs(v, x, ban);
    }
}
bool banned[N][N];
void solve() {
    for (int i = 1; i <= n; i++) {
        sort(Tr[i].begin(), Tr[i].end());
    }
    for (int i = 1; i <= n; i++) {
        for (auto v : Tr[i]) {
            if (banned[i][v]) {
                continue;
            }
            auto ban = make_pair(i, v);
            banned[i][v] = banned[v][i] = 1;
            cur = 0;
            memset(vis, 0, sizeof(vis));
            dfs(1, 0, ban);
            if (cur != n) {
                continue;
            }
            if (!ans[1]) {
                for (int i = 1; i <= n; i++) {
                    ans[i] = res[i];
                }
            } else {
                for (int i = 1; i <= n; i++) {
                    if (res[i] < ans[i]) {
                        for (int i = 1; i <= n; i++) {
                            ans[i] = res[i];
                        }
                        break;
                    } else if (res[i] > ans[i]) {
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
}
} // namespace SubtaskCycledTree
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    if (m == n - 1) {
        SubtaskTree::solve();
    } else {
        SubtaskCycledTree::solve();
    }
    return 0;
}
// Asusetic eru quionours.