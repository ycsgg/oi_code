### P2468 [SDOI2010]粟粟的书架

分类搞，只有一行的主席树二分，其他的二位前缀和

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int V = 1000;
int n, m, q;
namespace SubTask1 {
const int N = 210;
int val[N][N];
int sum[N][N][V + 10], cnt[N][N][V + 10];
int getsum(int x1, int y1, int x2, int y2, int k) {
    return sum[x2][y2][k] - sum[x1 - 1][y2][k] - sum[x2][y1 - 1][k] +
           sum[x1 - 1][y1 - 1][k];
}
int getcnt(int x1, int y1, int x2, int y2, int k) {
    return cnt[x2][y2][k] - cnt[x1 - 1][y2][k] - cnt[x2][y1 - 1][k] +
           cnt[x1 - 1][y1 - 1][k];
}
void Solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> val[i][j];
        }
    }
    for (int k = 1; k <= V; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j][k] = sum[i - 1][j][k] + sum[i][j - 1][k] -
                               sum[i - 1][j - 1][k] +
                               (val[i][j] >= k ? val[i][j] : 0);
                cnt[i][j][k] = cnt[i - 1][j][k] + cnt[i][j - 1][k] -
                               cnt[i - 1][j - 1][k] + (val[i][j] >= k ? 1 : 0);
            }
        }
    }
    while (q--) {
        int x1, y1, x2, y2, h;
        cin >> x1 >> y1 >> x2 >> y2 >> h;
        if (getsum(x1, y1, x2, y2, 1) < h) {
            cout << "Poor QLW" << endl;
            continue;
        }
        int l = 1, r = V;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (getsum(x1, y1, x2, y2, mid) < h)
                r = mid - 1;
            else
                l = mid;
        }
        cout << getcnt(x1, y1, x2, y2, l) - (getsum(x1, y1, x2, y2, l) - h) / l
             << endl;
    }
}
} // namespace SubTask1
namespace SubTask2 {
const int N = 500100;
int a[N];

int tot, root[N];
struct SegmentTree {
    int lc, rc;
    int cnt;
    int sum;
} tr[N * 200];

int newnode() {
    tot++;
    tr[tot].lc = tr[tot].rc = tr[tot].cnt = tr[tot].sum = 0;
    return tot;
}

void insert(int &p, int now, int l, int r, int pos, int val1, int val2) {
    p     = newnode();
    tr[p] = tr[now];
    tr[p].cnt += val1;
    tr[p].sum += val2;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    if (pos <= mid)
        insert(tr[p].lc, tr[now].lc, l, mid, pos, val1, val2);
    else
        insert(tr[p].rc, tr[now].rc, mid + 1, r, pos, val1, val2);
}

int query(int p, int q, int l, int r, int h) {
    if (l == r)
        return (h - 1) / l + 1;
    int mid  = (l + r) / 2;
    int rcnt = tr[tr[q].rc].cnt - tr[tr[p].rc].cnt,
        rsum = tr[tr[q].rc].sum - tr[tr[p].rc].sum;
    if (h <= rsum)
        return query(tr[p].rc, tr[q].rc, mid + 1, r, h);
    else
        return query(tr[p].lc, tr[q].lc, l, mid, h - rsum) + rcnt;
}

void Solve() {
    n = m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        insert(root[i], root[i - 1], 1, V, a[i], 1, a[i]);
    }
    while (q--) {
        int l, r, h;
        int tmp;
        cin >> tmp >> l >> tmp >> r >> h;
        if (tr[root[r]].sum - tr[root[l - 1]].sum < h) {
            cout << "Poor QLW" << endl;
            continue;
        }
        cout << query(root[l - 1], root[r], 1, V, h) << endl;
    }
}
} // namespace SubTask2
int main() {
    cin >> n >> m >> q;
    if (n > 1) {
        SubTask1::Solve();
    } else {
        SubTask2::Solve();
    }
    return 0;
}
// Asusetic eru quionours.
```

