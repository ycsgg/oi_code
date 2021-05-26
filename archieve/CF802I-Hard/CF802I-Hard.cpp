#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
namespace SAM {
int nxt[N * 2][27], link[N * 2], len[N * 2], siz[N * 2];
int cnt, last;
void insert(int c) {
    int cur  = ++cnt;
    int p    = last;
    last     = cur;
    siz[cur] = 1;
    len[cur] = len[p] + 1;
    while (p && !nxt[p][c]) {
        nxt[p][c] = cur;
        p         = link[p];
    }
    if (!p) {
        link[cur] = 1;
    } else {
        int q = nxt[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
        } else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[q], sizeof(nxt[q]));
            link[cq] = link[q];
            link[q] = link[cur] = cq;
            while (p && nxt[p][c] == q) {
                nxt[p][c] = cq;
                p         = link[p];
            }
        }
    }
}
void build(char *s) {
    int n = strlen(s);
    memset(nxt, 0, sizeof(nxt));
    memset(link, 0, sizeof(link));
    memset(siz, 0, sizeof(siz));
    memset(len, 0, sizeof(len));
    last = cnt = 1;
    for (int i = 0; i < n; i++) {
        insert(s[i] - 'a');
    }
}

} // namespace SAM
struct Edge {
    int v;
    int nxt;
} edge[N * 4];
int head[N * 4], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
long long ans = 0;
int T;
char s[N];
void dfs(int x) {
    using namespace SAM;
    // siz[x] = 1;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        dfs(v);
        siz[x] += siz[v];
    }
    // cout << len[x] << endl;
    ans += 1ll * (len[x] - len[link[x]]) * siz[x] * siz[x];
}
int main() {
    cin >> T;
    while (T--) {
        memset(head, 0, sizeof(head));
        memset(edge, 0, sizeof(edge));
        ecnt = 0;
        ans  = 0;
        cin >> s;
        SAM::build(s);
        for (int i = 1; i <= SAM::cnt; i++) {
            add(SAM::link[i], i);
            // cout << SAM::link[i] << endl;
        }
        dfs(1);
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours