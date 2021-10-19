#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} Tr;
int n, k;
int in[N];
int tot;
int dfs(int x, int _fa) {
    if (in[x] == 1) {
        return 0;
    }
    vector<int> tmp;
    for (auto v : Tr.edge[x]) {
        if (v == _fa) {
            continue;
        }
        tmp.push_back(dfs(v, x) + 1);
    }
    sort(tmp.begin(), tmp.end());
    auto it = tmp.rbegin();
    for (; next(it) != tmp.rend(); it++) {
        if (*it + *next(it) <= k) {
            break;
        }
        tot++;
    }
    return *it;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
        in[v]++;
        in[u]++;
    }
    int rt = 1;
    tot = 1;
    for (int i = 1; i <= n; i++) {
        if (in[i] > 1) {
            dfs(i, 0);
            break;
        }
    }
    cout << tot;
    return 0;
}
// Asusetic eru quionours.