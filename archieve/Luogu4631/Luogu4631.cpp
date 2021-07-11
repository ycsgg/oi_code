#include <algorithm>
#include <iostream>
using namespace std;
const int N = 300010;
#define int long long
struct Point {
    int p[2];
    int &operator[](const int &x) {
        return p[x];
    }
    const int operator[](const int &x) const {
        return p[x];
    }
};
struct Circle {
    int id;
    int x, y, R;
    Point l, r;
} cir[N];
int s[N];
int vis[N];
namespace KDT {
struct Rectangle {
    Point l, r;
};
struct Node {
    int ls, rs;
    int id;
    Rectangle range;
} tr[N];
int tot;
void pushup(int x) {
    tr[x].range = Rectangle{cir[tr[x].id].l, cir[tr[x].id].r};
    if (tr[x].ls) {
        for (int i = 0; i < 2; i++) {
            tr[x].range.l[i] = min(tr[x].range.l[i], tr[tr[x].ls].range.l[i]);
            tr[x].range.r[i] = max(tr[x].range.r[i], tr[tr[x].ls].range.r[i]);
        }
    }
    if (tr[x].rs) {
        for (int i = 0; i < 2; i++) {
            tr[x].range.l[i] = min(tr[x].range.l[i], tr[tr[x].rs].range.l[i]);
            tr[x].range.r[i] = max(tr[x].range.r[i], tr[tr[x].rs].range.r[i]);
        }
    }
}
void build(int &x, int l, int r, int d) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    nth_element(s + l, s + mid, s + r + 1,
                [&](const int &a, const int &b) -> bool {
                    return d ? cir[a].x < cir[b].x : cir[a].y < cir[b].y;
                });
    x        = ++tot;
    tr[x].id = s[mid];
    build(tr[x].ls, l, mid - 1, d ^ 1);
    build(tr[x].rs, mid + 1, r, d ^ 1);
    pushup(x);
}
// A out of B
bool out(const Rectangle &A, const Rectangle &B) {
    bool ans = 0;
    for (int i = 0; i < 2; i++) {
        ans |= (A.r[i] < B.l[i] || B.r[i] < A.l[i]);
    }
    return ans;
}
bool check(int a, int b) {
    return (cir[a].x - cir[b].x) * (cir[a].x - cir[b].x) +
               (cir[a].y - cir[b].y) * (cir[a].y - cir[b].y) <=
           (cir[a].R + cir[b].R) * (cir[a].R + cir[b].R);
}
void solve(int x, const Rectangle &c, const int &id) {
    if (!x)
        return;
    if (out(tr[x].range, c))
        return;
    if (!vis[cir[tr[x].id].id] && check(tr[x].id, id)) {
        vis[cir[tr[x].id].id] = cir[id].id;
    }
    if (tr[x].ls)
        solve(tr[x].ls, c, id);
    if (tr[x].rs)
        solve(tr[x].rs, c, id);
}
} // namespace KDT
int n;
int root;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cir[i].x >> cir[i].y >> cir[i].R;
        cir[i].id   = i;
        cir[i].l[0] = cir[i].x - cir[i].R;
        cir[i].l[1] = cir[i].y - cir[i].R;
        cir[i].r[0] = cir[i].x + cir[i].R;
        cir[i].r[1] = cir[i].y + cir[i].R;
        s[i]        = i;
    }
    sort(cir + 1, cir + 1 + n, [&](const Circle &A, const Circle &B) -> bool {
        return (A.R == B.R) ? A.id < B.id : A.R > B.R;
    });
    KDT::build(root, 1, n, 0);
    for (int i = 1; i <= n; i++) {
        auto &id = cir[i].id;
        if (!vis[id]) {
            KDT::solve(root, KDT::Rectangle{cir[i].l, cir[i].r}, i);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << vis[i] << " ";
    }
}
// Asusetic eru quionours.