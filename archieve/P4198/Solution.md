### P4198 楼房重建

https://www.luogu.com.cn/problem/P4198

思路比较奇妙的一道

其实就是找到斜率递增的点的个数

难点主要在区间合并上

因为左区间能看到的在父区间里都可以看到，所以左边直接合并

右区间则需要大于左区间最大斜率，只能合并比它大的答案

具体来说是右区间的左区间如果小于需要的斜率就忽略,扫右区间

否则的话因为右区间的右区间仍然被左区间挡住了，所以只查询左区间大于需要的斜率再加上右区间能看到了（11，12行）

需要注意的是$ans[rt]-ans[rt*2]$不能换成查询右区间，因为右区间的查询不会算上被左边挡住的（而且会T）被坑*1

```cpp
#include <iostream>
using namespace std;
const int N = 100005;
int n, m;
int ans[N * 4];
double val[N * 4];
int query(int rt, int l, int r, double k) {
    if (val[rt] <= k)
        return 0;
    if (l == r)
        return val[rt] > k;
    if ((val[rt * 2] <= k)) {
        return query(rt * 2 + 1, (l + r) / 2 + 1, r, k);
    }
    return query(rt * 2, l, (l + r) / 2, k) + ans[rt] - ans[rt * 2];
}
void update(int rt, int l, int r, int pos, double v) {
    if (l == r) {
        ans[rt] = 1;
        val[rt] = v;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(rt * 2, l, mid, pos, v);
    } else {
        update(rt * 2 + 1, mid + 1, r, pos, v);
    }
    val[rt] = max(val[rt * 2], val[rt * 2 + 1]);
    ans[rt] = ans[rt * 2] + query(rt * 2 + 1, mid + 1, r, val[rt * 2]);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        update(1, 1, n, x, (double)y / x);
        cout << ans[1] << endl;
    }
}
```

