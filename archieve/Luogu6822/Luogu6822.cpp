#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 4e5 + 5;
int n, m;
struct Graph {
    struct Node {
        int u, v;
        long long w;
        int id;
        const bool operator<(const Node &B) const {
            return w < B.w;
        }
    };
    vector<Node> edge[N];
    void add(int u, int v, long long w, int id) {
        edge[u].push_back(Node{u, v, w, id});
    }
    void add(int u, int v, int w) {
        edge[u].push_back(Node{u, v, w, -1});
    }
} G, G1;
namespace ShortestPath {
vector<long long> dis;
const long long INF = (1ll << 35);
struct Node {
    int id;
    long long dis;
    const bool operator<(const Node &B) const {
        return dis < B.dis;
    }
};
long long Dijkstra(const int S, const int T, const Graph &G) {
    dis.resize(N + 5);
    dis.assign(N + 5, INF);
    dis[S] = 0;
    priority_queue<Node> q;
    q.push(Node{S, -dis[S]});
    while (!q.empty()) {
        Node now = q.top();
        q.pop();
        for (auto e : G.edge[now.id]) {
            int v = e.v;
            if (e.w + dis[now.id] < dis[v]) {
                dis[v] = e.w + dis[now.id];
                q.push(Node{v, -dis[v]});
            }
        }
    }
    return dis[T];
}
} // namespace ShortestPath

int main() {
    cin >> n >> m;
    int s  = 0, t;
    int id = 0;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G.add(a, b, c, ++id);
        G.add(b, a, c, ++id);
    }
    t = id + 1;
    for (int i = 1; i <= n; i++) {
        sort(G.edge[i].begin(), G.edge[i].end());
        for (int j = 1; j < G.edge[i].size(); j++) {
            G1.add(G.edge[i][j].id, G.edge[i][j - 1].id, 0);
            G1.add(G.edge[i][j - 1].id, G.edge[i][j].id,
                   G.edge[i][j].w - G.edge[i][j - 1].w);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (auto e : G.edge[i]) {
            int v    = e.v;
            auto pos = lower_bound(G.edge[v].begin(), G.edge[v].end(), e);
            if (pos > G.edge[v].begin()) {
                G1.add(e.id, (pos - 1)->id, e.w);
            }
            if (pos != G.edge[v].end()) {
                G1.add(e.id, pos->id, pos->w);
            }
        }
    }
    for (auto e : G.edge[1]) {
        G1.add(s, e.id, e.w);
    }
    for (auto e : G.edge[n]) {
        G1.add(e.id, t, 0);
    }
    cout << ShortestPath::Dijkstra(s, t, G1);
    return 0;
}
// Asusetic eru quionours