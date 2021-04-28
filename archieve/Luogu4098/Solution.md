### P4098 [HEOI2013]ALO

异或题条件反射可持久化Trie

枚举每一个值当次大值

设左边第一个比它大的是 $l_1$ 第二个是 $l_2$

同理有 $r_1$ $r_2$

他能当作最大值的区间就是 $[l_1+1,r_2-1]$ 于$[l_2+1,r_1-1]$

用链表维护然后Trie上查询

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 50010;
namespace Trie {
int cnt, rt[N];
int ch[N * 35][2];
int v[N * 35];
void insert(int x, int pos) {
    rt[pos] = ++cnt;
    int now = rt[pos];
    int pre = rt[pos - 1];
    v[now]  = v[pre] + 1;
    for (int i = 30; i >= 0; i--) {
        int k          = ((x >> i) & 1);
        ch[now][k ^ 1] = ch[pre][k ^ 1];
        ch[now][k]     = ++cnt;
        now            = ch[now][k];
        pre            = ch[pre][k];
        v[now]         = v[pre] + 1;
    }
}
int query(int l, int r, int s) {
    int now = rt[--l], pre = rt[r];
    int res = 0;
    for (int i = 30; i >= 0; i--) {
        int k = ((s >> i) & 1);
        if (v[ch[pre][k ^ 1]] - v[ch[now][k ^ 1]]) {
            res += (1 << i);
            now = ch[now][k ^ 1];
            pre = ch[pre][k ^ 1];
        } else {
            now = ch[now][k];
            pre = ch[pre][k];
        }
    }
    return res;
}
} // namespace Trie
int n;
int pre[N], nxt[N];
int a[N];
pair<int, int> b[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        pre[i] = i - 1;
        nxt[i] = i + 1;
        cin >> a[i];
        b[i] = make_pair(a[i], i);
        Trie::insert(a[i], i);
    }
    sort(b + 1, b + 1 + n);
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        int x = b[i].second;
        int l = pre[x], r = nxt[x];
        nxt[l] = r;
        pre[r] = l;
        if (l != 0)
            ans = max(ans, Trie::query(pre[l] + 1, r - 1, a[x]));
        if (r != n + 1)
            ans = max(ans, Trie::query(l + 1, nxt[r] - 1, a[x]));
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours

```

