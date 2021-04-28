### CF1516D Cut

其实就是把一个区间划分成若干互质的区间

考虑对每个数预处理出来后面的能向后延伸的最大的互质长度，然后倍增去跳就行

```cpp
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int prime[N], pcnt, mindiv[N];
bool vis[N];
void pre() {
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mindiv[i]     = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] >= N) {
                break;
            }
            vis[i * prime[j]]    = 1;
            mindiv[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
int n, m;
int a[N];
int nxt[N][21];
int nxtp[N];
int solve(int l, int r) {
    int res = 0;
    for (int i = 20; i >= 0; i--) {
        if (nxt[l][i] && nxt[l][i] <= r) {
            res += (1 << i);
            l = nxt[l][i];
        }
    }
    return res + 1;
}
int main() {
    pre();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= pcnt; i++) {
        nxtp[prime[i]] = n + 1;
    }
    for (int j = 0; j <= 20; j++) {
        nxt[n + 1][j] = n + 1;
    }
    for (int i = n; i >= 1; i--) {
        int tmp  = a[i];
        int tnxt = n + 1;
        while (tmp != 1) {
            int d = mindiv[tmp];
            tnxt  = min(tnxt, nxtp[d]);
            while (tmp % d == 0) {
                tmp /= d;
            }
            nxtp[d] = i;
        }
        nxt[i][0] = min(nxt[i + 1][0], tnxt);
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= 20; j++) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << solve(l, r) << endl;
    }
    return 0;
}
// Asusetic eru quionours

```

