#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e6 + 6;
namespace SAM {
int cnt, link[N], len[N], nxt[N][27];
int insert(int c, int last) {
    if (nxt[last][c]) {
        int p = last, x = nxt[last][c];
        if (len[p] + 1 == len[x]) {
            return x;
        } else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[x], sizeof(nxt[x]));
            while (p && nxt[p][c] == x) {
                nxt[p][c] = cq;
                p         = link[p];
            }
            link[cq] = link[x];
            link[x]  = cq;
            return cq;
        }
    }
    int cur  = ++cnt;
    int p    = last;
    len[cur] = len[p] + 1;
    while (p && !nxt[p][c]) {
        nxt[p][c] = cur;
        p         = link[p];
    }
    if (!p) {
        link[cur] = 1;
    } else {
        int x = nxt[p][c];
        if (len[p] + 1 == len[x]) {
            link[cur] = x;
        } else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[x], sizeof(nxt[x]));
            while (p && nxt[p][c] == x) {
                nxt[p][c] = cq;
                p         = link[p];
            }
            link[cq]  = link[x];
            link[cur] = link[x] = cq;
        }
    }
    return cur;
}
typedef long long ll;
ll solve() {
    ll ans = 0;
    for (int i = 2; i <= cnt; i++) {
        ans += len[i] - len[link[i]];
    }
    return ans;
}
} // namespace SAM
int n;
char s[N];
int main() {
    cin >> n;
    SAM::cnt = 1;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        int last = 1;
        for (int j = 0; s[j]; j++) {
            last = SAM::insert(s[j] - 'a' + 1, last);
        }
    }
    cout << SAM::solve();
    return 0;
}