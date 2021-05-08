### P3293 [SCOI2016]美味

01Trie的本质

考虑到在01Trie上做最大异或就是贪心的高位取反，实际上每个节点保存的就是一个值域

设节点 $x$ 代表从根到他的二进制值，是第 $i$ 位置，那么他代表 $[x,x+2^i-1]$

那么按照值域去考虑用主席树“模拟”01Trie查询即可

```cpp
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int ls[N * 20], rs[N * 20], val[N * 20], rt[N * 20], cnt;
#define ls(x) ls[x]
#define rs(x) rs[x]
void insert(int &u, int pre, int l, int r, int x) {
    if (r < x || l > x) {
        return;
    }
    u      = ++cnt;
    ls(u)  = ls(pre);
    rs(u)  = rs(pre);
    val[u] = val[pre] + 1;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    insert(ls(u), ls(pre), l, mid, x);
    insert(rs(u), rs(pre), mid + 1, r, x);
}
int query(int u, int v, int l, int r, int L, int R) {
    int p = val[v] - val[u];
    if (R < l || L > r || !p) {
        return 0;
    }
    if (L <= l && r <= R) {
        return p;
    }
    int mid = (l + r) / 2;
    return query(ls(u), ls(v), l, mid, L, R) +
           query(rs(u), rs(v), mid + 1, r, L, R);
}
int n, m, q;
int a[N];
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        m = max(m, a[i]);
    }
    for (int i = 1; i <= n; i++) {
        insert(rt[i], rt[i - 1], 0, m, a[i]);
    }
    while (q--) {
        int b, x, l, r;
        int ans = 0;
        cin >> b >> x >> l >> r;
        for (int i = 18; i >= 0; i--) {
            if (b & (1 << i)) {
                if (!query(rt[l - 1], rt[r], 0, m, ans - x,
                           ans - x + (1 << i) - 1)) {
                    ans += (1 << i);
                }
            } else {
                if (query(rt[l - 1], rt[r], 0, m, ans - x + (1 << i),
                          ans - x + (1 << i + 1) - 1)) {
                    ans += (1 << i);
                }
            }
        }
        cout << (ans ^ b) << endl;
    }
    return 0;
}
// Asusetic eru quionours
```