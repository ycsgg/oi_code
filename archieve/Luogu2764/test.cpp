#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int INF = 2e9;

int n, m, x, y, s, s1, t, np = 1, mfl, mct;
int h[305], cur[305], tp[305], ln[305], q[12505], f[305];
bool vis[305];
struct rpg {
    int li, nx, ln, ct;
} a[12505];

void add(int ls, int nx, int ln, int ct) {
    a[++np] = (rpg){h[ls], nx, ln, ct};
    h[ls]   = np;
    a[++np] = (rpg){h[nx], ls, 0, -ct};
    h[nx]   = np;
}

bool bfs() {
    memset(tp, 0, sizeof(tp));
    int hd = 1, tl = 1;
    q[hd]  = s1;
    tp[s1] = 1;
    while (hd <= tl) {
        int nw = q[hd++];
        for (int i = h[nw]; i; i = a[i].li) {
            if (a[i].ln && !tp[a[i].nx]) {
                tp[a[i].nx] = tp[nw] + 1;
                q[++tl]     = a[i].nx;
            }
        }
    }
    return tp[t];
}

int dfs(int u, int maxn) {
    if (u == t || !maxn)
        return maxn;
    int sum = 0;
    for (int &i = cur[u]; i; i = a[i].li) {
        if (a[i].ln && tp[a[i].nx] == tp[u] + 1) {
            int f = dfs(a[i].nx, min(maxn, a[i].ln));
            if (f) {
                maxn -= f;
                sum += f;
                a[i].ln -= f;
                a[i ^ 1].ln += f;
                if (!maxn)
                    break;
            }
        }
    }
    return sum;
}

void dnc() {
    while (bfs()) {
        for (int i = 0; i <= t; ++i)
            cur[i] = h[i];
        while (int d = dfs(s1, INF))
            mfl += d;
    }
}

int find(int x) {
    if (f[x] == x)
        return x;
    else
        return f[x] = find(f[x]);
}

void un(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb)
        f[fa] = fb;
}

int main() {
    scanf("%d%d", &n, &m);
    t = (n << 1) + 1;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        add(x, y + n, 1, -1);
    }
    for (int i = 1; i <= n; ++i) {
        add(s, i, 1, -1);
        add(i + n, t, 1, 0);
    }
    dnc();

    mfl = n - mfl;
    for (int i = 1; i <= n; ++i)
        f[i] = i;

    for (int i = 1; i <= n; ++i) {
        for (int j = h[i]; j; j = a[j].li) {
            if (!a[j].ln && a[j].nx - n <= n && a[j].nx) {
                un(i, a[j].nx - n);
                cout << i << " " << a[j].nx - n << endl;
            }
        }
    }
    for (int i = n; i; --i) {
        bool fl = 0;
        for (int j = 1; j <= n; ++j) {
            if (find(j) == i) {
                printf("%d ", j);
                fl = 1;
            }
        }
        if (fl)
            puts("");
    }
    printf("%d\n", mfl);
    return 0;
}