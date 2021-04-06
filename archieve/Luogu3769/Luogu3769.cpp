#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 5e4 + 10;
namespace KDT {
const int INF = 1e9 + 10;
const int K   = 4;
int D;
int ans, flag;
struct Point {
    int d[K], w;
    int &operator[](int x) {
        return d[x];
    }
    const int operator[](int x) const {
        return d[x];
    }
    const bool operator<(const Point &p) const {
        if (d[D] != p[D])
            return d[D] < p[D];
        for (int i = 0; i < K - flag; i++) {
            if (d[i] != p[i]) {
                return d[i] < p[i];
            }
        }
        return 0;
    }
};
struct KCUBE {
    Point a, b;
    KCUBE(const Point &a, const Point &b) {
        this->a = a;
        this->b = b;
    }
};
const double alpha = 0.6;
template <int K> struct KDTree {
    struct Node {
        int siz, maxv;
        Node *ls, *rs;
        Point range, mmin, mmax;
        void pushup() {
            siz  = ls->siz + 1 + rs->siz;
            maxv = max(max(ls->maxv, rs->maxv), range.w);
            for (int i = 0; i < K; i++) {
                mmin[i] = min(range[i], min(ls->mmin[i], rs->mmin[i])),
                mmax[i] = max(range[i], max(ls->mmax[i], rs->mmax[i]));
            }
        }
        bool check() {
            return ls->siz > siz * alpha || rs->siz > siz * alpha;
        }
        bool in(const KCUBE &A) {
            for (int i = 0; i < K; i++) {
                if (A.a[i] > mmin[i] || A.b[i] < mmax[i]) {
                    return 0;
                }
            }
            return 1;
        }
        bool out(const KCUBE &A) {
            for (int i = 0; i < K; i++) {
                if (A.a[i] > mmax[i] || A.b[i] < mmin[i]) {
                    return 1;
                }
            }
            return false;
        }
        bool at(const KCUBE &A) {
            for (int i = 0; i < K; i++) {
                if (range[i] < A.a[i] || range[i] > A.b[i]) {
                    return false;
                }
            }
            return true;
        }
    } memory_pool[N], *tail, *nil, *rt, *recy[N];
    Point down;
    int top;
    const void init() {
        tail = memory_pool;
        nil  = tail++;
        for (int i = 0; i < K; i++) {
            nil->mmin[i] = INF;
            down[i] = nil->mmax[i] = -INF;
        }
        nil->ls = nil->rs = nil;
        rt                = nil;
    }
    Node *newnode(const Point &x) {
        Node *p = top ? recy[--top] : tail++;
        p->ls = p->rs = nil;
        p->range = p->mmin = p->mmax = x;
        p->maxv                      = x.w;
        p->siz                       = 1;
        return p;
    }
    Point px[N];
    int cnt;
    void assign(Node *p) {
        if (p == nil)
            return;
        assign(p->ls);
        px[++cnt]   = p->range;
        recy[top++] = p;
        assign(p->rs);
    }
    Node *rebuild(int l, int r, int d) {
        if (l > r) {
            return nil;
        }
        int mid = (l + r) / 2;
        D       = d;
        nth_element(px + l, px + mid, px + r + 1);
        Node *p = newnode(px[mid]);
        if (l == r)
            return p;
        p->ls = rebuild(l, mid - 1, (d + 1) % K);
        p->rs = rebuild(mid + 1, r, (d + 1) % K);
        return p->pushup(), p;
    }
    void rebuild(Node *&p) {
        cnt = 0;
        assign(p);
        p = rebuild(1, cnt, 0);
    }
    int query(Node *p, const KCUBE &Q) {
        if (p == nil) {
            return 0;
        }
        int ans = 0;
        if (p->out(Q))
            return ans;
        if (p->in(Q)) {
            ans = max(p->maxv, ans);
            return ans;
        }
        if (p->at(Q)) {
            ans = max(ans, p->range.w);
        }
        if (p->ls->maxv > ans)
            ans = max(query(p->ls, Q), ans);
        if (p->rs->maxv > ans)
            ans = max(query(p->rs, Q), ans);
        return ans;
    }
    Node **maintain(Node *&p, const Point &x, int d) {
        if (p == nil) {
            p = newnode(x);
            return &nil;
        }
        Node **bad;
        if (p->range[d] < x[d]) {
            bad = maintain(p->rs, x, (d + 1) % K);
        } else {
            bad = maintain(p->ls, x, (d + 1) % K);
        }
        p->pushup();
        if (p->check())
            bad = &p;
        return bad;
    }
    int query(const Point &up) {
        return query(rt, (KCUBE){down, up});
    }
    void insert(const Point &p) {
        Node **bad = maintain(rt, p, 0);
        if (*bad == nil) {
            return;
        }
        rebuild(*bad);
    }
};
} // namespace KDT
KDT::KDTree<3> tr;
KDT::Point a[N];
int n;
int main() {
    cin >> n;
    tr.init();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> a[i][j];
        }
    }
    sort(a + 1, a + n + 1);
    KDT::flag = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = a[i][j + 1];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        a[i].w = tr.query(a[i]) + 1;
        ans    = max(ans, a[i].w);
        tr.insert(a[i]);
    }
    cout << ans << endl;
    return 0;
}