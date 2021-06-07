### P6348 [PA2011]Journeys

线段树优化建图裸题

开两个线段树 $in,out$ 一个连出边一个入边

```cpp
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 5e5 + 10;
int n, m, S;
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
    void build(int &rt, int l, int r) {
        if (l == r) {
            rt = l;
            return;
        }
        if (!rt) {
            rt = ++tot;
        }
        int mid = (l + r) / 2;
        build(ls[rt], l, mid);
        if (typ == OUT)
            G.add(rt, ls[rt], 0);
        else
            G.add(ls[rt], rt, 0);
        build(rs[rt], mid + 1, r);
        if (typ == OUT)
            G.add(rt, rs[rt], 0);
        else
            G.add(rs[rt], rt, 0);
    }
    void add(int rt, int l, int r, int L, int R, int z) {
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
            add(ls[rt], l, mid, L, R, z);
        }
        if (mid < R) {
            add(rs[rt], mid + 1, r, L, R, z);
        }
    }
} in, out;
int ls[N * 8], rs[N * 8];
int dis[N * 4];
void Dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    deque<int> q;
    dis[S] = 0;
    q.push_front(S);
    while (!q.empty()) {
        int now = q.front();
        q.pop_front();
        for (auto e : G.edge[now]) {
            int v = e.v, w = e.w;
            if (dis[v] > dis[now] + w) {
                dis[v] = dis[now] + w;
                if (w)
                    q.push_back(v);
                else
                    q.push_front(v);
            }
        }
    }
}
int main() {
    cin >> n >> m >> S;
    tot = n;
    in.setType(SegmentTree::Type::IN);
    out.setType(SegmentTree::Type::OUT);
    in.rt  = 0;
    out.rt = 0;
    in.build(in.rt, 1, n);
    out.build(out.rt, 1, n);
    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int x, y;
        x = ++tot;
        y = ++tot;
        G.add(x, y, 1);
        in.add(in.rt, 1, n, a, b, x);
        out.add(out.rt, 1, n, c, d, y);
        x = ++tot;
        y = ++tot;
        G.add(x, y, 1);
        in.add(in.rt, 1, n, c, d, x);
        out.add(out.rt, 1, n, a, b, y);
    }
    Dijkstra();
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << endl;
    }
    return 0;
}
// Asusetic eru quionours
```