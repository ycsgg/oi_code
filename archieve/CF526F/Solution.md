### CF526F Pudding Monsters

很自然的想法是把这个东西拍到序列上，会形成一个排列

那么一个$k\times k$的矩形有$k$的点等价于某个长度为$k$的区间内的排列”连续"

就是把这个区间排完序之后是连续的一段正整数

那就是 析 合 树 

析点代表的区间$+1$ 合点所有的儿子两两都可以构成合法区间 还有所有的叶子节点

（这个析合树是$O(n\log n)$的，$O(n)$的太难写了）

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 6e5;
int n;
int a[N];
int pow2[25];
struct RMQ {
    int lg[N], mmax[N][20], mmin[N][20];
    void build() {
        pow2[0] = 1;
        for (int i = 1; i < 21; i++) {
            pow2[i] = pow2[i - 1] * 2;
        }
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i >> 1] + 1;
        }
        for (int i = 1; i <= n; i++) {
            mmax[i][0] = mmin[i][0] = a[i];
        }
        for (int i = 1; i < 19; i++) {
            for (int j = 1; j + pow2[i] - 1 <= n; j++) {
                mmin[j][i] = min(mmin[j][i - 1], mmin[j + pow2[i - 1]][i - 1]);
                mmax[j][i] = max(mmax[j][i - 1], mmax[j + pow2[i - 1]][i - 1]);
            }
        }
    }
    int query_min(int l, int r) {
        int k = lg[r - l + 1];
        return min(mmin[l][k], mmin[r - pow2[k] + 1][k]);
    }
    int query_max(int l, int r) {
        int k = lg[r - l + 1];
        return max(mmax[l][k], mmax[r - pow2[k] + 1][k]);
    }
} Table;
struct SegmentTree {
#define ls x * 2
#define rs x * 2 + 1
    int mmin[N * 8], tag[N * 8];
    void pushup(int x) {
        mmin[x] = min(mmin[ls], mmin[rs]);
    }
    void pushdown(int x) {
        if (tag[x]) {
            mmin[ls] += tag[x];
            tag[ls] += tag[x];
            mmin[rs] += tag[x];
            tag[rs] += tag[x];
            tag[x] = 0;
        }
    }
    void update(int x, int l, int r, int L, int R, int v) {
        if (l > R || r < L) {
            return;
        }
        if (l >= L && r <= R) {
            mmin[x] += v;
            tag[x] += v;
            return;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (R <= mid) {
            update(ls, l, mid, L, R, v);
        } else if (L > mid) {
            update(rs, mid + 1, r, L, R, v);
        } else {
            update(ls, l, mid, L, R, v);
            update(rs, mid + 1, r, L, R, v);
        }
        pushup(x);
    }
    int query(int x, int l, int r) {
        if (l == r) {
            return l;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (mmin[ls] == 0) {
            return query(ls, l, mid);
        } else {
            return query(rs, mid + 1, r);
        }
    }
#undef ls
#undef rs
} Tr;
int top1, top2, st1[N], st2[N];
int top, st[N];
int id[N], lp[N], rp[N], cnt;
int typ[N], M[N];
int rt;
bool check(int l, int r) {
    return (Table.query_max(l, r) - Table.query_min(l, r)) == r - l;
}
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N * 2], ecnt = 1;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
void build() {
    for (int i = 1; i <= n; i++) {
        while (top1 && a[i] <= a[st1[top1]]) {
            Tr.update(1, 1, n, st1[top1 - 1] + 1, st1[top1], a[st1[top1]]);
            top1--;
        }
        while (top2 && a[i] >= a[st2[top2]]) {
            Tr.update(1, 1, n, st2[top2 - 1] + 1, st2[top2], -a[st2[top2]]);
            top2--;
        }
        Tr.update(1, 1, n, st1[top1] + 1, i, -a[i]);
        st1[++top1] = i;
        Tr.update(1, 1, n, st2[top2] + 1, i, a[i]);
        st2[++top2] = i;
        id[i]       = ++cnt;
        lp[cnt] = rp[cnt] = i;
        int ls = Tr.query(1, 1, n), now = cnt;
        while (top && lp[st[top]] >= ls) {
            if (typ[st[top]] && check(M[st[top]], i)) {
                rp[st[top]] = i;
                add(st[top], now);
                now = st[top];
                top--;
            } else if (check(lp[st[top]], i)) {
                typ[++cnt] = 1;
                lp[cnt]    = lp[st[top]];
                rp[cnt]    = i;
                M[cnt]     = lp[now];
                add(cnt, st[top]);
                add(cnt, now);
                top--;
                now = cnt;
            } else {
                add(++cnt, now);
                do {
                    add(cnt, st[top]);
                    top--;
                } while (top && !check(lp[st[top]], i));
                lp[cnt] = lp[st[top]];
                rp[cnt] = i;
                add(cnt, st[top]);
                top--;
                now = cnt;
            }
        }
        st[++top] = now;
        Tr.update(1, 1, n, 1, i, -1);
    }
    rt = st[1];
}
int siz[N * 2];
void dfs(int x) {
    int cnt = 0;
    for (int i = head[x]; i; i = edge[i].nxt) {
        cnt++;
        dfs(edge[i].v);
    }
    siz[x] = cnt;
}
void print(int x) {
    vector<int> son;
    for (int i = head[x]; i; i = edge[i].nxt) {
        son.push_back((edge[i].v));
        print(edge[i].v);
    }
    if (!son.size()) {
        cout << x << "is a leaf node" << endl;
    } else {
        cout << x << " 's sons: ";
        for (auto i : son) {
            cout << i << " ";
        }
        cout << endl;
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        a[x] = y;
    }
    Table.build();
    build();
    dfs(rt);
    long long ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (typ[i]) {
            ans += 1ll * siz[i] * (siz[i] - 1) / 2;
        } else {
            ans++;
        }
    }
    cout << ans;
    return 0;
}
```

