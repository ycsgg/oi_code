#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
const int N = 5e4 + 20;
int n, m, s, k;
struct Edge {
    int u, v, w;
    bool operator<(const Edge &B) const {
        if (w == B.w) {
            bool flag = (u == s || v == s);
            if (flag) {
                return true;
            } else {
                return false;
            }
        }
        return w < B.w;
    }
};
vector<Edge> e1, e2, E;
namespace DSU {
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return 0;
    } else {
        fa[x] = y;
    }
    return 1;
}
void init() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}
} // namespace DSU
auto check(int x) {
    for (auto &e : e1) {
        e.w += x;
    }
    merge(e1.begin(), e1.end(), e2.begin(), e2.end(), E.begin());
    for (auto &e : e1) {
        e.w -= x;
    }
    DSU::init();
    int tot = n;
    int cnt = 0, res = 0;
    for (auto e : E) {
        if (DSU::find(e.u) == DSU::find(e.v))
            continue;
        DSU::merge(e.u, e.v);
        cnt += (e.u == s || e.v == s);
        res += e.w;
        --tot;
        if (tot == 1) {
            break;
        }
    }
    return make_pair(cnt, res);
}
int main() {
    cin >> n >> m >> s >> k;
    E.resize(m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == s || v == s) {
            e1.push_back({u, v, w});
        } else {
            e2.push_back({u, v, w});
        }
    }
    if (e1.size() < k) {
        cout << "Impossible" << endl;
        return 0;
    }

    int block = n;
    DSU::init();
    for (auto e : e1) {
        block -= DSU::merge(e.u, e.v);
    }
    for (auto e : e2) {
        block -= DSU::merge(e.u, e.v);
    }
    if (block != 1) {
        cout << "Impossible" << endl;
        return 0;
    }

    sort(e1.begin(), e1.end());
    sort(e2.begin(), e2.end());
    int l = -1e8, r = 1e8, ans = -1e8;
    if (check(l).first < k) {
        cout << "Impossible" << endl;
        return 0;
    }
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid).first >= k) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (check(ans).first != k) {
        cout << "Impossible" << endl;
        return 0;
    }
    cout << check(ans).second - k * ans << endl;
    return 0;
}
// Asusetic eru quionours