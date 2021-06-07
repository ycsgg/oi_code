#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define row(x) x
#define col(x) x + r
const int N = 2e6 + 1e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G;
struct Node {
    int x, y, typ;
} a[100005];
const int dx[] = {1, 0, -1, 0, 1, 1, -1, -1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};
int n, r, c;
int find(int x, int y) {
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if ((a[mid].x == x) && (a[mid].y == y)) {
            return mid;
        }
        if (a[mid].x < x || (a[mid].x == x && a[mid].y < y)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}
int dfn[N], low[N], dfn_id, siz[N];
bool vis[N];
int st[N], top;
int scc_cnt, scc[N];
void tarjan(int x, const Graph &G) {
    dfn[x] = low[x] = ++dfn_id;
    st[++top]       = x;
    vis[x]          = 1;
    for (auto v : G.edge[x]) {
        if (!dfn[v]) {
            tarjan(v, G);
            low[x] = min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = min(low[x], dfn[v]);
        }
    }
    if (low[x] == dfn[x]) {
        scc_cnt++;
        int now = 0;
        do {
            now      = st[top];
            vis[now] = 0;
            scc[now] = scc_cnt;
            siz[scc_cnt] += (now > r + c);
            top--;
        } while (now != x);
    }
}
set<pair<int, int>> g;
int in[N];
int dp[N];
int main() {
    cin >> n >> r >> c;
    int tot = r + c;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].typ;
    }
    sort(a + 1, a + 1 + n, [&](const Node &A, const Node &B) -> bool {
        if (A.x == B.x) {
            return A.y < B.y;
        }
        return A.x < B.x;
    });
    for (int i = 1; i <= n; i++) {
        G.add(row(a[i].x), tot + i);
        G.add(col(a[i].y), tot + i);
        if (a[i].typ == 1) {
            G.add(tot + i, row(a[i].x));
        } else if (a[i].typ == 2) {
            G.add(tot + i, col(a[i].y));
        } else {
            for (int k = 0; k < 8; k++) {
                int nx = a[i].x + dx[k];
                int ny = a[i].y + dy[k];
                if (nx >= 1 && nx <= r && ny >= 1 && ny <= c) {
                    int p = find(nx, ny);
                    if (p != -1) {
                        G.add(i + tot, tot + p);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= tot + n; i++) {
        if (!dfn[i]) {
            tarjan(i, G);
        }
    }
    for (int i = 1; i <= tot + n; i++) {
        for (auto p : G.edge[i]) {
            if (scc[i] != scc[p] && !g.count(make_pair(scc[i], scc[p]))) {
                g.insert(make_pair(scc[i], scc[p]));
            }
        }
        G.edge[i].clear();
    }
    for (auto e : g) {
        G.add(e.first, e.second);
        in[e.second]++;
        // cout << "P" << endl;
    }
    queue<int> q;
    for (int i = 1; i <= scc_cnt; i++) {
        // cout << in[i] << endl;
        if (!in[i]) {
            q.push(i);
            dp[i] = siz[i];
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto v : G.edge[x]) {
            dp[v] = max(dp[v], dp[x] + siz[v]);
            --in[v];
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours
