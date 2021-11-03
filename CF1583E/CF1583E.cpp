#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 3e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G, Tr;
int n, m, q;
int a[N], b[N];
bool mark[N], vis[N];
void SpanningTree(int x) {
    vis[x] = 1;
    for (auto v : G.edge[x]) {
        if (vis[v]) {
            continue;
        }
        Tr.add(x, v);
        Tr.add(v, x);
        SpanningTree(v);
    }
}
bool flag;
void findPath(int x, int pre, int target, vector<int> &res) {
    res.push_back(x);
    if (x == target) {
        flag = 1;
        return;
    }
    for (auto v : Tr.edge[x]) {
        if (v == pre) {
            continue;
        }
        findPath(v, x, target, res);
        if (flag) {
            return;
        }
    }
    if (!flag) {
        res.pop_back();
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u);
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> a[i] >> b[i];
        mark[a[i]] ^= 1;
        mark[b[i]] ^= 1;
    }

    int tot = 0;
    for (int i = 1; i <= n; i++) {
        tot += mark[i];
    }
    if (tot == 0) {
        SpanningTree(1);
        cout << "Yes\n";
        for (int i = 1; i <= q; i++) {
            flag = 0;
            vector<int> res;
            findPath(a[i], 0, b[i], res);
            cout << res.size() << '\n';
            for (auto v : res) {
                cout << v << ' ';
            }
            cout << '\n';
        }
    } else {
        cout << "No\n";
        cout << tot / 2 << '\n';
    }
    return 0;
}
// Asusetic eru quionours.
