#include <iostream>
using namespace std;
typedef long long ll;
const int p = 21;
const int N = 1 << 21;
struct Edge {
    int v;
    int nxt;
} edge[N];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
unsigned long long ans = 0;
ll a[N];
ll c[p][N];
ll dfs(int x, int dep) {
    ll res = a[x];
    for (int i = 0; i < p; i++) {
        c[i][(dep + a[x]) & ((1ll << i) - 1)] ^= (1ll << i);
    }
    for (int i = 0; i < p; i++) {
        res ^= c[i][dep & ((1ll << i) - 1)];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        res ^= dfs(v, dep + 1);
    }
    for (int i = 0; i < p; i++) {
        res ^= c[i][dep & ((1ll << i) - 1)];
    }
    ans += res;
    return res;
}
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        add(x, i);
    }
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}