
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, u[N], v[N], head[N], deg[N], ecnt, To[N];
double ans[N];
struct Edge {
    int v, nxt;
} edge[N * 2];
void add(int x, int y) {
    edge[++ecnt].v = y;
    edge[ecnt].nxt = head[x];
    head[x]        = ecnt;
}
void dfs(int x, int fa, double lst) {
    double time = 2.0 / deg[x];
    for (int i = head[x]; i; i = edge[i].nxt) {
        if (edge[i].v != fa) {
            lst += time;
            while (lst > 2) {
                lst -= 2;
            }
            int id = (i + 1) / 2;
            if (lst <= 1) {
                To[id] = x, ans[id] = lst;
            } else {
                To[id] = edge[i].v, ans[id] = lst - 1;
            }
            dfs(edge[i].v, x, lst + 1);
        }
    }
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u[i] >> v[i];
        add(u[i], v[i]);
        add(v[i], u[i]);
        deg[u[i]]++;
        deg[v[i]]++;
    }
    dfs(1, -1, 0);
    cout << n - 1 << endl;
    for (int i = 1; i < n; i++) {
        printf("1 %d %d %d %.8lf\n", i, u[i] + v[i] - To[i], To[i], ans[i]);
    }
    return 0;
}


