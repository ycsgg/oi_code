
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 500005;
struct Edge {
  int v;
  int nxt;
} edge[N * 4];
int head[N], ecnt;
void add(int u, int v) {
  edge[++ecnt].v = v;
  edge[ecnt].nxt = head[u];
  head[u] = ecnt;
}
bool vis[N];
int ans[N], cnt;
int n, m, k;
int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    add(u, v);
    add(v, u);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      ans[++cnt] = i;
      vis[i] = 1;
      for (int j = head[i]; j; j = edge[j].nxt) {
        vis[edge[j].v] = 1;
        for (int k = head[edge[j].v]; k; k = edge[k].nxt) {
          vis[edge[k].v] = 1;
        }
      }
    }
  }
  cout << cnt << endl;
  for (int i = 1; i <= cnt; i++) {
    cout << ans[i] << " ";
  }
}
