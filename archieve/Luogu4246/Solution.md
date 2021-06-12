### P4246 [SHOI2008]堵塞的交通

只有两行的网格图，考虑每个区间的走法比较固定，为了满足合并的需求，仅需要记录

- 左上 -> 左下
- 右上 -> 右下
- 左上 -> 右上
- 左下 -> 右下
- 左上 -> 右下
- 左下 -> 右上

六种状态，pushup和查询的时候需要好好考虑下能走的路径，尤其查询的时候是可以从 $[1,l]$ $[r,n]$ 绕行的

```cpp
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
bool state[N][2];
//(_,x) -> (_,x+1) connect
namespace SegmentTree {
#define ls(x) x * 2
#define rs(x) x * 2 + 1
struct Node {
    int L, R;
    bool l, r, u, d, x, y;
    // x : left up -> right down
    // y : left down -> right up
} tr[N << 2];
void pushup(Node &x, Node l, Node r) {
    x.L = l.L;
    x.R = r.R;
    x.l = l.l | (l.u & state[l.R][0] & r.l & state[l.R][1] & l.d);
    x.r = r.r | (r.u & state[l.R][0] & l.r & state[l.R][1] & r.d);
    x.u = (l.u & state[l.R][0] & r.u) | (l.x & state[l.R][1] & r.y);
    x.d = (l.d & state[l.R][1] & r.d) | (l.y & state[l.R][0] & r.x);
    x.x = (l.u & state[l.R][0] & r.x) | (l.x & state[l.R][1] & r.d);
    x.y = (l.d & state[l.R][1] & r.y) | (l.y & state[l.R][0] & r.u);
}
void pushup(int rt) {
    pushup(tr[rt], tr[ls(rt)], tr[rs(rt)]);
}
void build(int rt, int l, int r) {
    if (l == r) {
        tr[rt].L = tr[rt].R = l;
        tr[rt].u = tr[rt].d = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
void modify_row(int rt, int pos, int row, bool val) { // in one row
    int l = tr[rt].L, r = tr[rt].R;
    int mid = (l + r) >> 1;
    if (mid == pos) {
        state[pos][row] = val;
        pushup(rt);
        return;
    }
    if (mid >= pos) {
        modify_row(ls(rt), pos, row, val);
    } else {
        modify_row(rs(rt), pos, row, val);
    }
    pushup(rt);
}
void modify_col(int rt, int pos, bool val) { // in one col
    int l = tr[rt].L, r = tr[rt].R;
    if (l == r) {
        tr[rt].l = tr[rt].r = tr[rt].x = tr[rt].y = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= pos) {
        modify_col(ls(rt), pos, val);
    } else {
        modify_col(rs(rt), pos, val);
    }
    pushup(rt);
}
Node query(int rt, int L, int R) {
    int l = tr[rt].L, r = tr[rt].R;
    if (l >= L && r <= R)
        return tr[rt];
    int mid = (l + r) >> 1;
    if (mid < L) {
        return query(rs(rt), L, R);
    }
    if (mid >= R) {
        return query(ls(rt), L, R);
    }
    Node ans;
    pushup(ans, query(ls(rt), L, R), query(rs(rt), L, R));
    return ans;
}
#undef ls
#undef rs
} // namespace SegmentTree
int n;
char s[15];
int main() {
    cin >> n;
    SegmentTree::build(1, 1, n);
    while (cin >> s && s[0] != 'E') {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (s[0] == 'O') {
            if (a == c) {
                SegmentTree::modify_row(1, min(b, d), a - 1, 1);
            } else {
                SegmentTree::modify_col(1, b, 1);
            }
        } else if (s[0] == 'C') {
            if (a == c) {
                SegmentTree::modify_row(1, min(b, d), a - 1, 0);
            } else {
                SegmentTree::modify_col(1, b, 0);
            }
        } else {
            if (b > d) {
                swap(a, c);
                swap(b, d);
            }
            SegmentTree::Node now  = SegmentTree::query(1, b, d);
            SegmentTree::Node resl = SegmentTree::query(1, 1, b);
            SegmentTree::Node resr = SegmentTree::query(1, d, n);
            bool ans               = 0;
            if (a == 1) {
                if (c == 1) { // up & up
                    ans = now.u | (resl.r & now.y) | (now.x & resr.l) |
                          (resl.r & now.d & resr.l);
                } else { // up & down
                    ans = now.x | (resl.r & now.d) | (now.u & resr.l) |
                          (resl.r & now.y & resr.l);
                }
            } else {
                if (c == 1) { // down & up
                    ans = now.y | (resl.r & now.u) | (now.d & resr.l) |
                          (resl.r & now.x & resr.l);
                } else { // down & down
                    ans = now.d | (resl.r & now.x) | (now.y & resr.l) |
                          (resl.r & now.u & resr.l);
                }
            }
            cout << (ans ? "Y" : "N") << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours
```

