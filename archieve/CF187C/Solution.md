### CF187C Weak Memory

这题显然没紫题难度，最多绿

既然让能量最小可以考虑二分答案变成可行性问题

因为操作只会$-1$或者补满，所以某个点当前能量最大一定“有利于”接下来点的转移

那就二分最小能量跑$bfs$即可

```cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 100010;
struct Edge {
    int v;
    int nxt;
} edge[N * 4];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int pos[N];
int dis[N];
int n, m, k, s, t;
struct Data {
    int x, w;
    bool operator<(const Data &b) const {
        return w < b.w;
    }
};
priority_queue<Data> q;
bool check(int x) {
    while (!q.empty())
        q.pop();
    memset(dis, -1, sizeof(dis));
    dis[s] = x;
    q.push({s, x});
    while (!q.empty()) {
        Data now = q.top();
        q.pop();
        if (now.w == 0) {
            continue;
        }
        for (int i = head[now.x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            int w = now.w - 1;
            if (v == t)
                return true;
            if (pos[v]) {
                w = x;
            }
            if (dis[v] < w) {
                dis[v] = w;
                q.push({v, w});
            }
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int tmp;
        cin >> tmp;
        pos[tmp] = 1;
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    cin >> s >> t;
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
}
```

