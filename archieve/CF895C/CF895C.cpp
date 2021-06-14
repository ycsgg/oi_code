#include <iostream>
#include <vector>
using namespace std;
using ll          = long long;
const int prime[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                     31, 37, 41, 43, 47, 53, 59, 61, 67};
int p[30];
void insert(int x) {
    for (int i = 19; i >= 0; i--) {
        if (x & (1 << i)) {
            if (!p[i]) {
                p[i] = x;
            }
            x ^= p[i];
        }
    }
}
const ll mod = 1e9 + 7;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
int n;
int main() {
    cin >> n;
    vector<int> a(n);
    for (auto &v : a) {
        cin >> v;
        int res = 0;
        for (int j = 0; j < 19; j++) {
            if (v % prime[j])
                continue;
            int now = 0;
            while (v % prime[j] == 0) {
                v /= prime[j];
                now++;
            }
            now %= 2;
            res ^= (now << j);
        }
        insert(res);
    }
    for (int i = 0; i <= 19; i++) {
        if (p[i]) {
            n--;
        }
    }
    cout << (qpow(2, n) - 1ll + mod) % mod << endl;
    return 0;
}
// Asusetic eru quionours
