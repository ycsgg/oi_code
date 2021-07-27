#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} Tr;
int n, k, tot, root, ans;
array<int, N> city, siz, mx, qfa, cur;
vector<int> node[N];
array<bool, N> vis, solved, vised;
void getrt(int x, int fa) {
    siz[x] = 1;
    mx[x]  = 0;
    for (auto v : Tr.edge[x]) {
        if (v == fa || vis[v])
            continue;
        getrt(v, x);
        siz[x] += siz[v];
        mx[x] = max(mx[x], siz[v]);
    }
    mx[x] = max(mx[x], tot - siz[x]);
    if (mx[x] < mx[root]) {
        root = x;
    }
}
void getsiz(int x, int fa) {
    siz[x] = 1;
    for (auto v : Tr.edge[x]) {
        if (v == fa || vis[v])
            continue;
        getsiz(v, x);
        siz[x] += siz[v];
    }
}

void getfa(int x, int fa) {
    qfa[x] = fa;
    cur[city[x]]++;
    for (auto v : Tr.edge[x]) {
        if (v == fa || vis[v])
            continue;
        getfa(v, x);
    }
}
void clear(int x, int fa) {
    qfa[x]          = 0;
    cur[city[x]]    = 0;
    solved[city[x]] = 0;
    vised[x]        = 0;
    for (auto v : Tr.edge[x]) {
        if (v == fa || vis[v])
            continue;
        clear(v, x);
    }
}
void calc(int x) {
    int flag = 0, cnt = 0;
    queue<int> q;
    getfa(x, 0);
    q.push(city[x]);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (solved[x])
            continue;
        solved[x] = true;
        ++cnt;
        if (cur[x] != node[x].size()) {
            flag = 1;
            break;
        }
        for (auto v : node[x]) {
            vised[v] = true;
        }
        for (auto v : node[x]) {
            for (int p = qfa[v]; p && !vised[p]; p = qfa[p]) {
                vised[p] = 1;
                q.push(city[p]);
            }
        }
    }
    if (!flag) {
        ans = min(ans, cnt);
    }
    clear(x, 0);
}
void solve(int x) {
    calc(x);
    vis[x] = 1;
    for (auto v : Tr.edge[x]) {
        if (vis[v])
            continue;
        getsiz(v, x);
        tot  = siz[v];
        root = 0;
        getrt(v, x);
        solve(root);
    }
}
int main() {
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> city[i];
        node[city[i]].push_back(i);
    }
    ans   = n;
    root  = 0;
    mx[0] = n;
    tot   = n;
    getrt(1, 0);
    solve(root);
    cout << ans - 1 << endl; //
    return 0;
}
// Asusetic eru quionours