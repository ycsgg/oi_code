### CF888G Xor-MST

看到生成树就想到Kruskal，看到异或就想到01Trie ~~中国人的想象力惟在这一层能够如此跃进~~

每次选取边权最小的两个点连起来连通块连起来肯定是对的

所以问题就是当前图中两个连通块间最小边权是谁

插到 01 Trie 里发现叶子节点是要两两连边的

边权最小就是LCA深度最小的，因为肯定要尽量让高位是 $0$

所以沿着 Trie 搜下去对可以成为 LCA 的点找合并两颗子树就好

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int n;
int a[N];
namespace Trie {
int ch[N * 20 + 10][2], cnt, rt = 0;
void insert(int x) {
    int now = rt;
    for (int i = 30; i >= 0; i--) {
        int d = (x >> i) & 1;
        if (!ch[now][d]) {
            ch[now][d] = ++cnt;
        }
        now = ch[now][d];
    }
}
int find(int p1, int p2, int d) {
    if (d < 0)
        return 0;
    int res0 = -1, res1 = -1;
    if (ch[p1][0] && ch[p2][0]) {
        res0 = find(ch[p1][0], ch[p2][0], d - 1);
    }
    if (ch[p1][1] && ch[p2][1]) {
        res1 = find(ch[p1][1], ch[p2][1], d - 1);
    }
    if (res0 != -1 || res1 != -1) {
        if (res0 != -1 && res1 != -1) {
            return min(res0, res1);
        }
        return res0 + res1 + 1;
    }
    if (ch[p1][1] && ch[p2][0]) {
        res0 = find(ch[p1][1], ch[p2][0], d - 1) + (1 << d);
    }
    if (ch[p1][0] && ch[p2][1]) {
        res1 = find(ch[p1][0], ch[p2][1], d - 1) + (1 << d);
    }
    if (res0 != -1 || res1 != -1) {
        if (res0 != -1 && res1 != -1) {
            return min(res0, res1);
        }
        return res0 + res1 + 1;
    }
    return 0;
}
} // namespace Trie
long long ans = 0;
void dfs(int x, int d) {
    using namespace Trie;
    if (d < 0)
        return;
    if (ch[x][0] && ch[x][1]) {
        ans += find(ch[x][0], ch[x][1], d - 1) + (1 << d);
        dfs(ch[x][0], d - 1);
        dfs(ch[x][1], d - 1);
        return;
    }
    if (ch[x][0])
        dfs(ch[x][0], d - 1);
    if (ch[x][1])
        dfs(ch[x][1], d - 1);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n;i++){
        Trie::insert(a[i]);
    }
        dfs(Trie::rt, 30);
    cout << ans;
    return 0;
}
// Asusetic eru quionours
```

