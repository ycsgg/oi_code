### **P5212 SubString**

一个子串出现的次数就是SAM中终止节点在```parent```树上的```endpos```集合大小

需要维护动态改边，和路径修改单点查询，用```LCT```即可

```cpp
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1200050;
char s[3000050];
string chars;
int mask;
string decodeWithMask(int mask) {
    cin >> s;
    chars = s;
    for (int j = 0; j < chars.length(); j++) {
        mask        = (mask * 131 + j) % chars.length();
        char t      = chars[j];
        chars[j]    = chars[mask];
        chars[mask] = t;
    }
    return chars;
}
namespace LCT {
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
int w[N], tag[N], ch[N][2], fa[N], st[N];
void pushdown(int x) {
    if (tag[x]) {
        w[ls(x)] += tag[x];
        tag[ls(x)] += tag[x];
        w[rs(x)] += tag[x];
        tag[rs(x)] += tag[x];
        tag[x] = 0;
    }
}
bool isroot(int x) {
    return ls(fa[x]) != x && rs(fa[x]) != x;
}
bool identity(int x) {
    return (ls(fa[x]) == x ? 0 : 1);
}
void rotate(int x) {
    int y = fa[x], z = fa[y];
    int k = identity(x);
    if (!isroot(y)) {
        ch[z][identity(y)] = x;
    }
    fa[x]            = z;
    fa[y]            = x;
    fa[ch[x][k ^ 1]] = y;
    ch[y][k]         = ch[x][k ^ 1];
    ch[x][k ^ 1]     = y;
}
void splay(int x) {
    int top   = 0;
    st[++top] = x;
    for (int i = x; !isroot(i); i = fa[i]) {
        st[++top] = fa[i];
    }
    while (top) {
        pushdown(st[top]);
        top--;
    }
    while (!isroot(x)) {
        int y = fa[x];
        if (!isroot(y)) {
            rotate(identity(x) ^ identity(y) ? x : y);
        }
        rotate(x);
    }
}
void access(int x) {
    int y = 0;
    while (x) {
        splay(x);
        rs(x) = y;
        y     = x;
        x     = fa[x];
    }
}
void Link(int x, int y) {
    fa[x] = y;
    access(y);
    splay(y);
    w[y] += w[x];
    tag[y] += w[x];
}
void Cut(int x) {
    access(x);
    splay(x);
    w[ls(x)] -= w[x];
    tag[ls(x)] -= w[x];
    fa[ls(x)] = 0;
    ls(x)     = 0;
}
#undef ls
#undef rs
} // namespace LCT

namespace SAM {
using LCT::Cut;
using LCT::Link;
using LCT::splay;
using LCT::w;
int cnt, last;
int nxt[N][3], link[N], len[N];
void insert(int c) {
    int p = last, cur = ++cnt;
    last     = cur;
    len[cur] = len[p] + 1;
    w[cur]   = 1;
    while (p && !nxt[p][c]) {
        nxt[p][c] = cur;
        p         = link[p];
    }
    if (!p) {
        link[cur] = 1;
        Link(cur, 1);
    } else {
        int q = nxt[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
            Link(cur, q);
        } else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[q], sizeof(nxt[q]));
            link[cq] = link[q];
            Link(cq, link[q]);
            link[q] = link[cur] = cq;
            Cut(q);
            Link(q, cq);
            Link(cur, cq);
            while (nxt[p][c] == q) {
                nxt[p][c] = cq;
                p         = link[p];
            }
        }
    }
}
void add() {
    decodeWithMask(mask);
    for (auto c : chars) {
        insert(c - 'A' + 1);
    }
}
int query() {
    decodeWithMask(mask);
    int p = 1;
    for (auto c : chars) {
        p = nxt[p][c - 'A' + 1];
        if (!p) {
            return 0;
        }
    }
    splay(p);
    return w[p];
}
} // namespace SAM
int q;
int main() {
    cin >> q;
    SAM::cnt = SAM::last = 1;
    cin >> s;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        SAM::insert(s[i] - 'A' + 1);
    }
    while (q--) {
        char opt[10];
        cin >> opt;
        if (opt[0] == 'A') {
            SAM::add();
        } else {
            int ans = SAM::query();
            cout << ans << endl;
            mask ^= ans;
        }
    }
    return 0;
}
```

