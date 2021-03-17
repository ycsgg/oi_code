#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const int N           = 100005;
int block_size        = 320;
const long double eps = 1e-18;
int n, m;
int belong[N];
long long sum[N], a0[N];
long long d[N];
int l[N], r[N];
struct Data {
    int x;
    long long y;
    friend bool operator<(const Data &a, const Data &b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }
        return a.x < b.x;
    }
};
vector<Data> ans[N];
Data tmp[N], q[N];
double slope(Data A, Data B) {
    if (fabs((double)B.x - (double)A.x) < eps) {
        if (fabs((double)B.y - (double)A.y) < eps)
            return 0;
        else if (B.y > A.y)
            return 1e18;
        else
            return -1e18;
    }
    return ((double)B.y - (double)A.y) / ((double)B.x - (double)A.x);
}
void build(int id) {
    if (d[id]) {
        for (int i = l[id]; i <= r[id]; i++) {
            sum[i] += 1ll * d[id] * (i - l[id] + 1);
        }
        d[id] = 0;
    }
    if (a0[id]) {
        for (int i = l[id]; i <= r[id]; i++) {
            sum[i] += a0[id];
        }
        a0[id] = 0;
    }
    int tail = 0;
    int cnt  = 0;
    ans[id].clear();
    for (int i = l[id]; i <= r[id]; i++) {
        tmp[++cnt] = {i - l[id] + 1, sum[i]};
    }
    sort(tmp + 1, tmp + 1 + cnt);
    for (int i = 1; i <= cnt; i++) {
        while (tail > 1 &&
               slope(q[tail], tmp[i]) >= slope(q[tail - 1], q[tail])) {
            tail--;
        }
        q[++tail] = tmp[i];
    }
    for (int i = 1; i <= tail; i++) {
        ans[id].push_back(q[i]);
    }
}
void update(int x, int y, int v) {
    for (int i = x; i <= min(y, r[belong[x]]); i++) {
        sum[i] += 1ll * v * (i - x + 1);
    }
    for (int i = y + 1; i <= r[belong[y]]; i++) {
        sum[i] += 1ll * v * (y - x + 1);
    }
    for (int i = belong[y] + 1; i <= belong[n]; i++) {
        a0[i] += 1ll * v * (y - x + 1);
    }
    build(belong[x]);
    if (belong[x] == belong[y])
        return;
    for (int i = l[belong[y]]; i <= y; i++) {
        sum[i] += 1ll * v * (i - x + 1);
    }
    build(belong[y]);
    for (int i = belong[x] + 1; i <= belong[y] - 1; i++) {
        a0[i] += 1ll * (l[i] - x) * v;
        d[i] += v;
    }
}
long long _query(int id) {
    int x = 1, y = ans[id].size();
    double res = -1.0 * d[id];
    while (x < y) {
        int mid = (x + y) / 2;
        if (slope(ans[id][mid - 1], ans[id][mid]) <= res)
            y = mid;
        else
            x = mid + 1;
    }
    x--;
    return (long long)ans[id][x].y + (long long)d[id] * ans[id][x].x +
           (long long)a0[id];
}
long long query(int x, int y) {
    build(belong[x]);
    long long res = -0x3f3f3f3f3f3f3f3f;
    for (int i = x; i <= min(r[belong[x]], y); i++) {
        res = max(res, sum[i]);
    }
    if (belong[x] == belong[y])
        return res;
    build(belong[y]);
    for (int i = l[belong[y]]; i <= y; i++) {
        res = max(res, sum[i]);
    }
    for (int i = belong[x] + 1; i <= belong[y] - 1; i++) {
        res = max(res, _query(i));
    }
    return res;
}
int main() {
    cin >> n;
    block_size = sqrt(n);
    for (int i = 1; i <= n; i++) {
        belong[i] = (i - 1) / block_size + 1;
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    for (int i = 1; i <= belong[n]; i++) {
        l[i] = (i - 1) * block_size + 1;
        r[i] = min(i * block_size, n);
    }
    for (int i = 1; i <= belong[n]; i++) {
        build(i);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int op, l, r, x;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 0) {
            scanf("%d", &x);
            update(l, r, x);
        } else {
            printf("%lld\n", query(l, r));
        }
    }
    return 0;
}