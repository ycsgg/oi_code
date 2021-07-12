#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
#define int long long
const int N = 100005;
struct Point {
    int p[2];
    int id;
    int &operator[](const int &x) {
        return p[x];
    }
    const int &operator[](const int &x) const {
        return p[x];
    }
} a[N];
int dis(const Point &A, const Point &B) {
    return (A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]);
}
unordered_map<int, bool> del[N];
namespace KDT {
struct Rectangle {
    Point l, r;
};
struct Node {
    Point p;
    Rectangle range;
    int ls, rs;
} tr[N];
int tot;
void pushup(int x) {
    for (int i = 0; i < 2; i++) {
        tr[x].range.l[i] = tr[x].range.r[i] = tr[x].p[i];
        if (tr[x].ls) {
            tr[x].range.l[i] = min(tr[x].range.l[i], tr[tr[x].ls].range.l[i]);
            tr[x].range.r[i] = max(tr[x].range.r[i], tr[tr[x].ls].range.r[i]);
        }
        if (tr[x].rs) {
            tr[x].range.l[i] = min(tr[x].range.l[i], tr[tr[x].rs].range.l[i]);
            tr[x].range.r[i] = max(tr[x].range.r[i], tr[tr[x].rs].range.r[i]);
        }
    }
}
void build(int &x, int l, int r, int d) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    nth_element(a + l, a + mid, a + r + 1,
                [&](const Point &A, const Point &B) -> bool {
                    return A[d] < B[d];
                });
    x       = ++tot;
    tr[x].p = a[mid];
    if (l < mid)
        build(tr[x].ls, l, mid - 1, d ^ 1);
    if (r > mid)
        build(tr[x].rs, mid + 1, r, d ^ 1);
    pushup(x);
}
struct Ans {
    Point x, y;
    int dis;
    bool operator<(const Ans &B) const {
        return dis < B.dis;
    }
} res;
int getdis(Rectangle range, Point p) {
    int res = 0;
    for (int i = 0; i < 2; i++) {
        res += max(p[i] - range.l[i], range.r[i] - p[i]) *
               max(p[i] - range.l[i], range.r[i] - p[i]);
    }
    return res;
}
void solve(int x, Point p) {
    if (!del[p.id].count(tr[x].p.id) && dis(tr[x].p, p) > res.dis) {
        res.y   = tr[x].p;
        res.dis = dis(tr[x].p, p);
    }
    int disl = 0, disr = 0;
    if (tr[x].ls) {
        disl = getdis(tr[tr[x].ls].range, p);
    }
    if (tr[x].rs) {
        disr = getdis(tr[tr[x].rs].range, p);
    }
    if (disl > disr) {
        if (disl > res.dis) {
            solve(tr[x].ls, p);
        }
        if (disr > res.dis) {
            solve(tr[x].rs, p);
        }
    } else {
        if (disr > res.dis) {
            solve(tr[x].rs, p);
        }
        if (disl > res.dis) {
            solve(tr[x].ls, p);
        }
    }
}
} // namespace KDT
int root;
int n, k;

priority_queue<KDT::Ans> q;
signed main() {
    cin >> n >> k;
    k *= 2;
    for (int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i].id = i;
    }
    KDT::build(root, 1, n, 0);
    for (int i = 1; i <= n; i++) {
        KDT::res.x = KDT::res.y = a[i];
        KDT::res.dis            = 0;
        KDT::solve(root, a[i]);
        q.push(KDT::res);
        del[KDT::res.x.id][KDT::res.y.id] = 1;
    }
    KDT::Ans ans;
    while (k--) {
        auto now = q.top();
        q.pop();
        ans        = now;
        KDT::res.x = KDT::res.y = now.x;
        KDT::res.dis            = 0;
        KDT::solve(root, now.x);
        q.push(KDT::res);
        del[KDT::res.x.id][KDT::res.y.id] = 1;
    }
    cout << ans.dis;
    return 0;
}
// Asusetic eru quionours