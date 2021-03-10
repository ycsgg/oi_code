### P4383 [八省联考2018]林克卡特树

wqs二分/dp凸优化

先考虑朴素的树形dp

$dp_{i,0}$表示$i$子树内的链不经过$i$
$dp_{i,1}$表示$i$子树内的链有一个端点经过$i$
$dp_{i,2}$表示$i$子树内的链有一个$lca$经过$i$

转移的时候需要考虑路径条数的变化

然后这个东西是$O(nk)$的

需要优化，打表可知（不会证）发现$f(x)$是凸函数，也就是它的图像在平面上构成凸包

我们想求特定的$f(k)$，但是如果我们做一个直线切凸包，从上至下扫到第一个点，那我们可以方便的求出这个点，并且可以确定它在$(k,f(k))$的左右

如果是左，那么减小斜率，反之增大（这里是图）

求切点坐标

为了找到最高的切点，我们需最大化$y=kx+b$中的$b$，我们将$(x,f(x))$下平移至$(x,f(x)-kx)$，这仍然是凸包且最高点即切点

题目中就是把每个收益减去斜率，不考虑选取限制的求最大收益，并得到此时的选取个数，根据这个个数和限制个数改变斜率

于是我们就可以愉快的二分了

```cpp
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
```

