#include <algorithm>
#include <cstdio>
#include <iostream>
#define N   50005
#define E   500005
#define inf 1e9

using namespace std;

int n, m, s, k;

int tot0, tot1;
struct edge {
    int u, v, w;
    bool isNeed;
} orig[2][E], e[E];

bool cmp_edge(const edge &lhs, const edge &rhs) {
    return lhs.w < rhs.w;
}

inline void read(int &x) {
    x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - '0', ch = getchar();
}

void mergeSort(int delta) {
    for (int i = 1; i <= tot1; ++i)
        orig[1][i].w += delta;
    int i, j, o;
    i = j = o = 0;
    while (i < tot0 && j < tot1) {
        if (cmp_edge(orig[0][i + 1],
                     orig[1][j + 1])) { // w 相同, 与 s 相连的点优先
            e[++o] = orig[0][++i];
        } else {
            e[++o] = orig[1][++j];
        }
    }
    while (i < tot0)
        e[++o] = orig[0][++i];
    while (j < tot1)
        e[++o] = orig[1][++j];
    for (int i = 1; i <= tot1; ++i)
        orig[1][i].w -= delta;
    return;
}

namespace UFS {

int fa[N];
inline void init() {
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
}
inline int find(int u) {
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}
inline bool merge(int u, int v) {
    int x = find(u), y = find(v);
    if (x == y)
        return false;
    return fa[x] = y, true;
}

} // namespace UFS
using UFS ::merge;

int cnt;
long long res;
bool check(int delta) {
    mergeSort(delta);
    res = cnt = 0;
    UFS ::init();
    int block = n;
    for (int i = 1; i <= m; ++i) {
        cout << e[i].w << " ";
        if (!merge(e[i].u, e[i].v))
            continue;
        cnt += e[i].isNeed;
        res += e[i].w;
        if (--block == 1)
            break;
    }
    cout << endl;
    return cnt >= k;
}

int main() {
    int u, v, w;
    read(n), read(m), read(s), read(k);
    for (int i = 1; i <= m; ++i) {
        read(u), read(v), read(w);
        if (u == s || v == s) {
            orig[1][++tot1] = (edge){u, v, w, true};
        } else {
            orig[0][++tot0] = (edge){u, v, w, false};
        }
    }

    // judge if it is possible
    if (tot1 < k)
        return puts("Impossible"), 0;

    // not scc
    int block = n;
    UFS ::init();
    for (int i = 1; i <= tot0; ++i)
        block -= merge(orig[0][i].u, orig[0][i].v);
    for (int i = 1; i <= tot1; ++i)
        block -= merge(orig[1][i].u, orig[1][i].v);
    if (block != 1)
        return puts("Impossible"), 0;

    // mergeSort init
    sort(orig[0] + 1, orig[0] + 1 + tot0, cmp_edge);
    sort(orig[1] + 1, orig[1] + 1 + tot1, cmp_edge);

    // 找到满足条件的 maxdelta
    /*int l = -inf, r = inf, mid, maxp = -inf;
    if (!check(l))
        return puts("Impossible"), 0;
    while (l <= r) {
        mid = l + r >> 1;
            cout << mid << " " << check(mid) << endl;
        if (check(mid)) {
            maxp = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }*/

    check(-4);
    printf("%lld\n", res);
    return 0;
}