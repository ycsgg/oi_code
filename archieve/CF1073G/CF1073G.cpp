#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
char s[N];
int n, q;
typedef long long ll;
namespace SA {
int m = 127;
int buc[N], id[N], sa[N], rk[N], oldrk[N], px[N];
int height[N];
bool cmp(int a, int b, int w) {
    return oldrk[a] == oldrk[b] && oldrk[a + w] == oldrk[b + w];
}
void getSA() {
    int m = 127, p;
    for (int i = 1; i <= n; i++) {
        rk[i] = s[i];
        ++buc[rk[i]];
    }
    for (int i = 1; i <= m; i++) {
        buc[i] += buc[i - 1];
    }
    for (int i = n; i >= 1; i--) {
        sa[buc[rk[i]]--] = i;
    }
    for (int w = 1;; w *= 2, m = p) {
        p = 0;
        for (int i = n; i > n - w; i--) {
            id[++p] = i;
        }
        for (int i = 1; i <= n; i++) {
            if (sa[i] > w) {
                id[++p] = sa[i] - w;
            }
        }
        memset(buc, 0, sizeof(buc));
        for (int i = 1; i <= n; i++) {
            px[i] = rk[id[i]];
            ++buc[px[i]];
        }
        for (int i = 1; i <= m; i++) {
            buc[i] += buc[i - 1];
        }
        for (int i = n; i >= 1; i--) {
            sa[buc[px[i]]--] = id[i];
        }
        memcpy(oldrk, rk, sizeof(rk));
        p = 0;
        for (int i = 1; i <= n; i++) {
            rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
        }
        if (p == n) {
            for (int i = 1; i <= n; i++) {
                sa[rk[i]] = i;
            }
            break;
        }
    }
}
void getHeight() {
    for (int i = 1, k = 0; i <= n; i++) {
        if (k) {
            k--;
        }
        int j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k]) {
            ++k;
        }
        height[rk[i]] = k;
    }
}
} // namespace SA
namespace RMQ {
ll st[N][20];
int lg[N];
void init() {
    using namespace SA;
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        st[i][0] = height[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
        }
    }
}
ll query(int l, int r) {
    int k = lg[r - l + 1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}
} // namespace RMQ
ll lcp(int l, int r) {
    if (l > r) {
        swap(l, r);
    }
    if (l == r) {
        return n - SA::sa[l] + 1;
    }
    if (l + 1 == r) {
        return SA::height[r];
    }
    return RMQ::query(l + 1, r);
}
int a[N], b[N], c[N * 2];
using SA::rk;
using SA::sa;
int cnt;
struct QStack {
    ll st[N], len[N], top, sum;
    void qpush(ll val) {
        ll plen = 0;
        while (top && st[top] >= val) {
            sum -= st[top] * len[top];
            plen += len[top];
            top--;
        }
        push(val, plen);
    }
    void push(ll val, ll pl = 1) {
        st[++top] = val;
        len[top]  = pl;
        sum += pl * val;
    }
} AS, BS;

ll solve(int c1, int c2) {
    int lp = 1, rp = 1, pre = 0;
    ll ans = 0;
    while (lp <= c1 || rp <= c2) {
        int typ, pos;
        if (lp > c1 || rp <= c2 && b[rp] < a[lp]) {
            typ = 2;
            pos = b[rp++];
        } else {
            typ = 1;
            pos = a[lp++];
        }
        ll val = lcp(pre, pos);
        AS.qpush(val);
        BS.qpush(val);
        if (typ == 1) {
            ans += BS.sum;
            AS.push(n - sa[pos] + 1);
        } else {
            ans += AS.sum;
            BS.push(n - sa[pos] + 1);
        }
        pre = pos;
    }
    return ans;
}
int main() {
    cin >> n >> q >> s + 1;
    SA::getSA();
    SA::getHeight();
    RMQ::init();
    while (q--) {
        AS.top = BS.top = AS.sum = BS.sum = 0;
        int c1, c2;
        cin >> c1 >> c2;
        for (int i = 1; i <= c1; i++) {
            cin >> a[i];
            a[i] = rk[a[i]];
        }
        for (int i = 1; i <= c2; i++) {
            cin >> b[i];
            b[i] = rk[b[i]];
        }
        sort(a + 1, a + 1 + c1);
        sort(b + 1, b + 1 + c2);
        cout << solve(c1, c2) << endl;
    }
    return 0;
}
// Asusetic eru quionours