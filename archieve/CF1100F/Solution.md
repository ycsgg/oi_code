###  CF1100F Ivan and Burgers

先离线下来排好序，思考一下发现插入线性基的过程中可以记录一下某个线性基最晚在什么时刻达到，贪心的取最大的时刻肯定不劣，查询直接查大于等于 $l$ 的线性基即可

$O(n\log n)$

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
const int N = 5e5 + 5;
namespace XorBasis {
const int LIM = 20;
array<int, LIM> basis, pos;
void insert(int x, int id) {
    for (int i = LIM; ~i; i--) {
        if ((x >> i) & 1) {
            if (!basis[i]) {
                basis[i] = x;
                pos[i]   = id;
                return;
            }
            if (pos[i] < id) {
                swap(pos[i], id);
                swap(x, basis[i]);
            }
            x ^= basis[i];
        }
    }
}
int query(int l, int r) {
    int res = 0;
    for (int i = LIM; ~i; i--) {
        if (pos[i] >= l) {
            res = max(res, res ^ basis[i]);
        }
    }
    return res;
}
} // namespace XorBasis
int n, q;
struct Query {
    int id, l, r;
};
vector<Query> c;
int main() {
    cin >> n;
    vector<int> a(n);
    for (auto &v : a) {
        cin >> v;
    }
    cin >> q;
    c.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> c[i].l >> c[i].r;
        c[i].r--;
        c[i].l--;
        c[i].id = i;
    }
    sort(c.begin(), c.end(), [&](const Query &A, const Query &B) -> bool {
        if (A.r == B.r) {
            return A.l < B.l;
        }
        return A.r < B.r;
    });
    int nowr = -1;
    vector<int> ans(q);
    for (auto qr : c) {
        while (nowr < qr.r) {
            nowr++;
            XorBasis::insert(a[nowr], nowr);
        }
        ans[qr.id] = XorBasis::query(qr.l, qr.r);
    }
    for (auto p : ans) {
        printf("%d\n", p);
    }
    return 0;
}
// Asusetic eru quionours
```