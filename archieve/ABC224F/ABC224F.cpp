#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
using ll = long long;
const ll mod = 998244353;
const ll inv40 = 573990503;
char s[N];
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
    cin >> (s + 1);
    int n = strlen(s + 1);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll tmp = ((qpow(5, n - i + 1) * 9ll % mod) - 5 + mod) % mod;
        tmp = (tmp * inv40) % mod;
        tmp = (tmp * (s[i] - '0')) % mod;
        ans = (ans + tmp) % mod;
    }
    cout << ans * qpow(2, n - 1) % mod << '\n';
    return 0;
}
// Asusetic eru quionours.