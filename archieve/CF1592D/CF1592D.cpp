#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
const int N = 1e3 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
    vector<int> &operator[](const int &x) {
        return edge[x];
    }
    const vector<int> &operator[](const int &x) const {
        return edge[x];
    }
} Tr;
int pos[N * 4], tot;
void dfs(int x, int pre) {
    pos[++tot] = x;
    for (auto v : Tr[x]) {
        if (v == pre) {
            continue;
        }
        dfs(v, x);
        pos[++tot] = x;
    }
}
int query(int l, int r) {
    set<int> s;
    for (int i = l; i <= r; i++) {
        s.insert(pos[i]);
    }
    printf("? %d", (int)s.size());
    for (auto &x : s) {
        printf(" %d", x);
    }
    printf("\n");
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}
void answer(int u, int v) {
    printf("! %d %d\n", u, v);
    fflush(stdout);
}
int a[N];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    fill(a, a + N, 0);
    dfs(1, 0);
    int l = 1, r = tot;
    int mmax = query(l, r);
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (query(l, mid) == mmax) {
            r = mid;
        } else {
            l = mid;
        }
    }
    answer(pos[l], pos[r]);
    return 0;
}
// Asusetic eru quionours.