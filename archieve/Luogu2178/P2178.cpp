
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
struct SuffixArray {
    static const int N = 320000;
    int a[N], x[N], id[N], cnt[N];
    int rk[N], sa[N], height[N];
    int pm = 50, n;
    bool cmp(int i, int j, int k) {
        return id[i] == id[j] && id[i + k] == id[j + k];
    }
    void build() {
        int m = pm;
        for (int i = 1; i <= n; i++) {
            x[i] = a[i];
            cnt[x[i]]++;
        }
        for (int i = 1; i <= m; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n; i >= 1; i--) {
            sa[cnt[x[i]]] = i;
            cnt[x[i]]--;
        }
        int p = 0;
        for (int k = 1; k <= n; k *= 2, m = p) {
            p = 0;
            for (int i = n - k + 1; i <= n; i++) {
                id[++p] = i;
            }
            for (int i = 1; i <= n; i++) {
                if (sa[i] > k) {
                    id[++p] = sa[i] - k;
                }
            }
            for (int i = 0; i <= m; i++) {
                cnt[i] = 0;
            }
            for (int i = 1; i <= n; i++) {
                cnt[x[id[i]]]++;
            }
            for (int i = 1; i <= m; i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n; i >= 1; i--) {
                sa[cnt[x[id[i]]]] = id[i];
                cnt[x[id[i]]]--;
            }
            swap(x, id);
            x[sa[1]] = 1;
            p        = 1;
            for (int i = 2; i <= n; i++) {
                x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
            }
            if (p >= n) {
                break;
            }
        }
        for (int i = 1; i <= n; i++) {
            rk[sa[i]] = i;
        }
        for (int i = 1, j = 0; i <= n; i++) {
            if (j)
                j--;
            while (a[i + j] == a[sa[rk[i] - 1] + j])
                j++;
            height[rk[i]] = j;
        }
    }
} SA;
const int N = 320000;
char s[N];
int id[N];
int n;
ll val[N], ans1[N], ans2[N], ans[N];
int fa[N], siz[N], mmax[N], mmin[N];
bool cmp(const int &a, const int &b) {
    return SA.height[a] > SA.height[b];
}
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y, int len) {
    x = find(x), y = find(y);
    fa[y] = x;
    ans1[len] += 1ll * siz[x] * siz[y];
    siz[x] += siz[y];
    ans[x] = max(ans[x], ans[y]);
    ans[x] = max(ans[x], max(1ll * mmax[x] * mmax[y], 1ll * mmin[x] * mmin[y]));
    ans[x] = max(ans[x], max(1ll * mmin[x] * mmax[y], 1ll * mmin[y] * mmax[x]));
    mmax[x]   = max(mmax[x], mmax[y]);
    mmin[x]   = min(mmin[x], mmin[y]);
    ans2[len] = max(ans2[len], ans[x]);
}
int main() {
    cin >> n;
    cin >> s + 1;
    for (int i = 1; i <= n; i++) {
        SA.a[i] = s[i] - 'a' + 1;
    }
    SA.n = n;
    SA.build();
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        id[i]   = i;
        fa[i]   = i;
        siz[i]  = 1;
        mmax[i] = mmin[i] = val[i];
        ans[i] = ans2[i] = -1e18;
    }
    memset(ans2, -63, sizeof(ans2));
    sort(id + 2, id + n + 1, cmp);
    for (int i = 2; i <= n; i++) {
        merge(SA.sa[id[i]], SA.sa[id[i] - 1], SA.height[id[i]]);
    }
    for (int i = n; i >= 0; i--) {
        ans1[i] += ans1[i + 1];
        ans2[i] = max(ans2[i], ans2[i + 1]);
    }
    for (int i = 0; i < n; i++) {
        printf("%lld %lld\n", ans1[i], !ans1[i] ? 0 : ans2[i]);
    }
}


