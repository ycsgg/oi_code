#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
};
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
int T;
int main() {
    cin >> T;
    while (T--) {
        int n, m, k;
        Graph G;
        cin >> n >> m >> k;
        for (int i = 1; i <= m; i++) {
            int x, y, w;
            cin >> x >> y >> w;
            G.add(x, y, w);
        }
        vector<int> nodes(k + 1);
        for (int i = 1; i <= k; i++) {
            cin >> nodes[i];
        }
        long long ans = (1ll << 60);
        Graph G1;
        int S = 0, T = n + 1;
        for (int pos = 0; (1 << pos) <= k; pos++) {
            G1 = G;
            for (int i = 1; i <= k; i++) {
                if (i & (1 << pos)) {
                    G1.add(S, nodes[i], 0);
                } else {
                    G1.add(nodes[i], T, 0);
                }
            }
            ans = min(ans, ShortestPath::Dijkstra(S, T, G1));
            G1 = G;
            for (int i = 1; i <= k; i++) {
                if (i & (1 << pos)) {
                    G1.add(nodes[i], T, 0);
                } else {
                    G1.add(S, nodes[i], 0);
                }
            }
            ans = min(ans, ShortestPath::Dijkstra(S, T, G1));
        }
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours