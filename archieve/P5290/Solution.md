### P5290 [十二省联考2019]春节十二响

看了半天先简化下题意

给定一棵树，点有点权，选定若干点集，点集中的点不能有祖先后代关系，点集的权值为所有点中点权最大值，问点集权值之和的最小值

考虑如果是一个根挂两条链，那么就是每一个链向另一侧匹配，可以开个堆，把最大的匹配起来

对于二叉树的话每个叶子节点都可以这么搞，搞完的话可以合并起来，然后向上回溯处理

多叉树同样

```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N = 2e5 + 5;
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
int id[N];
int n;
int m[N];
vector<int> tmp;
priority_queue<int> q[N];
void merge(int x, int y) {
    if (q[id[x]].size() < q[id[y]].size()) {
        swap(id[x], id[y]);
    }
    while (!q[id[y]].empty()) {
        tmp.push_back(max(q[id[x]].top(), q[id[y]].top()));
        q[id[x]].pop();
        q[id[y]].pop();
    }
    while (!tmp.empty()) {
        q[id[x]].push(tmp.back());
        tmp.pop_back();
    }
}
void dfs(int x) {
    for (int i = head[x]; i; i = edge[i].nxt) {
        dfs(edge[i].v);
        merge(x, edge[i].v);
    }
    q[id[x]].push(m[x]);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
        id[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        add(fa, i);
    }
    dfs(1);
    long long ans = 0;
    while (!q[id[1]].empty()) {
        ans += q[id[1]].top();
        q[id[1]].pop();
    }
    cout << ans;
    return 0;
}
```