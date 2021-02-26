
#include <iostream>
using namespace std;
const int N = 100005;
int n, m;
int ans[N * 4];
double val[N * 4];
int query(int rt, int l, int r, double k) {
    if (val[rt] <= k)
        return 0;
    if (l == r)
        return val[rt] > k;
    if ((val[rt * 2] <= k)) {
        return query(rt * 2 + 1, (l + r) / 2 + 1, r, k);
    }
    return query(rt * 2, l, (l + r) / 2, k) + ans[rt] - ans[rt * 2];
}
void update(int rt, int l, int r, int pos, double v) {
    if (l == r) {
        ans[rt] = 1;
        val[rt] = v;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(rt * 2, l, mid, pos, v);
    } else {
        update(rt * 2 + 1, mid + 1, r, pos, v);
    }
    val[rt] = max(val[rt * 2], val[rt * 2 + 1]);
    ans[rt] = ans[rt * 2] + query(rt * 2 + 1, mid + 1, r, val[rt * 2]);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        update(1, 1, n, x, (double)y / x);
        cout << ans[1] << endl;
    }
}


