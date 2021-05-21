#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
const int N  = 1e5 + 5;
const ll mod = 1e9 + 7;
int n;
int a[N], in[N], st[N], top;
bool inst[N], vis[N], cyc[N];
int len[N];
void dfs(int x) {
    if (vis[x]) {
        if (inst[x]) {
            for (int i = top; i >= 1; i--) {
                cyc[st[i]] = 1;
                if (st[i] == x) {
                    return;
                }
            }
        }
        return;
    }
    vis[x] = inst[x] = 1;
    st[++top]        = x;
    dfs(a[x]);
    inst[x] = 0;
}
int cnt[N];
ll ans = 1;
void pre(int x) {
    int tot = 0, fr = 0, ed = 0, frid;
    while (cyc[x]) {
        ++tot;
        cyc[x] = 0;
        if (len[x]) {
            if (!fr) {
                fr   = tot;
                ed   = tot;
                frid = x;
            } else {
                int pm = (len[x] < tot - ed) + (len[x] <= tot - ed);
                ans    = 1ll * ans * pm % mod;
                ed     = tot;
            }
        }
        x = a[x];
    }
    if (!fr) {
        ++cnt[tot];
    } else {
        int kl = (len[frid] < tot - ed + fr) + (len[frid] <= tot - ed + fr);
        ans    = 1ll * ans * kl % mod;
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ++in[a[i]];
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i);
        if (!in[i]) {
            q.push(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if ((cyc[i] && in[i] > 2) || (!cyc[i] && in[i] > 1)) {
            cout << 0;
            exit(0);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        len[a[x]] = len[x] + 1;
        if (!cyc[a[x]]) {
            q.push(a[x]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cyc[i]) {
            pre(i);
        }
    }
    static ll num[N];
    for (int i = 1; i <= n; i++) {
        if (cnt[i]) {
            num[0] = 1;
            for (int j = 1; j <= cnt[i]; j++) {
                if (i > 1 && i % 2 != 0) {
                    num[j] = (num[j - 1] + num[j - 1]) % mod;
                } else {
                    num[j] = num[j - 1];
                }
                if (j > 1) {
                    num[j] =
                        (1ll * num[j] + 1ll * num[j - 2] * 1ll * (j - 1ll) %
                                            mod * 1ll * i % mod) %
                        mod;
                }
            }
            ans = 1ll * ans * num[cnt[i]] % mod;
        }
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours