
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN = 110;
const int MAXE = 10010;
struct Edge {
  int v, nxt, w1, w2;
} edge[MAXE];
bool f[MAXN][MAXE], g[MAXN][MAXE], vis[MAXN];
int n, m, tot;
int head[MAXN], in[MAXN];
void add(int u, int v, int w1, int w2) {
  edge[++tot].nxt = head[u];
  edge[tot].v = v;
  edge[tot].w1 = w1;
  edge[tot].w2 = w2;
  head[u] = tot;
}
queue<int> q;
int main() {
  scanf("%d%d", &n, &m);
  for (int x, y, a, b, i = 1; i <= m; ++i) {
    scanf("%d%d%d%d", &a, &b, &x, &y);
    add(a, b, x, y);
    ++in[b];
  }
  for (int i = 1; i <= n; ++i) {
    if (!in[i]) {
      q.push(i);
    }
  }
  f[1][0] = g[1][0] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = edge[i].nxt) {
      int w1 = edge[i].w1, w2 = edge[i].w2, v = edge[i].v;
      for (int j = 0; j + w1 < MAXE; ++j)
        f[v][j + w1] |= f[u][j];
      for (int j = 0; j + w2 < MAXE; ++j)
        g[v][j + w2] |= g[u][j];
      in[v]--;
      if (!in[v])
        q.push(v);
    }
  }
  for (int i = 0; i < MAXE; ++i)
    if (f[n][i] && g[n][i]) {
      printf("%d", i);
      return 0;
    }
  printf("IMPOSSIBLE");
  return 0;
}
