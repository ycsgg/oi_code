### P3755 [CQOI2017]老C的任务

https://www.luogu.com.cn/problem/P3755

二维数点模板

主席树

先把$x$排序，然后把$y$离散化

把$x$看作时间轴，把$y$看作值域轴

每个$(x,y,p)$就是在$y$上加$p$

一个询问$(x_1,y_1,x_2,y_2)$二分一下然后在$x_2$和$x_1-1$上查询$[y1,y2]$上的值做个差即可

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 100010;
typedef long long ll;
struct Data {
    int x, y, w;
    Data() {
    }
    Data(int x, int y) {
        this->x = x;
        this->y = y;
    }
} p[N];
bool operator<(const Data &a, const Data &b) {
    return a.x < b.x;
}
int tot;
int lson[N * 20], rson[N * 20], rt[N * 20];
ll val[N * 20];
int n, m;
int tmpy[N];
bool cmp_Data(const Data &a, const Data &b) {
    return a.x < b.x;
}
void build(int &k, int l, int r) {
    k = ++tot;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(lson[k], l, mid);
    build(rson[k], mid + 1, r);
    return;
}
void update(int &k, int pre, int l, int r, int x, int w) {
    k      = ++tot;
    val[k] = val[pre] + w;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    if (x <= mid) {
        rson[k] = rson[pre];
        update(lson[k], lson[pre], l, mid, x, w);
    } else {
        lson[k] = lson[pre];
        update(rson[k], rson[pre], mid + 1, r, x, w);
    }
    return;
}
ll query(int k, int l, int r, int L, int R) {
    if (l > R || r < L) {
        return 0;
    }
    if (l >= L && r <= R) {
        return val[k];
    }
    int mid = (l + r) / 2;
    return query(lson[k], l, mid, L, R) + query(rson[k], mid + 1, r, L, R);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y >> p[i].w;
    }
    sort(p + 1, p + 1 + n, cmp_Data);
    for (int i = 1; i <= n; i++) {
        tmpy[i] = p[i].y;
    }
    sort(tmpy + 1, tmpy + 1 + n);
    int tot_y = unique(tmpy + 1, tmpy + 1 + n) - tmpy - 1;
    for (int i = 1; i <= n; i++) {
        p[i].y = lower_bound(tmpy + 1, tmpy + 1 + tot_y, p[i].y) - tmpy;
    }
    build(rt[0], 1, tot_y);
    for (int i = 1; i <= n; i++) {
        update(rt[i], rt[i - 1], 0, tot_y, p[i].y, p[i].w);
    }
    while (m--) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 = lower_bound(p + 1, p + 1 + n, Data(x1, 0)) - p - 1;
        x2 = upper_bound(p + 1, p + 1 + n, Data(x2, 0)) - p - 1;
        y1 = lower_bound(tmpy + 1, tmpy + 1 + tot_y, y1) - tmpy;
        y2 = upper_bound(tmpy + 1, tmpy + 1 + tot_y, y2) - tmpy - 1;
        cout << query(rt[x2], 0, tot_y, y1, y2) -
                    query(rt[x1], 0, tot_y, y1, y2)
             << endl;
    }
    return 0;
}
```

