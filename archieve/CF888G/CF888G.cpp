#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int n;
int a[N];
namespace Trie {
int ch[N * 20 + 10][2], cnt, rt = 0;
void insert(int x) {
    int now = rt;
    for (int i = 30; i >= 0; i--) {
        int d = (x >> i) & 1;
        if (!ch[now][d]) {
            ch[now][d] = ++cnt;
        }
        now = ch[now][d];
    }
}
int find(int p1, int p2, int d) {
    if (d < 0)
        return 0;
    int res0 = -1, res1 = -1;
    if (ch[p1][0] && ch[p2][0]) {
        res0 = find(ch[p1][0], ch[p2][0], d - 1);
    }
    if (ch[p1][1] && ch[p2][1]) {
        res1 = find(ch[p1][1], ch[p2][1], d - 1);
    }
    if (res0 != -1 || res1 != -1) {
        if (res0 != -1 && res1 != -1) {
            return min(res0, res1);
        }
        return res0 + res1 + 1;
    }
    if (ch[p1][1] && ch[p2][0]) {
        res0 = find(ch[p1][1], ch[p2][0], d - 1) + (1 << d);
    }
    if (ch[p1][0] && ch[p2][1]) {
        res1 = find(ch[p1][0], ch[p2][1], d - 1) + (1 << d);
    }
    if (res0 != -1 || res1 != -1) {
        if (res0 != -1 && res1 != -1) {
            return min(res0, res1);
        }
        return res0 + res1 + 1;
    }
    return 0;
}
} // namespace Trie
long long ans = 0;
void dfs(int x, int d) {
    using namespace Trie;
    if (d < 0)
        return;
    if (ch[x][0] && ch[x][1]) {
        ans += find(ch[x][0], ch[x][1], d - 1) + (1 << d);
        dfs(ch[x][0], d - 1);
        dfs(ch[x][1], d - 1);
        return;
    }
    if (ch[x][0])
        dfs(ch[x][0], d - 1);
    if (ch[x][1])
        dfs(ch[x][1], d - 1);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n;i++){
        Trie::insert(a[i]);
    }
        dfs(Trie::rt, 30);
    cout << ans;
    return 0;
}
// Asusetic eru quionours