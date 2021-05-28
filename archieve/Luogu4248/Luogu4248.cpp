#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 500010;

namespace SA {

char s[N];
int n, m = 127, sa[N], tp[N];
int rk[N], oldrk[N], bin[N], height[N];
void bsort() {
    for (int i = 0; i <= m; ++i)
        bin[i] = 0;
    for (int i = 1; i <= n; ++i)
        bin[rk[tp[i]]]++;
    for (int i = 1; i <= m; ++i)
        bin[i] += bin[i - 1];
    for (int i = n; i >= 1; --i)
        sa[bin[rk[tp[i]]]--] = tp[i];
}

void build() {
    for (int i = 1; i <= n; ++i) {
        tp[i] = i;
        rk[i] = s[i - 1];
    }
    bsort();
    for (int w = 1; w <= n; w <<= 1) {
        int cnt = 0;
        for (int i = n - w + 1; i <= n; ++i) {
            tp[++cnt] = i;
        }
        for (int i = 1; i <= n; ++i) {
            if (sa[i] > w) {
                tp[++cnt] = sa[i] - w;
            }
        }
        bsort();
        memcpy(oldrk, rk, sizeof(rk));
        rk[sa[1]] = cnt = 1;
        for (int i = 2; i <= n; ++i) {
            rk[sa[i]] = oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                                oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]
                            ? cnt
                            : ++cnt;
        }
        if (cnt == n)
            break;
        m = cnt;
    }
}

void getHeight() {
    for (int i = 1, k = 0; i <= n; ++i) {
        if (k)
            k--;
        int j = sa[rk[i] - 1];
        while (s[i + k - 1] == s[j + k - 1])
            ++k;
        height[rk[i]] = k;
    }
}
} // namespace SA
using namespace SA;

int S[N];
int top;
ll f[N];

int main() {
    cin >> s;
    n = strlen(s);
    build();
    getHeight();
    ll ans = 1LL * (n - 1) * n * (n + 1) / 2;
    for (int i = 1; i <= n; ++i) {
        while (top && height[S[top]] > height[i])
            --top;
        f[i] = f[S[top]] + 1ll * (i - S[top]) * height[i];
        ans -= 2 * f[i];
        S[++top] = i;
    }
    cout << ans << endl;
}