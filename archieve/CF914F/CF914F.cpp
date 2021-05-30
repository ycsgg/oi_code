#include <bitset>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
bitset<N> p[28], res;
char s[N], tmp[N];
int n;
int main() {
    cin >> s + 1;
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        p[s[i] - 'a'].set(i);
    }
    int q;
    cin >> q;
    while (q--) {
        int opt, pos, l, r;
        cin >> opt;
        if (opt == 1) {
            char c;
            cin >> pos >> c;
            p[s[pos] - 'a'].reset(pos);
            s[pos] = c;
            p[s[pos] - 'a'].set(pos);
        } else {
            cin >> l >> r >> tmp + 1;
            int len = strlen(tmp + 1);
            res.set();
            r = r - len + 1;
            for (int i = 1; i <= len; i++) {
                res &= p[tmp[i] - 'a'] >> (i - 1);
            }
            int lcnt = (res >> l).count();
            int rcnt = (res >> (r + 1)).count();
            cout << max(lcnt - rcnt, 0) << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours