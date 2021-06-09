#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 5e4 + 10;
int n, m, k;
int tot;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N * 8];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
struct SegmentTree {
    int ls[N * 4], rs[N * 4];
    enum Type { IN, OUT };
    Type typ;
    int rt;
    void setType(Type tp) {
        typ = tp;
    }
    void _build(int &rt, int l, int r) {
        if (l == r) {
            rt = l;
            return;
        }
        if (!rt) {
            rt = ++tot;
        }
        int mid = (l + r) / 2;
        _build(ls[rt], l, mid);
        if (typ == OUT)
            G.add(rt, ls[rt], 0);
        else
            G.add(ls[rt], rt, 0);
        _build(rs[rt], mid + 1, r);
        if (typ == OUT)
            G.add(rt, rs[rt], 0);
        else
            G.add(rs[rt], rt, 0);
    }
    void build(int l, int r) {
        rt = 0;
        _build(rt, l, r);
    }
    void _add(int rt, int l, int r, int L, int R, int z) {
        if (l >= L && r <= R) {
            if (typ == OUT) {
                G.add(z, rt, 0);
            } else {
                G.add(rt, z, 0);
            }
            return;
        }
        int mid = (l + r) / 2;
        if (L <= mid) {
            _add(ls[rt], l, mid, L, R, z);
        }
        if (mid < R) {
            _add(rs[rt], mid + 1, r, L, R, z);
        }
    }
    void add(int l, int r, int p) {
        _add(rt, 1, n, l, r, p);
    }
} in, out;
int dis[N * 4][11];
int vis[N * 4][11];
struct Node {
    int v, dis, cnt;
    const bool operator<(const Node &B) const {
        return dis > B.dis;
    }
};
void Dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<Node> q;
    dis[1][0] = 0;
    q.push(Node{1, dis[1][0], 0});
    while (!q.empty()) {
        Node p = q.top();
        q.pop();
        int now = p.v;
        int cnt = p.cnt;
        if (vis[now][cnt])
            continue;
        vis[now][cnt] = 1;
        for (auto e : G.edge[now]) {
            int v = e.v, w = e.w;
            if (dis[v][cnt] > dis[now][cnt] + w) {
                dis[v][cnt] = dis[now][cnt] + w;
                q.push(Node{v, dis[v][cnt], cnt});
            }
            if (cnt < k && dis[v][cnt + 1] > dis[now][cnt]) {
                dis[v][cnt + 1] = dis[now][cnt];
                q.push(Node{v, dis[v][cnt + 1], cnt + 1});
            }
        }
    }
}
int main() {
    cin >> n;
    cin >> n >> m >> k;
    tot = n;
    in.setType(SegmentTree::Type::IN);
    out.setType(SegmentTree::Type::OUT);
    in.build(1, n);
    out.build(1, n);
    for (int i = 1; i <= m; i++) {
        int a, b, c, d, w;
        cin >> a >> b >> c >> d >> w;
        int x, y;
        x = ++tot;
        y = ++tot;
        G.add(x, y, w);
        in.add(a, b, x);
        out.add(c, d, y);
        x = ++tot;
        y = ++tot;
        G.add(x, y, w);
        in.add(c, d, x);
        out.add(a, b, y);
    }
    Dijkstra();
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++) {
        ans = min(ans, dis[n][i]);
    }
    if (ans >= 0x3f3f3f3f) {
        cout << "CreationAugust is a sb!" << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours