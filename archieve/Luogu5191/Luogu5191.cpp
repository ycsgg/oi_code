#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1005;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G;
int d, m, n;
int deg[N];
bitset<N> to[N], need[N], mark;
void dfs(int x, int id) {
    if (to[id][x]) {
        return;
    }
    to[id][x] = 1;
    for (auto v : G.edge[x]) {
        dfs(v, id);
    }
}
int main() {
    cin >> d >> m >> n;
    for (int i = 1; i <= d; i++) {
        need[i].set();
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G.add(u, v);
        deg[v]++;
    }
    for (int i = 1; i <= d; i++) {
        dfs(i, i);
    }
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mark[x] = 1;
        for (int j = 1; j <= d; j++) {
            if (!deg[j] && to[j][x]) {
                need[x] &= to[j];
            }
        }
        mark |= need[x];
    }
    for (int i = 1; i <= d; i++) {
        if (mark[i]) {
            cout << i << ' ';
        }
    }
    return 0;
}
// Asusetic eru quionours.