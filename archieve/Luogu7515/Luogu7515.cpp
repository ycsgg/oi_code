#include <cstring>
#include <deque>
#include <iostream>
using namespace std;
const int N   = 605;
const int MAX = 1e6;
int T;
int b[N][N];
int a[N][N];
int n, m;
struct Edge {
    int v;
    int w, nxt;
} edge[N * N * 2];
int head[N * N * 2], ecnt;
void init() {
    memset(a, 0, sizeof(a));
    memset(head, 0, sizeof(head));
    ecnt = 0;
}
void add(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
long long dis[N * 2];
int cnt[N * 2];
bool vis[N * 2];
bool spfa() {
    deque<int> q;
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    dis[1] = 0;
    q.push_back(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        ++cnt[x];
        vis[x] = 0;
        if (cnt[x] > n + m) {
            return false;
        }
        for (int i = head[x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dis[v] > dis[x] + edge[i].w) {
                dis[v] = dis[x] + edge[i].w;
                if (!vis[v]) {
                    if (!q.empty() && dis[v] < dis[q.front()]) {
                        q.push_front(v);
                    } else {
                        q.push_back(v);
                    }
                    vis[v] = 1;
                }
            }
        }
    }
    return true;
}
int main() {
    cin >> T;
    while (T--) {
        init();
        cin >> n >> m;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                cin >> b[i][j];
            }
        }
        for (int i = n; i >= 1; i--) {
            for (int j = m; j >= 1; j--) {
                a[i][j] = b[i][j] - a[i + 1][j] - a[i + 1][j + 1] - a[i][j + 1];
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if ((i + j) & 1) {
                    add(i, j + n, MAX - a[i][j]);
                    add(j + n, i, a[i][j]);
                } else {
                    add(i, j + n, a[i][j]);
                    add(j + n, i, MAX - a[i][j]);
                }
            }
        }
        if (!spfa()) {
            cout << "NO" << endl;
            continue;
        } else {
            cout << "YES" << endl;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    if ((i + j) & 1) {
                        a[i][j] -= dis[i];
                        a[i][j] += dis[j + n];
                    } else {
                        a[i][j] += dis[i];
                        a[i][j] -= dis[j + n];
                    }
                    cout << a[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
    return 0;
}