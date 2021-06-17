#include <array>
#include <iostream>
using namespace std;
const int N = 1e6 + 10;
array<int, N> siz, head, nxt, col, c;
int n, m, ans;
void merge(int x, int y) {
    if (!siz[x] || x == y) {
        return;
    }
    for (int i = head[x]; ~i; i = nxt[i]) {
        ans -= (c[i - 1] == y) + (c[i + 1] == y);
    }
    for (int i = head[x]; ~i; i = nxt[i]) {
        c[i] = y;
        if (nxt[i] == -1) {
            nxt[i]  = head[y];
            head[y] = head[x];
            break;
        }
    }
    siz[y] += siz[x];
    siz[x]  = 0;
    head[x] = -1;
}
int main() {
    cin >> n >> m;
    head.fill(-1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        col[c[i]]  = c[i];
        nxt[i]     = head[c[i]];
        head[c[i]] = i;
        siz[c[i]]++;
        ans += (c[i] != c[i - 1]);
    }
    while (m--) {
        int opt, x, y;
        cin >> opt;
        if (opt == 2) {
            cout << ans << endl;
        } else {
            cin >> x >> y;
            if (siz[col[x]] > siz[col[y]]) {
                swap(col[x], col[y]);
            }
            merge(col[x], col[y]);
        }
    }
}
// Asusetic eru quionours.