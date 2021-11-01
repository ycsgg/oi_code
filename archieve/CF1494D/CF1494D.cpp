#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 505;
int n;
struct Node {
    int val, x, y;
} a[N * N];
int val[N * N];
namespace DSU {
int fa[N * N];
void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
} // namespace DSU
int tot;
int fa[N * N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    DSU::init(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            if (i > j) {
                continue;
            }
            if (i == j) {
                val[i] = x;
            }
            a[++tot].val = x;
            a[tot].x = i;
            a[tot].y = j;
        }
    }
    sort(a + 1, a + 1 + tot, [&](const auto &A, const auto &B) -> bool {
        if (A.val == B.val) {
            return A.x < B.x;
        }
        return A.val < B.val;
    });
    int cnt = n;
    for (int i = 1; i <= tot; i++) {
        auto u = DSU::find(a[i].x);
        auto v = DSU::find(a[i].y);
        if (u == v) {
            continue;
        }
        int mmax = max(val[u], val[v]);
        if (mmax == a[i].val) {
            if (val[u] == a[i].val) {
                DSU::fa[v] = u;
                fa[v] = u;
            } else {
                DSU::fa[u] = v;
                fa[u] = v;
            }
        } else if (mmax < a[i].val) {
            ++cnt;
            DSU::fa[cnt] = cnt;
            val[cnt] = a[i].val;
            fa[u] = fa[v] = cnt;
            DSU::fa[u] = DSU::fa[v] = cnt;
        }
    }

    cout << cnt << '\n';

    int rt = 0;
    for (int i = 1; i <= cnt; i++) {
        if (DSU::find(i) == i) {
            rt = i;
        }
        cout << val[i] << ' ';
    }
    cout << '\n';
    cout << rt << '\n';
    for (int i = 1; i <= cnt; i++) {
        if (i != rt) {
            cout << i << ' ' << fa[i] << '\n';
        }
    }

    return 0;
}
// Asusetic eru quionours.