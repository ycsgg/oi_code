
#include <iostream>
using namespace std;
#ifdef DEBUG
#define Err(a) std::cerr << " >>| " << (a) << endl
#else
#define Err(a) 
#endif
const int N = 5005, M = 10050;
struct Edge {
    int u, v;
    int nxt;
} edge[M * 2];
int head[N], ecnt=1;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].u   = u;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, m;
int dfn[N], low[N], dcc[N], tot, dcc_cnt;
int in[N];
int bridge[M];
void tarjan(int x, int eid) {
    dfn[x] = low[x] = ++tot;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            tarjan(v, i);
            low[x] = min(low[x], low[v]);
            if (dfn[x] < low[v]) {
                bridge[i] = bridge[i ^ 1] = 1;
            }
        } else if (i != (eid ^ 1)) {
            low[x] = min(low[x], dfn[v]);
        }
    }
}
void dfs(int x) {
    dcc[x] = dcc_cnt;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (dcc[v] != 0 || bridge[i] == 1) {
            continue;
        }
        dfs(v);
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    tarjan(1,0);
    for (int i = 1; i <= n; i++) {
        if (!dcc[i]) {
            dcc_cnt++;
            dfs(i);
        }
    }
    for (int i = 1; i <= m; i++) {
        Err(dcc[edge[i * 2].u]);
        Err(dcc[edge[i * 2].v]);
        if (dcc[edge[i * 2].u] != dcc[edge[i * 2].v]) {
            in[dcc[edge[i * 2].u]]++;
            in[dcc[edge[i * 2].v]]++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= dcc_cnt; i++) {
        if (in[i] == 1) {
            ans++;
        }
    }
    cout << (ans + 1) / 2;
}


