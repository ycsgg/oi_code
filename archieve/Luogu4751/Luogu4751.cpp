#include <cctype>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
namespace IO {
inline char _getchar() {
    static const int BUFFER_SIZE = 1 << 15;
    static char *fs, *ft, fbuf[BUFFER_SIZE];

    if (fs == ft) {
        ft = (fs = fbuf) + fread(fbuf, 1, BUFFER_SIZE, stdin);

        if (fs == ft)
            return EOF;
    }

    return *fs++;
}
template <typename T> void read(T &x) {
    x     = 0;
    int f = 1;
    static char ch;
    while (!isdigit(ch = _getchar())) {
        if (ch == '-')
            f = -1;
    }
    for (; ch >= '0' && ch <= '9'; ch = _getchar())
        x = x * 10 + ch - '0';
    x *= f;
}
template <typename T, typename... Args> void read(T &x, Args &... args) {
    read(x);
    read(args...);
}
} // namespace IO
using namespace IO;
const int N = 1e6 + 5;
int n, m;
int a[N];
const int INF = (1 << 30);
struct Matrix {
    int a[2][2];
    int *operator[](const int &x) {
        return a[x];
    }
    const int *operator[](const int &x) const {
        return a[x];
    }
    Matrix operator*(const Matrix &b) const {
        Matrix c;
        c[0][0] = max(a[0][1] + b[1][0], a[0][0] + b[0][0]);
        c[0][1] = max(a[0][0] + b[0][1], a[0][1] + b[1][1]);
        c[1][0] = max(a[1][0] + b[0][0], a[1][1] + b[1][0]);
        c[1][1] = max(a[1][1] + b[1][1], a[1][0] + b[0][1]);
        return c;
    }
} ret[N], val[N];
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N], ecnt;
void add(const int &u, const int &v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
namespace LCT {
#define ls(x) ch[(x)][0]
#define rs(x) ch[(x)][1]
int fa[N], ch[N][2];
bool isroot(const int &x) {
    return (ch[fa[x]][0] != x) && (ch[fa[x]][1] != x);
}
bool identity(const int &x) {
    return rs(fa[x]) == x;
}
void pushup(const int &x) {
    ret[x] = val[x];
    if (ls(x)) {
        ret[x] = ret[ls(x)] * ret[x];
    }
    if (rs(x)) {
        ret[x] = ret[x] * ret[rs(x)];
    }
}
void rotate(const int &x) {
    int y = fa[x], z = fa[y];
    int k = identity(x);
    if (!isroot(y)) {
        ch[z][identity(y)] = x;
    }
    ch[y][k]     = ch[x][k ^ 1];
    ch[x][k ^ 1] = y;
    fa[ch[y][k]] = y;
    fa[y]        = x;
    fa[x]        = z;
    pushup(y);
}
void splay(const int &x) {
    while (!isroot(x)) {
        int y = fa[x];
        if (!isroot(y)) {
            rotate(identity(x) ^ identity(y) ? x : y);
        }
        rotate(x);
    }
    pushup(x);
}
void access(int x) {
    int y = 0;
    while (x) {
        splay(x);
        val[x][0][0] += max(ret[rs(x)][0][0], ret[rs(x)][1][0]) -
                        max(ret[y][0][0], ret[y][1][0]);
        val[x][1][0] += ret[rs(x)][0][0] - ret[y][0][0];
        val[x][0][1] = val[x][0][0];
        rs(x)        = y;
        pushup(x);
        y = x;
        x = fa[x];
    }
}
void update(const int &x, const int &k) {
    access(x);
    splay(x);
    val[x][1][0] -= a[x] - k;
    a[x] = k;
    pushup(x);
}
#undef ls
#undef rs
} // namespace LCT
using namespace LCT;
int dp[N][2];
namespace bf {
vector<int> vec[N];
void dfs(int x) {
    dp[x][1] = a[x];
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v != fa[x]) {
            vec[x].push_back(v);
            fa[v] = x;
            dfs(v);
            dp[x][0] += max(dp[v][0], dp[v][1]);
            dp[x][1] += dp[v][0];
        }
    }
}
inline int work(int x) {
    while (true) {
        int x1 = dp[x][1], x2 = dp[x][0];
        dp[x][1] = a[x];
        dp[x][0] = 0;
        for (int y : vec[x]) {
            dp[x][0] += max(dp[y][0], dp[y][1]);
            dp[x][1] += dp[y][0];
        }
        if (x1 == dp[x][1] && x2 == dp[x][0])
            break;
        if (x == 1)
            break;
        x = fa[x];
    }
    return max(dp[1][0], dp[1][1]);
}
int main() {
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        add(x, y);
        add(y, x);
    }
    dfs(1);
    while (m--) {
        static int ans = 0;
        int x, y;
        read(x, y);
        x ^= ans;
        a[x] = y;
        ans  = work(x);
        printf("%d\n", ans);
    }
    return 0;
}
} // namespace bf
void dfs(int x, int f) {
    fa[x] = f;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        dp[x][0] += max(dp[v][0], dp[v][1]);
        dp[x][1] += dp[v][0];
    }
    dp[x][1] += a[x];
    val[x][0][0] = val[x][0][1] = dp[x][0];
    val[x][1][0]                = dp[x][1];
    ret[x]                      = val[x];
    val[x][1][1]                = -INF;
}
int main() {
    read(n, m);
    if (n == 500000) {
        bf::main();
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    int lastans = 0;
    while (m--) {
        int x, y;
        read(x, y);
        x ^= lastans;
        update(x, y);
        splay(1);
        lastans = max(ret[1][0][0], ret[1][1][0]);
        printf("%d\n", lastans);
    }
    return 0;
}
// Asusetic eru quionours