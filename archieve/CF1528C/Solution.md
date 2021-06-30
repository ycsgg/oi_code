### CF1528C Trees of Tranquillity

有意思的题

考虑如果我们对树 $2$ 搞出来欧拉序，然后就变成了找到最多的区间在树 $1$ 上有包含关系而树 $2$ 上没有

如果一个区间和别的都不相交直接加入，如果被包含就删掉包含他的，如果包含别人就去掉不要

开一个 set/线段树 维护均可，一边回溯一遍统计，复杂度 $O(n\log n)$

```cpp

#include <array>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
const int N = 3e5 + 10;
int T, n, tim;
enum { WORSE, CONTAINS, DISJOINT };
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
    auto &operator[](int x) {
        return edge[x];
    }
    auto operator[](int x) const {
        return edge[x];
    }
} Tr1, Tr2;
array<int, N * 2> st, ed;
void dfs(int x, int fa, const Graph &G) {
    st[x] = ++tim;
    for (auto v : G[x]) {
        if (v == fa)
            continue;
        dfs(v, x, G);
    }
    ed[x] = ++tim;
}
set<pair<int, int>> p;
auto get(int x) {
    auto it = p.lower_bound(make_pair(st[x], x));
    if (it != p.end() && ed[it->second] < ed[x]) {
        return make_pair(WORSE, 0);
    }
    if (it != p.begin()) {
        it--;
        if (ed[it->second] > ed[x]) {
            return make_pair(CONTAINS, it->second);
        }
    }
    return make_pair(DISJOINT, 0);
}
int ans = -1;
void solve(int x, int fa, const Graph &G) {
    auto [State, id] = get(x);
    if (id) {
        p.erase(make_pair(st[id], id));
    }
    if (State != WORSE) {
        p.insert(make_pair(st[x], x));
    }
    ans = max(ans, (int)p.size());
    for (auto v : G[x]) {
        if (v == fa)
            continue;
        solve(v, x, G);
    }
    if (id) {
        p.insert(make_pair(st[id], id));
    }
    if (State != WORSE) {
        p.erase(make_pair(st[x], x));
    }
}
void clear() {
    p.clear();
    ans = 0;
    tim = 0;
    for (int i = 1; i <= n; i++) {
        Tr1.edge[i].clear();
        st[i] = ed[i] = 0;
        Tr2.edge[i].clear();
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        clear();
        cin >> n;
        for (int i = 2; i <= n; i++) {
            int _fa;
            cin >> _fa;
            Tr1.add(_fa, i);
            Tr1.add(i, _fa);
        }
        for (int i = 2; i <= n; i++) {
            int _fa;
            cin >> _fa;
            Tr2.add(_fa, i);
            Tr2.add(i, _fa);
        }
        dfs(1, 0, Tr2);
        solve(1, 0, Tr1);
        cout << ans << endl;
    }
    cout.flush();
    return 0;
}
// Asusetic eru quionours
```

#欧拉序

 