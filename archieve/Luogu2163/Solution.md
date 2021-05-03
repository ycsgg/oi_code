### P2163 [SHOI2007]园丁的烦恼

二维数点裸题

cdq / 树状数组啥的都可以

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 3e6 + 10;
struct Oper {
    int x, y, opt, id;
} q[N], tmpq[N];
auto cmp = [&](const Oper &A, const Oper &B) -> bool {
    if (A.x == B.x) {
        if (A.y == B.y) {
            return A.opt;
        }
        return A.y < B.y;
    }
    return A.x < B.x;
};
int qid, ansid;
int ans[N];
int n, m;
void cdq(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    int posl = l, posr = mid + 1;
    int cur = l, tot = 0;
    while (posl <= mid && posr <= r) {
        if (q[posl].y <= q[posr].y) {
            tot += q[posl].opt;
            tmpq[cur++] = q[posl++];
        } else {
            ans[q[posr].id] += tot;
            tmpq[cur++] = q[posr++];
        }
    }
    while (posl <= mid) {
        tmpq[cur++] = q[posl++];
    }
    while (posr <= r) {
        ans[q[posr].id] += tot;
        tmpq[cur++] = q[posr++];
    }
    for (int i = l; i <= r; i++) {
        q[i] = tmpq[i];
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        q[++qid] = {x, y, 1, 0};
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        q[++qid] = {c, d, 0, ++ansid};
        q[++qid] = {c, b - 1, 0, ++ansid};
        q[++qid] = {a - 1, d, 0, ++ansid};
        q[++qid] = {a - 1, b - 1, 0, ++ansid};
    }
    sort(q + 1, q + 1 + qid, cmp);
    cdq(1, qid);
    for (int i = 1; i + 3 <= ansid; i += 4) {
        cout << ans[i] - ans[i + 1] - ans[i + 2] + ans[i + 3] << endl;
    }
    return 0;
}
// Asusetic eru quionours

```

