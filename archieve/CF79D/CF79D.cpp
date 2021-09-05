#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 55e4 + 10;
int n, k, l;
int c[N], id[N], a[N];
int tot;
int dis[N];
int cost[40][40];
int dp[(1 << 20) + 10];
void SSSP(int S) {
    memset(dis, 0x3f, sizeof(dis));
    queue<int> q;
    dis[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 1; i <= l; i++) {
            int v = x + a[i];
            if (v <= n + 1 && dis[v] == 0x3f3f3f3f) {
                dis[v] = dis[x] + 1;
                q.push(v);
            }
            v = x - a[i];
            if (v >= 1 && dis[v] == 0x3f3f3f3f) {
                dis[v] = dis[x] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        if (~id[i]) {
            cost[id[S]][id[i]] = dis[i];
        }
    }
}
int main() {
    cin >> n >> k >> l;
    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        c[x] = 1;
    }
    for (int i = 1; i <= l; i++) {
        cin >> a[i];
    }
    for (int i = n + 1; i >= 1; i--) {
        c[i] ^= c[i - 1];
    }
    for (int i = 1; i <= n + 1; i++) {
        if (c[i]) {
            id[i] = tot++;
        } else {
            id[i] = -1;
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        if (c[i]) {
            SSSP(i);
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int S = 0; S < (1 << tot); S++) {
        if (dp[S] == 0x3f3f3f3f) {
            continue;
        }
        for (int j = 0; j < tot; j++) {
            if (S & (1 << j)) {
                continue;
            }
            for (int k = j + 1; k < tot; k++) {
                if (!(S & (1 << k))) {
                    dp[S + (1 << j) + (1 << k)] =
                        min(dp[S + (1 << j) + (1 << k)], dp[S] + cost[j][k]);
                }
            }
        }
    }
    int ans = dp[(1 << tot) - 1];
    if (ans == 0x3f3f3f3f) {
        ans = -1;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours.