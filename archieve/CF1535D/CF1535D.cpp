#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
int ans[N];
char s[N];
void build(int rt, int l, int r) {
    if (l == r) {
        ans[rt] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    if (s[rt] == '?') {
        ans[rt] = ans[rt * 2] + ans[rt * 2 + 1];
    } else if (s[rt] == '0') {
        ans[rt] = ans[rt * 2 + 1];
    } else {
        ans[rt] = ans[rt * 2];
    }
}
int main() {
    int k;
    cin >> k >> (s + 1);
    int n = (1 << k);
    reverse(s + 1, s + n);
    build(1, 1, n);
    int q;
    cin >> q;
    while (q--) {
        int x;
        char ch;
        cin >> x >> ch;
        x = n - x;
        s[x] = ch;
        while (x) {
            if (s[x] == '?') {
                ans[x] = ans[x * 2] + ans[x * 2 + 1];
            } else if (s[x] == '0') {
                ans[x] = ans[x * 2 + 1];
            } else {
                ans[x] = ans[x * 2];
            }
            x /= 2;
        }
        cout << ans[1] << '\n';
    }
    return 0;
}
// Asusetic eru quionours.
