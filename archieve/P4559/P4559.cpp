
#include <iostream>
using namespace std;
const int max_left = 1e6;
const int N = 500005, M = 11000005;
int rt[M], siz[M], lson[M], rson[M];
long long sum[M];
int cnt;
//TODO:Solution
void insert(int &u, int pre, int l, int r, int p) {
    u      = ++cnt;
    siz[u] = siz[pre] + 1;
    sum[u] = sum[pre] + p;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid) {
        insert(lson[u], lson[pre], l, mid, p);
        rson[u] = rson[pre];
    } else {
        insert(rson[u], rson[pre], mid + 1, r, p);
        lson[u] = lson[pre];
    }
}
long long query(int x, int y, int l, int r, int f, int k) {
    if (siz[x] - siz[y] <= 0) {
        return 0;
    }
    long long sz = siz[x] - siz[y], s = sum[x] - sum[y];
    if (l >= k + f) {
        return s - (2 * k + 2 * f + sz - 1) * sz / 2;
    }
    if (r <= k + f + sz - 1) {
        return (2 * k + 2 * f + sz - 1) * sz / 2 - s;
    }
    int mid = (l + r) / 2;
    int lsz = siz[lson[x]] - siz[lson[y]];
    return query(lson[x], lson[y], l, mid, f, k) +
           query(rson[x], rson[y], mid + 1, r, f + lsz, k);
}
int n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        insert(rt[i], rt[i - 1], 1, max_left, x);
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << query(rt[r], rt[l - 1], 1, max_left, 0, k) << endl;
    }
}


