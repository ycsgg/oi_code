#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll     = long long;
const ll mod = 1e9 + 7;
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
int T;
int main() {
    cin >> T;
    while (T--) {
        int cnt  = 0;
        int flag = 1;
        int n, m;
        cin >> n >> m;
        string s;
        for (int i = 1; i <= n; i++) {
            cin >> s;
            for (auto c : s) {
                cnt += (c == '#');
                flag &= (c != '0');
            }
        }
        cout << qpow(2, cnt) - flag << endl;
    }
    return 0;
}
// Asusetic eru quionours