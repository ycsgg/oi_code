#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
using ll    = long long;
struct Graph {
    struct Node {
        int v;
        ll w;
    };
    vector<Node> edge[N];
    void add(int u, int v, ll w) {
        edge[u].push_back(Node{v, w});
    }
} G, revG, DAG;
int n, m, s;
array<ll, N> dis;
void SP(const Graph &G, const int &S) {
    dis.fill((1ll << 60));
    dis[S] = 0;
    priority_queue<pair<ll, int>> q;
    q.push(make_pair(0, S));
    while (!q.empty()) {
        auto [d, x] = q.top();
        q.pop();
        d = -d;
        if (d != dis[x])
            continue;
        for (auto e : G.edge[x]) {
            if (dis[x] + e.w < dis[e.v]) {
                dis[e.v] = dis[x] + e.w;
                q.push(make_pair(-dis[e.v], e.v));
            }
        }
    }
}
array<int, N> in;
int main() {
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add(u, v, w);
        G.add(v, u, w);
    }
    SP(G, s);
    for (int i = 1; i <= n; i++) {
        if (dis[i] == (1ll << 60))
            continue;
        for (auto e : G.edge[i]) {
            if (dis[i] + e.w == dis[e.v]) {
                DAG.add(i, e.v, -1);
                in[e.v]++;
                revG.add(e.v, i, -1);
            }
        }
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            q.push(i);
        }
    }
    vector<int> topo;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        topo.push_back(v);
        for (auto e : DAG.edge[v]) {
            auto &v = e.v;
            --in[v];
            if (!in[v]) {
                q.push(v);
            }
        }
    }
    vector<int> id(n + 1), siz(n + 1);
    for (int i = 1; i <= n; i++) {
        id[i]  = i;
        siz[i] = 1;
    }
    for (auto x : topo) {
        if (x == s) {
            continue;
        }
        int pq = 0;
        for (auto e : revG.edge[x]) {
            if (!pq && e.v != s) {
                pq = id[e.v];
            } else {
                if (pq != id[e.v]) {
                    pq = -1;
                }
            }
        }
        if (pq && (~pq)) {
            id[x] = pq;
            siz[pq]++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i != s && dis[i] != (1ll << 60)) {
            ans = max(ans, siz[id[i]]);
        }
    }
    cout << ans << endl;
}
//Asusetic eru quionours
