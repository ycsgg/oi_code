#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 2e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} Tr;
int n;
ll dp[N][3];
void dfs(int x) {
    bool flag = 0;
    ll prod = 1;
    ll xprod = 1;
    dp[x][2] = 1;
    for (auto v : Tr.edge[x]) {
        flag = 1;
        dfs(v);
        dp[x][1] = (dp[x][1] * (dp[v][0] + 2 * dp[v][1] + dp[v][2]) +
                    dp[x][0] * (dp[v][0] + dp[v][1])) %
                   mod;
        dp[x][0] = (dp[x][0] * (dp[v][1] + dp[v][2]) +
                    dp[x][2] * (dp[v][0] + dp[v][1])) %
                   mod;
        dp[x][2] = dp[x][2] * (dp[v][1] + dp[v][2]) % mod;
    }
    if (!flag) {
        dp[x][0] = dp[x][2] = 0;
        dp[x][1] = 1;
    }
}
int main() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        Tr.add(x, i);
    }
    dfs(1);
    cout << (dp[1][1] + dp[1][2]) % mod;
    return 0;
}
// Asusetic eru quionours.