#include <cstdio>
#include <iostream>
using namespace std;
using ll = long long;
const int N = 2400;
const int mod = 2333;
ll C[N + 2][N + 2];
ll pre[N + 2][N + 2];
ll Lucas(ll n, ll m) {
    if (!m) {
        return 1;
    }
    if (n == m) {
        return 1;
    }
    if (n < m) {
        return 0;
    }
    return C[n % mod][m % mod] * Lucas(n / mod, m / mod) % mod;
}
ll F(ll n, ll k) {
    if (k < 0)
        return 0;
    if (!n || !k) {
        return 1;
    }
    if (n < mod && k < mod) {
        return pre[n][k];
    }
    return (F(n / mod, k / mod - 1) * pre[n % mod][mod - 1] % mod +
            Lucas(n / mod, k / mod) * pre[n % mod][k % mod] % mod) %
           mod;
}
void init() {
    C[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        C[i][i] = C[i][0] = 1;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
    pre[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        pre[i][0] = 1;
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            pre[i][j] = (C[i][j] + pre[i][j - 1]) % mod;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();
    int _;
    cin >> _;
    while (_--) {
        ll n, k;
        cin >> n >> k;
        cout << F(n, k) << '\n';
    }
    return 0;
}
// Asusetic eru quionours.