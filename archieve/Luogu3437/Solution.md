### P3437 [POI2006]TET-Tetris 3D

标记永久化+二维线段树

二维线段树无脑套一层就可以，但是传标记发现不太好向内传标记，所以借助标记永久化的思路不对标记进行操作

而是查询的时候统计贡献，因为 $\max$ 单调不降所以可行

```cpp
#include <iostream>
using namespace std;
const int N = 1050;
int n, m, p;
namespace Tree {
struct SegmentTreeY {
    int mmax[N * 2], tag[N * 2];
    int query(int rt, int l, int r, int L, int R) {
        if (l > R || r < L)
            return -1e9;
        if (l >= L && r <= R)
            return max(mmax[rt], tag[rt]);
        int mid = (l + r) >> 1;
        int Tag = tag[rt];
        return max(Tag, max(query(rt * 2, l, mid, L, R),
                            query(rt * 2 + 1, mid + 1, r, L, R)));
    }
    void update(int rt, int l, int r, int L, int R, int v) {
        if (l > R || r < L)
            return;
        mmax[rt] = max(mmax[rt], v);
        if (l >= L && r <= R) {
            tag[rt] = max(tag[rt], v);
            return;
        }
        int mid = (l + r) >> 1;
        update(rt * 2, l, mid, L, R, v);
        update(rt * 2 + 1, mid + 1, r, L, R, v);
    }
};
struct SegmentTreeX {
    SegmentTreeY tag[N * 2], mmax[N * 2];
    int query(int rt, int l, int r, int L, int R, int down, int up) {
        if (l > R || r < L)
            return -1e9;
        if (l >= L && r <= R)
            return mmax[rt].query(1, 1, m, down, up);
        int mid = (l + r) >> 1;
        int Tag = tag[rt].query(1, 1, m, down, up);
        return max(Tag, max(query(rt * 2, l, mid, L, R, down, up),
                            query(rt * 2 + 1, mid + 1, r, L, R, down, up)));
    }
    void update(int rt, int l, int r, int L, int R, int down, int up, int v) {
        if (l > R || r < L)
            return;
        mmax[rt].update(1, 1, m, down, up, v);
        if (l >= L && r <= R) {
            tag[rt].update(1, 1, m, down, up, v);
            return;
        }
        int mid = (l + r) >> 1;
        update(rt * 2, l, mid, L, R, down, up, v);
        update(rt * 2 + 1, mid + 1, r, L, R, down, up, v);
    }
};

} // namespace Tree
Tree::SegmentTreeX T;
int main() {
    cin >> n >> m >> p;
    while (p--) {
        int d, s, h, x, y;
        cin >> d >> s >> h >> x >> y;
        h += T.query(1, 1, n, x + 1, x + d, y + 1, y + s);
        T.update(1, 1, n, x + 1, x + d, y + 1, y + s, h);
    }
    cout << T.query(1, 1, n, 1, n, 1, m);
    return 0;
}
// Asusetic eru quionours
```

