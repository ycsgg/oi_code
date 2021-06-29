#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
namespace File {
void open_file(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}
void close_file() {
    fclose(stdin);
    fclose(stdout);
}
} // namespace File
using ll    = long long;
const int N = 1e5 + 10;
int n, cnt;
int a[N], b[N], lg[N], root[N];
int st[N][20];
ll ans;
namespace SegmentTree {
struct Seg {
#define ls(p)  (tr[p].ls)
#define rs(p)  (tr[p].rs)
#define sum(p) (tr[p].sum)
    int ls, rs, sum;
} tr[N * 30];
int tot;
void insert(int &p, int pre, int l, int r, int pos) {
    p     = ++tot;
    tr[p] = tr[pre];
    sum(p)++;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    if (pos <= mid)
        insert(ls(p), ls(pre), l, mid, pos);
    else
        insert(rs(p), rs(pre), mid + 1, r, pos);
}
int query(int pl, int pr, int l, int r, int L, int R) {
    if (L > r || R < l)
        return 0;
    if (l >= L && r <= R) {
        return sum(pr) - sum(pl);
    }
    int mid = (l + r) / 2, res = 0;
    if (L <= mid)
        res += query(ls(pl), ls(pr), l, mid, L, R);
    if (R > mid)
        res += query(rs(pl), rs(pr), mid + 1, r, L, R);
    return res;
}
#undef ls
#undef rs
#undef sum
} // namespace SegmentTree
namespace ST {
void init() {
    lg[0] = -1;
    for (int i = 1; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        st[i][0] = i;
    }
    for (int j = 1; j <= 17; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = a[st[i][j - 1]] >= a[st[i + (1 << (j - 1))][j - 1]]
                           ? st[i][j - 1]
                           : st[i + (1 << (j - 1))][j - 1];
        }
    }
}
int query(int l, int r) {
    int t = lg[r - l + 1];
    return a[st[l][t]] >= a[st[r - (1 << t) + 1][t]] ? st[l][t]
                                                     : st[r - (1 << t) + 1][t];
}
} // namespace ST
void solve(int l, int r) {
    if (l > r)
        return;
    if (l == r) {
        ans += b[a[l]] == 1;
        return;
    }
    int mid = ST::query(l, r);
    if (mid - l + 1 <= r - mid) {
        for (int i = l; i <= mid; i++) {
            int k =
                upper_bound(b + 1, b + cnt + 1, b[a[mid]] / b[a[i]]) - b - 1;
            ans += SegmentTree::query(root[mid - 1], root[r], 1, cnt, 1, k);
        }
    } else {
        for (int i = mid; i <= r; i++) {
            int k =
                upper_bound(b + 1, b + cnt + 1, b[a[mid]] / b[a[i]]) - b - 1;
            ans += SegmentTree::query(root[l - 1], root[mid], 1, cnt, 1, k);
        }
    }
    solve(l, mid - 1);
    solve(mid + 1, r);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    cnt = unique(b + 1, b + n + 1) - (b + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
    }
    for (int i = 1; i <= n; i++) {
        SegmentTree::insert(root[i], root[i - 1], 1, cnt, a[i]);
    }
    ST::init();
    solve(1, n);
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours