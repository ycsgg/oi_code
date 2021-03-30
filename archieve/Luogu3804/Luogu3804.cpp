#include <cstring>
#include <iostream>
using namespace std;
const int N = 2000005;
namespace SAM {
int last, cnt, nxt[N * 2][27], link[N * 2], len[N * 2], siz[N];
void insert(int c) {
    int p    = last;
    int cur  = ++cnt;
    last     = cur;
    len[cur] = len[p] + 1;
    while (p && !nxt[p][c]) {
        nxt[p][c] = cur;
        p         = link[p];
    }
    if (!p)
        link[cur] = 1;
    else {
        int q = nxt[p][c];
        if (len[p] + 1 == len[q])
            link[cur] = q;
        else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[q], sizeof(nxt[q]));
            link[cq] = link[q];
            link[q] = link[cur] = cq;
            while (nxt[p][c] == q) {
                nxt[p][c] = cq;
                p         = link[p];
            }
        }
    }
    siz[cur] = 1;
}
void build(char *s) {
    int len = strlen(s);
    last = cnt = 1;
    for (int i = 0; i < len; i++) {
        insert(s[i] - 'a');
    }
}
int c[N], a[N];
int solve() {
    long long ans = 0;
    for (int i = 1; i <= cnt; i++) {
        c[len[i]]++;
    }
    for (int i = 1; i <= cnt; i++) {
        c[i] += c[i - 1];
    }
    for (int i = 1; i <= cnt; i++) {
        a[c[len[i]]] = i;
        c[len[i]]--;
    }
    for (int i = cnt; i; i--) {
        int p = a[i];
        siz[link[p]] += siz[p];
        if (siz[p] > 1) {
            ans = max(ans, 1ll * siz[p] * len[p]);
        }
    }
    return ans;
}
} // namespace SAM
char s[N];
int main() {
    cin >> s;
    SAM::build(s);
    cout << SAM::solve();
    return 0;
}