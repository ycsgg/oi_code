#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
namespace Maker {
unsigned int x0, seed;
void init() {
    scanf("%u%u", &x0, &seed);
}
inline unsigned int getnum() {
    x0 = (x0 << 3) ^ x0;
    x0 = ((x0 >> 5) + seed) ^ x0;
    return x0;
}
} // namespace Maker
const int N = 100005;
void ckmax(unsigned int &x, unsigned int v) {
    x < v ? x = v : 0;
}
int n, m;
int lg[N];
unsigned int st[N][17];
void prework() {
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
}
void update(int l, int r, unsigned int v) {
    const int k = lg[r - l + 1];
    ckmax(st[l][k], v);
    ckmax(st[r - (1 << k) + 1][k], v);
}
void solve() {
    for (int j = 16; j >= 1; --j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            ckmax(st[i][j - 1], st[i][j]);
            ckmax(st[i + (1 << (j - 1))][j - 1], st[i][j]);
        }
}
int typ;
int main() {
    cin >> n >> m >> typ;
    for (int i = 1; i <= n; ++i) {
        cin >> st[i][0];
    }
    prework();
    Maker::init();
    for (int i = 1; i <= m; ++i) {
        int l = Maker::getnum() % n + 1, r = Maker::getnum() % n + 1;
        unsigned int v = Maker::getnum();
        if (l > r)
            swap(l, r);
        if (typ == 1)
            l = 1;
        update(l, r, v);
    }
    solve();
    for (int i = 1; i <= n; ++i) {
        cout << st[i][0] << " ";
    }
    return 0;
}