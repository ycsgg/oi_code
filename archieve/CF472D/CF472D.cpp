
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2005;
struct Edge {
  int u, v, w, nxt;
} graph[N * N], tree[N];
bool cmp(const Edge &a, const Edge &b) { return a.w < b.w; }
int graph_head[N], tree_head[N], gcnt, tcnt;
void add(int u, int v, int w, Edge *Eset, int *Ehead, int &Ecnt) {
  Eset[++Ecnt].v = v;
  Eset[Ecnt].w = w;
  Eset[Ecnt].u = u;
  Eset[Ecnt].nxt = Ehead[u];
  Ehead[u] = Ecnt;
}
int g[N][N];
int n;
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool used[N * N];
int dis[N][N];
void dfs(int x, int fa, int s) {
  for (int i = tree_head[x]; i; i = tree[i].nxt) {
    int v = tree[i].v;
    if (v == fa)
      continue;
    dis[s][v] = dis[s][x] + tree[i].w;
    dfs(v, x, s);
  }
}
int main() {
  bool flag = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &g[i][j]);
      if (!flag && g[i][j]) {
        flag = 1;
      }
      if (i < j) {
        add(i, j, g[i][j], graph, graph_head, gcnt);
      } else if (i == j) {
        if (g[i][j]) {
          cout << "NO";
          return 0;
        }
      } else {
        if (g[i][j] != g[j][i]) {
          cout << "NO" << endl;
          return 0;
        }
      }
    }
  }
  if (n != 1 && !flag) {
    cout << "NO" << endl;
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
  }
  sort(graph + 1, graph + 1 + gcnt, cmp);
  for (int i = 1; i <= gcnt; i++) {
    int u = find(graph[i].u), v = find(graph[i].v);
    if (u != v) {
      add(graph[i].u, graph[i].v, graph[i].w, tree, tree_head, tcnt);
      add(graph[i].v, graph[i].u, graph[i].w, tree, tree_head, tcnt);
      fa[u] = v;
      used[i] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    dfs(i, 0, i);
  }
  for (int i = 1; i <= gcnt; i++) {
    if (!used[i]) {
      int u = graph[i].u;
      int v = graph[i].v;
      if (dis[u][v] != graph[i].w) {
        cout << "NO" << endl;
        return 0;
      }
    }
  }
  cout << "YES" << endl;
  return 0;
}
