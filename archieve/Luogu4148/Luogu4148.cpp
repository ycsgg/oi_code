#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, rt;
namespace KDT {
int D, top, cur, mempool[N];
const double alpha = 0.6;
const int K        = 2;
struct Point {
    int d[K];
    int w;
} p[N];
struct Rectangle {
    int x1, y1, x2, y2;
};

#define ls(x) tr[x].lson
#define rs(x) tr[x].rson
struct Node {
    int mmin[K], mmax[K], sum, lson, rson, siz;
    Point tp;
} tr[N];
int newnode() {
    if (top) {
        return mempool[top--];
    } else {
        return ++cur;
    }
}
bool operator<(const Point &a, const Point &b) {
    return a.d[D] < b.d[D];
}
void pushup(int x) {
    int l = tr[x].lson, r = tr[x].rson;
    for (int i = 0; i <= 1; ++i) {
        tr[x].mmin[i] = tr[x].mmax[i] = tr[x].tp.d[i];
        if (l)
            tr[x].mmin[i] = min(tr[x].mmin[i], tr[l].mmin[i]);
        if (r)
            tr[x].mmin[i] = min(tr[x].mmin[i], tr[r].mmin[i]);
        if (l)
            tr[x].mmax[i] = max(tr[x].mmax[i], tr[l].mmax[i]);
        if (r)
            tr[x].mmax[i] = max(tr[x].mmax[i], tr[r].mmax[i]);
    }
    tr[x].sum = tr[l].sum + tr[r].sum + tr[x].tp.w,
    tr[x].siz = tr[l].siz + tr[r].siz + 1;
    tr[x].siz = tr[ls(x)].siz + tr[rs(x)].siz + 1;
    tr[x].sum = tr[ls(x)].sum + tr[rs(x)].sum + tr[x].tp.w;
    for (int i = 0; i < K; i++) {
        tr[x].mmin[i] = tr[x].mmax[i] = tr[x].tp.d[i];
        if (ls(x)) {
            tr[x].mmin[i] = min(tr[x].mmin[i], tr[ls(x)].mmin[i]);
            tr[x].mmax[i] = max(tr[x].mmax[i], tr[ls(x)].mmax[i]);
        }
        if (rs(x)) {
            tr[x].mmin[i] = min(tr[x].mmin[i], tr[rs(x)].mmin[i]);
            tr[x].mmax[i] = max(tr[x].mmax[i], tr[rs(x)].mmax[i]);
        }
    }
}
int rebuild(int l, int r, int d) {
    if (l > r)
        return 0;
    int mid = (l + r) / 2;
    int k   = newnode();
    D       = d;
    nth_element(p + l, p + 1 + mid, p + r + 1);
    tr[k].tp = p[mid];
    ls(k)    = rebuild(l, mid - 1, d ^ 1);
    rs(k)    = rebuild(mid + 1, r, d ^ 1);
    pushup(k);
    return k;
}
void assign(int k, int num) {
    if (ls(k)) {
        assign(ls(k), num);
    }
    p[tr[ls(k)].siz + num + 1] = tr[k].tp;
    mempool[++top]             = k;
    if (rs(k)) {
        assign(rs(k), num + tr[ls(k)].siz + 1);
    }
}
void maintain(int &k, int d) {
    if (alpha * tr[k].siz < tr[ls(k)].siz ||
        alpha * tr[k].siz < tr[rs(k)].siz) {
        assign(k, 0);
        k = rebuild(1, tr[k].siz, d);
    }
}
void insert(int &k, Point tmp, int dim) {
    if (!k) {
        k     = newnode();
        ls(k) = rs(k) = 0;
        tr[k].tp      = tmp;
        pushup(k);
        return;
    }
    if (tmp.d[dim] <= tr[k].tp.d[dim]) {
        insert(ls(k), tmp, dim ^ 1);
    } else {
        insert(rs(k), tmp, dim ^ 1);
    }
    pushup(k);
    maintain(k, dim);
}
bool check_in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {
    return (X1 >= x1 && X2 <= x2 && Y1 >= y1 && Y2 <= y2);
}
bool check_out(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {
    return (x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1);
}
bool in(Rectangle A, Rectangle B) {
    return (B.x1 >= A.x1 && B.x2 <= A.x2 && B.y1 >= A.y1 && B.y2 <= A.y2);
}
bool out(Rectangle A, Rectangle B) {
    return (A.x1 > B.x2 || A.x2 < B.x1 || A.y1 > B.y2 || A.y2 < B.y1);
}
int query(int k, Rectangle Q) {
    if (!k)
        return 0;
    int res = 0;
    Rectangle now =
        (Rectangle){tr[k].mmin[0], tr[k].mmin[1], tr[k].mmax[0], tr[k].mmax[1]};
    Rectangle R =
        (Rectangle){tr[k].tp.d[0], tr[k].tp.d[1], tr[k].tp.d[0], tr[k].tp.d[1]};
    if (in(Q, now)) {
        return tr[k].sum;
    }
    if (out(Q, now)) {
        return 0;
    }
    if (in(Q, R)) {
        res += tr[k].tp.w;
    }
    res += query(ls(k), Q) + query(rs(k), Q);
    return res;
}
#undef ls
#undef rs
} // namespace KDT
int opt, ans;
int main() {
    cin >> n;
    while ("qwq") {
        scanf("%d", &opt);
        if (opt == 3) {
            return 0;
        }
        if (opt == 1) {
            int x, y, a;
            scanf("%d%d%d", &x, &y, &a);
            x ^= ans;
            y ^= ans;
            a ^= ans;
            KDT::Point p;
            p.d[0] = x;
            p.d[1] = y;
            p.w    = a;
            KDT::insert(rt, p, 0);
        } else {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1 ^= ans;
            y1 ^= ans;
            x2 ^= ans;
            y2 ^= ans;
            ans = KDT::query(rt, (KDT::Rectangle){x1, y1, x2, y2});
            cout << ans << endl;
        }
    }
    return 0;
}