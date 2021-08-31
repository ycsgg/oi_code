#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e4 + 10;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} Tr;
int n;
int cnt[N], dis[N], siz[N];
bool vis[N];
void getdep(int x, int _fa) {
    cnt[dis[x]]++;
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        auto w = e.w;
        if (v == _fa || vis[v])
            continue;
        dis[v] = (dis[x] + w) % 3;
        getdep(v, x);
    }
}
int rt, mmax[N];
int calc(int u, int p) {
    cnt[0] = cnt[1] = cnt[2] = 0;
    dis[u] = p;
    getdep(u, 0);
    return cnt[1] * cnt[2] * 2 + cnt[0] * cnt[0];
}
void getrt(int x, int _fa, int tot) {
    siz[x] = 1;
    mmax[x] = 0;
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        auto w = e.w;
        if (v == _fa || vis[v]) {
            continue;
        }
        getrt(v, x, tot);
        siz[x] += siz[v];
        mmax[x] = max(mmax[x], siz[v]);
    }
    mmax[x] = max(mmax[x], tot - siz[x]);
    if (mmax[x] < mmax[rt]) {
        rt = x;
    }
}
int ans = 0;
void solve(int x) {
    ans += calc(x, 0);
    vis[x] = 1;
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        auto w = e.w;
        if (vis[v])
            continue;
        ans -= calc(v, w);
        rt = 0;
        getrt(v, 0, siz[v]);
        solve(rt);
    }
}
int gcd(int a, int b) {
    return (!b) ? a : gcd(b, a % b);
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        Tr.add(x, y, w % 3);
        Tr.add(y, x, w % 3);
    }
    mmax[0] = n;
    getrt(1, 0, n);
    solve(rt);
    int g = gcd(ans, n * n);
    cout << ans / g << "/" << n * n / g << endl;
    return 0;
}
// Asusetic eru quionours