#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
struct node {
    int next, to, w;
} e[5000005];
bool bo[N][2];
int now[N * 2], ret[N * 2], head[N], m;
inline void add(int u, int v, int w) {
    e[++m].w  = w;
    e[m].to   = v;
    e[m].next = head[u];
    head[u]   = m;
}
int main() {
    char ch;
    int s, t, x1, x2, y1, y2, i, j, u, v, rem, l, r, res, tmp;
    tmp = r = 2;
    cin >> t >> s >> x1 >> y1 >> x2 >> y2;
    for (int i = 1; i <= (s * 2 + 1); i++) {
        getchar();
        for (int j = 1; j <= (i & 1 ? t : (t * 2 + 1)); j++) {
            ch = getchar();
            if (ch == 'n')
                continue;
            if (i & 1)
                u = (i >> 1) * (t + 1) + j, v = u + 1;
            else
                u = (i >> 1) * (t + 1) + (j >> 1) + (j & 1),
                v = u - t - (j & 1);
            add(u, v, ch != 'w'), add(v, u, ch != 'w');
        }
    }
    now[1] = now[2] = y1 * (t + 1) + x1 + 1;
    ret[1] = res = 0;
    rem          = y2 * (t + 1) + x2 + 1;
    l = bo[now[1]][1] = bo[now[1]][0] = ret[2] = 1;
    while (l <= r) {
        if (now[l] == rem)
            break;
        for (i = head[now[l]]; i; i = e[i].next)
            if (e[i].w != ret[l]) {
                v = e[i].to;
                if (!bo[v][e[i].w]) {
                    bo[v][e[i].w] = 1;
                    now[++r]      = v;
                    ret[r]        = e[i].w;
                }
            }
        l++;
        if (l > tmp)
            tmp = r, res++;
    }
    cout << res;
    return 0;
}
// Asusetic eru quionours