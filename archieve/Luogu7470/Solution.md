### P7470 [NOI Online 2021 提高组] 岛屿探险

先把询问拆成$[1,r]-[1,l-1]$

然后考虑除去$\min(b,d)$的限制变成对于指定的$d$可以按位考虑

在第$i$位上，若$d_i=0$那么所有的$(a \ \mathrm{xor} \ c)_i=1$都可以除去，剩下的接着向低位考虑

$d_i=1$类似

这样的处理很容易发现是可以$0$-$1$ trie处理，而对于区间的限制则可以可持久化

而如果除去$d$的限制，仅查询$a_i \ \mathrm{xor}\ c \le b_i$ 

考虑每一个插入对于答案的贡献，那么考虑起来和上一类情况类似，只是需要在插入是考虑贡献

而对于两个情况同时出现，我们希望找到一个分界点，前面是$b_i<d$后面相反

也就是按$b_i$排序，但是这样的话又没办法处理区间关系，所以考虑用cdq分治 外层去掉下标限制，内层按$b_i$排序，左边修改对右边产生贡献的套路

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
int n, m, cnt;
const int N = 1e6 + 5, M = 1e7 + 5;
struct Data {
    int id, pos, typ, a, b, c, d;
    friend bool operator<(const Data &A, const Data &B) {
        if (A.pos == B.pos) {
            if (!A.typ || !B.typ) {
                return !A.typ;
            } else {
                return A.typ < B.typ;
            }
        } else {
            return A.pos < B.pos;
        }
    }
} q[N];
bool cmpb(const Data &A, const Data &B) {
    return A.b < B.b;
}
int ans[N];
namespace MinD {
int ch[M][2], siz[M], rt, tot;
void insert(int x, int v) {
    int now = rt;
    int id;
    for (int i = 23; i >= 0; i--) {
        id = ((x >> i) & 1);
        if (!ch[now][id]) {
            ch[now][id] = ++tot;
        }
        now = ch[now][id];
        siz[now] += v;
    }
}
int query(int c, int d) {
    ++d;
    int res = 0, now = rt, idc, idd;
    for (int i = 23; i >= 0; --i) {
        idc = ((c >> i) & 1);
        idd = ((d >> i) & 1);
        if (idd) {
            res += siz[ch[now][idc]];
            now = ch[now][idc ^ 1];
        } else {
            now = ch[now][idc];
        }
        if (!now)
            break;
    }
    return res;
}
} // namespace MinD

namespace MinB {
int ch[M][2], siz[M], rt, tot;
void insert(int a, int b, int v) {
    ++b;
    int now = rt, ida, idb;
    for (int i = 23; i >= 0; --i) {
        ida = ((a >> i) & 1);
        idb = ((b >> i) & 1);
        if (idb) {
            if (!ch[now][ida]) {
                ch[now][ida] = ++tot;
            }
            if (!ch[now][ida ^ 1]) {
                ch[now][ida ^ 1] = ++tot;
            }
            siz[ch[now][ida]] += v;
            now = ch[now][ida ^ 1];
        } else {
            if (!ch[now][ida]) {
                ch[now][ida] = ++tot;
            }
            now = ch[now][ida];
        }
    }
}
int query(int c) {
    int now = rt, res = 0, id;
    for (int i = 23; i >= 0; --i) {
        id = ((c >> i) & 1);
        if (!ch[now][id]) {
            break;
        }
        now = ch[now][id];
        res += siz[now];
    }
    return res;
}
} // namespace MinB
void cdq(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    sort(q + l, q + mid + 1, cmpb);
    sort(q + mid + 1, q + r + 1, cmpb);
    // solve
    for (int i = l; i <= mid; ++i) {
        if (q[i].typ == 0) {
            MinD::insert(q[i].a, 1);
        }
    }
    int j = l;
    for (int i = mid + 1; i <= r; ++i) {
        while (j <= mid && q[j].b < q[i].d) {
            if (q[j].typ == 0) {
                MinD::insert(q[j].a, -1);
                MinB::insert(q[j].a, q[j].b, 1);
            }
            ++j;
        }
        if (q[i].typ) {
            int t1 = MinD::query(q[i].c, q[i].d);
            int t2 = MinB::query(q[i].c);
            ans[q[i].id] += q[i].typ * (t1 + t2);
        }
    }
    // clear
    for (int i = l; i < j; ++i) {
        if (!q[i].typ) {
            MinB::insert(q[i].c, q[i].d, -1);
        }
    }
    for (int i = j; i <= mid; ++i) {
        if (!q[i].typ) {
            MinD::insert(q[i].a, -1);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        q[++cnt] = (Data){i, i, 0, a, b, a, b};
    }
    for (int i = 1; i <= m; ++i) {
        int l, r, c, d;
        scanf("%d%d%d%d", &l, &r, &c, &d);
        q[++cnt] = (Data){i, r, 1, c, d, c, d};
        q[++cnt] = (Data){i, l - 1, -1, c, d, c, d};
    }
    sort(q + 1, q + cnt + 1);
    cdq(1, cnt);
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
```

