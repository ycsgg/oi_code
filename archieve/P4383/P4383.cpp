
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 700005;
struct Edge {
    int v;
    int w, nxt;
} edge[N];
int head[N], ecnt;
void newEdge(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, k;
struct Node {
    ll val;
    int cnt;
    Node operator+(const Node &b) const {
        return Node{val + b.val, cnt + b.cnt};
    }
    Node operator+(const int &b) const {
        return Node{val + b, cnt};
    }
    bool operator>(const Node &A) const {
        return val == A.val ? cnt > A.cnt : val > A.val;
    }
    bool operator<(const Node &b) const {
        return val == b.val ? cnt < b.cnt : val < b.val;
    }
} dp[N][3];
void solve(int x, int fa, int slope) {
    Node newEdge = {-slope, 1};
    for (int p = head[x]; p; p = edge[p].nxt)
        if (edge[p].v != fa) {
            int v = edge[p].v, w = edge[p].w;
            solve(v, x, slope);
            Node tmp =
                max(dp[x][2] + dp[v][0], dp[x][1] + dp[v][1] + w + newEdge);
            if (tmp > dp[x][2]) {
                dp[x][2] = tmp;
            }
            tmp = max(dp[x][1] + dp[v][0], dp[x][0] + dp[v][1] + w);
            if (tmp > dp[x][1]) {
                dp[x][1] = tmp;
            }
            dp[x][0] = dp[x][0] + dp[v][0];
        }
    dp[x][0] = max(dp[x][0], max(dp[x][2], dp[x][1] + newEdge));
}
bool check(int mid) {
    memset(dp, 0, sizeof(dp));
    solve(1, 0, mid);
    return dp[1][0].cnt >= k;
}
int main() {
    cin >> n >> k;
    k++;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        newEdge(u, v, w);
        newEdge(v, u, w);
    }
    ll l = (ll)-1e12, r = (ll)1e12;
    ll ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l   = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    memset(dp, 0, sizeof(dp));
    solve(1, 0, ans);
    cout << 1ll * dp[1][0].val + ans * k;
}


