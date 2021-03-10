### P1456 Monkey King

可并堆板子

左偏树实现

```cpp
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m;
int val[N], fa[N];
int ch[N][2], dep[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int merge(int x, int y) {
    if (!x || !y) {
        return x + y;
    }
    if (val[x] < val[y])
        swap(x, y);
    ch[x][1]     = merge(ch[x][1], y);
    fa[ch[x][1]] = x;
    if (dep[ch[x][0]] < dep[ch[x][1]]) {
        swap(ch[x][0], ch[x][1]);
    }
    dep[x] = dep[ch[x][0]] + 1;
    return x;
}
int pick(int x) {
    val[x] /= 2;
    int rt   = merge(ch[x][0], ch[x][1]);
    ch[x][0] = ch[x][1] = dep[x] = 0;
    return fa[rt] = fa[x] = merge(rt, x);
}
int main() {
    while (cin >> n) {
        memset(ch, 0, sizeof(ch));
        memset(dep, 0, sizeof(dep));
        for (int i = 1; i <= n; i++) {
            cin >> val[i];
            fa[i] = i;
        }
        cin >> m;
        while (m--) {
            int x, y;
            cin >> x >> y;
            x = find(x);
            y = find(y);
            if (x == y) {
                cout << -1 << endl;
                continue;
            } else {
                int l = pick(x), r = pick(y);
                fa[l] = fa[r] = merge(l, r);
                cout << val[fa[l]] << endl;
            }
        }
    }
    return 0;
}
```