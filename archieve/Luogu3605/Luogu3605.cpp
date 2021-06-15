#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
int n;
namespace BIT {
array<int, N> c;
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int v) {
    while (pos <= n) {
        c[pos] += v;
        pos += lowbit(pos);
    }
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
} // namespace BIT
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G;
array<int, N> ans;
vector<int> a, b;
void dfs(int x) {
    ans[x] -= BIT::query(n) - BIT::query(a[x]);
    for (auto v : G.edge[x]) {
        dfs(v);
    }
    ans[x] += BIT::query(n) - BIT::query(a[x]);
    BIT::add(a[x], 1);
}
int main() {
    cin >> n;
    a.resize(n + 1);
    b.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        G.add(fa, i);
    }
    sort(b.begin() + 1, b.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
}