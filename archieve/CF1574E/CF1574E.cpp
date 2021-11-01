#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 1e6 + 10;
int n, m, q;
int empty_row, empty_col;
int ban_row, ban_col;
int has_row[N][2], has_col[N][2];
map<int, int> cell[N];
int flag[2];
void del(int x, int y) {
    int z = (x + y + cell[x][y]) & 1;
    flag[z]--;
    --has_row[x][z];
    --has_col[y][z];
    if (!has_row[x][z]) {
        if (has_row[x][z ^ 1]) {
            ban_row--;
        } else {
            empty_row++;
        }
    }
    if (!has_col[y][z]) {
        if (has_col[y][z ^ 1]) {
            ban_col--;
        } else {
            empty_col++;
        }
    }
    cell[x].erase(y);
}
void add(int x, int y, int z) {
    cell[x][y] = z;
    z = (z + x + y) & 1;
    flag[z]++;
    if (!has_row[x][z]) {
        if (has_row[x][z ^ 1]) {
            ban_row++;
        } else {
            empty_row--;
        }
    }
    if (!has_col[y][z]) {
        if (has_col[y][z ^ 1]) {
            ban_col++;
        } else {
            empty_col--;
        }
    }
    has_row[x][z]++;
    has_col[y][z]++;
}
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> q;
    empty_row = n;
    empty_col = m;
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (z == -1) {
            if (cell[x].count(y)) {
                del(x, y);
            }
        } else {
            if (cell[x].count(y)) {
                del(x, y);
            }
            add(x, y, z);
        }
        ll ans = ((ban_row ? 0 : qpow(2, empty_row)) +
                  (ban_col ? 0 : qpow(2, empty_col))) %
                 mod;
        ans = (ans - (flag[0] == 0) - (flag[1] == 0) + mod) % mod;
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.