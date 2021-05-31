### P5460 [BJOI2016]IP地址

首先 $[l,r]$ 的查询时能差分成 $[1,r]-[1,l-1]$ 的

一开始把所有 $ip$ 串放在一起比较好处理

考虑最优匹配是最长的匹配

当我们修改一个规则的时候，如果这个规则是某个规则 $A$ 的前缀，他不会影响到这个 $A$ 匹配的串

也就是仅影响他俩之间的匹配，每个点上记录一下自己作为匹配时的修改次数，修改规则直接打一个标记解决

```cpp
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
int n, q;
string s[N];
int opt[N];
struct Query {
    string ip;
    int id;
} qr[N];
namespace Trie {
int rt = 0;
int ch[N * 32][2];
int tag[N * 32], val[N * 32];
int end[N * 32];
int cnt;
void add(int x, int v) {
    tag[x] += v;
    val[x] += v;
}
void pushdown(int x) {
    if (tag[x] == 0) {
        return;
    }
    if (ch[x][0] && !end[ch[x][0]]) {
        add(ch[x][0], tag[x]);
    }
    if (ch[x][1] && !end[ch[x][1]]) {
        add(ch[x][1], tag[x]);
    }
    tag[x] = 0;
}
void update(string s, int v) {
    int now = rt;
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (!ch[now][s[i] - '0']) {
            ch[now][s[i] - '0'] = ++cnt;
        }
        pushdown(now);
        now = ch[now][s[i] - '0'];
    }
    end[now] += v;
    tag[now]++;
    val[now]++;
}
int query(string s) {
    int len = s.length();
    int now = rt;
    for (int i = 0; i < len; i++) {
        if (!ch[now][s[i] - '0']) {
            ch[now][s[i] - '0'] = ++cnt;
        }
        pushdown(now);
        now = ch[now][s[i] - '0'];
    }
    return val[now];
}
} // namespace Trie
vector<int> del[N], add[N];
int ans[N];
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        static char op[4];
        cin >> op >> s[i];
        if (op[0] == 'A') {
            opt[i] = 1;
        } else {
            opt[i] = -1;
        }
    }
    for (int i = 1; i <= q; i++) {
        cin >> qr[i].ip;
        qr[i].id = i;
        int l, r;
        cin >> l >> r;
        del[l].push_back(i);
        add[r].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        Trie::update(s[i], opt[i]);
        for (auto tmp : del[i]) {
            ans[qr[tmp].id] -= Trie::query(qr[tmp].ip);
        }
        for (auto tmp : add[i]) {
            ans[qr[tmp].id] += Trie::query(qr[tmp].ip);
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

