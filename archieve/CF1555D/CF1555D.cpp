#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
const char pattern[][4] = {"abc", "acb", "bac", "bca", "cab", "cba"};
char s[N];
int res[6][N];
int n, q;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;
    cin >> (s + 1);

    int tot = 0;

    for (auto pat : pattern) {
        int cnt = 0;
        int cur = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i] != pat[cur]) {
                cnt++;
            }
            cur = (cur + 1) % 3;
            res[tot][i] = cnt;
        }
        tot++;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (r - l + 1 <= 2) {
            if (l == r || s[l] != s[r]) {
                cout << 0 << '\n';
            } else {
                cout << 1 << '\n';
            }
            continue;
        }
        int ans = r - l + 1;
        for (int i = 0; i < tot; i++) {
            ans = min(ans, res[i][r] - res[i][l - 1]);
        }
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.