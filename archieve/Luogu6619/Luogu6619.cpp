#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
struct Data {
    int opt;
    int k, t, x, y;
} a[N];
int p[N], cnt;
int q;
struct BIT {
    ll c[N];
    int n;
    int lowbit(int x) {
        return x & (-x);
    }
    void add(int pos, int v) {
        while (pos <= n) {
            c[pos] += v;
            pos += lowbit(pos);
        }
    }
    ll query(int pos) {
        ll res = 0;
        while (pos) {
            res += c[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
    ll &operator[](int x) {
        return c[x];
    }
} Fire, Ice;

int main() {
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> a[i].opt;
        if (a[i].opt == 1) {
            scanf("%d%d%d", &a[i].t, &a[i].x, &a[i].y);
            p[++cnt] = a[i].x;
        } else {
            scanf("%d", &a[i].k);
        }
    }
    sort(p + 1, p + 1 + cnt);
    cnt = unique(p + 1, p + 1 + cnt) - p - 1;
    for (int i = 1; i <= q; i++) {
        if (a[i].opt == 1) {
            a[i].x = lower_bound(p + 1, p + 1 + cnt, a[i].x) - p;
        }
    }
    Fire.n = Ice.n = cnt;
    ll s_fire      = 0;
    for (int i = 1; i <= q; i++) {
        if (a[i].opt == 1) {
            if (a[i].t == 0) {
                Ice.add(a[i].x, a[i].y);
            } else {
                Fire.add(a[i].x + 1, a[i].y);
                s_fire += a[i].y;
            }
        } else {
            int k = a[i].k;
            if (a[k].t == 0) {
                Ice.add(a[k].x, -a[k].y);
            } else {
                Fire.add(a[k].x + 1, -a[k].y);
                s_fire -= a[k].y;
            }
        }
        ll sum_ice = 0, sum_fire = s_fire;
        ll f1 = 0, f2 = 0;
        int p1 = 0, p2 = 0;
        for (int i = 20; i >= 0; i--) {
            int pos = p1 + (1 << i);
            if (pos > cnt)
                continue;
            int nsumi = sum_ice + Ice[pos], nsumf = sum_fire - Fire[pos];
            if (nsumi < nsumf) {
                p1      = pos;
                sum_ice = nsumi, sum_fire = nsumf;
            }
        }
        f1 = sum_ice, sum_ice = 0, sum_fire = s_fire;
        if (p1 < cnt) {
            f2 = min(Ice.query(p1 + 1), s_fire - Fire.query(p1 + 1));
            for (int i = 20; i >= 0; i--) {
                int pos = p2 + (1 << i);
                if (pos > cnt)
                    continue;
                int nsumi = sum_ice + Ice[pos], nsumf = sum_fire - Fire[pos];
                if (nsumi < nsumf || min(nsumi, nsumf) == f2) {
                    p2      = pos;
                    sum_ice = nsumi, sum_fire = nsumf;
                }
            }
        }
        if (max(f1, f2) == 0) {
            printf("Peace\n");
        } else if (f1 > f2) {
            printf("%d %d\n", p[p1], f1 * 2);
        } else {
            printf("%d %d\n", p[p2], f2 * 2);
        }
    }
    return 0;
}