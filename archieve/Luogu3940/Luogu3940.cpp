#include <array>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const int N = 150005;
const int K = 512;
int n, k;
array<int, N> a;
namespace Task1 {
array<bool, N * 2> vis;
array<int, N> ans;
int tot;
void solve() {
    int lim = n + 1;
    for (int i = n; i >= 1; i--) {
        int now   = sqrt(a[i]);
        bool flag = 0;
        for (int j = now; j <= K; j++) {
            if (j * j < a[i])
                continue;
            if (vis[j * j - a[i]]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            for (int j = i + 1; j < lim; j++) {
                vis[a[j]] = 0;
            }
            ans[++tot] = i;
            lim        = i + 1;
        }
        vis[a[i]] = 1;
    }
    cout << tot + 1 << endl;
    for (int i = tot; i >= 1; i--) {
        cout << ans[i] << " ";
    }
}
} // namespace Task1
namespace Task2 {
array<int, N * 2> fa, ans;
int tot;
vector<int> vis[N * 2];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void update(int l, int r) {
    for (int i = l + 1; i < r; i++) {
        vis[a[i]] = vector<int>();
    }
    ans[++tot] = l;
}
void solve() {
    int lim = n + 1;
    for (int i = 1; i <= n * 2; i++) {
        fa[i] = i;
    }
    for (int i = n; i >= 1; i--) {
        int now = sqrt(a[i]);
        for (int j = now; j <= K; j++) {
            if (j * j < a[i])
                continue;
            if (vis[j * j - a[i]].size()) {
                for (auto x : vis[j * j - a[i]]) {
                    if (find(x) == find(i)) {
                        update(i, lim);
                        lim = i + 1;
                        break;
                    } else {
                        fa[find(i + n)] = find(x);
                        fa[find(x + n)] = fa[find(i)];
                    }
                }
            }
        }
        vis[a[i]].push_back(i);
    }
    cout << tot + 1 << endl;
    for (int i = tot; i >= 1; i--) {
        cout << ans[i] << " ";
    }
}
} // namespace Task2

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if (k == 1) {
        Task1::solve();
    } else {
        Task2::solve();
    }
    return 0;
}
// Asusetic eru quionours