### CF822F Madness

https://codeforces.com/problemset/problem/822/F

首先我们可以想到每个路径只选择一条边就是最优的

可以这样理解一下，因为如果一个路径包含多个边，那么这内部的一个端点上的计时器肯定不优于在这个端点上在加一个新的动点

因为一个点来回跑需要$2s$所以每个点最大显示实现最小就是$\dfrac{2}{deg}$，$deg$是这个点的度数

然后我们只要深搜贪心的构造一下最小值就好了

```cpp
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
```

