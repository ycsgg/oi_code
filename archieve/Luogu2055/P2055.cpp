
#include <cstring>
#include <iostream>

using namespace std;
const int N = 105, M = 10050;
int T, n, tot;
bool stu[N], back[N];
struct Edge {
  int v;
  int nxt;
} edge[M];
int head[N], ecnt;
bool vis[N];
void add(int u, int v) {
  edge[++ecnt].v = v;
  edge[ecnt].nxt = head[u];
  head[u] = ecnt;
}
void init() {
  memset(head, 0, sizeof(head));
  memset(edge, 0, sizeof(edge));
  tot = 0;
}
int link[N];
bool dfs(int x) {
  for (int i = head[x]; i; i = edge[i].nxt) {
    int v = edge[i].v;
    if (!vis[v]) {
      vis[v] = 1;
      if (!link[v] || dfs(link[v])) {
        link[v] = x;
        return 1;
      }
    }
  }
  return 0;
}
int MaxMatch() {
  memset(link, 0, sizeof(link));
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if ((stu[i] && (!back[i])) || (!stu[i])) {
      memset(vis, 0, sizeof(vis));
      if (dfs(i)) {
        ans++;
      }
    }
  }
  return ans;
}
int main() {
  cin >> T;
  while (T--) {
    init();
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> stu[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> back[i];
      if ((!back[i]) && stu[i]) {
        add(i, i);
      }
    }
    for (int i = 1; i <= n; i++) {
      if ((!stu[i]) || (!back[i])) {
        ++tot;
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int tmp;
        cin >> tmp;
        if (tmp && stu[j]) {
          add(i, j);
        }
      }
    }
    int res = MaxMatch();
    if (res == tot) {
      cout << "^_^" << endl;
    } else {
      cout << "T_T" << endl;
    }
  }
}
