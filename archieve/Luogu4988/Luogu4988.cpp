#include <cmath>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
ll a, p, b;
ll mul(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res + a % m;
        }
        a = a + a % m;
        b /= 2;
    }
    return res;
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
map<ll, ll> hashk;
ll BSGS(ll a, ll b, ll p, ll c) {
    hashk.clear();
    ll m = sqrt(p) + 1;
    ll f = 1;
    for (int i = 0; i < m; i++) {
        hashk[f * b % p] = i;
        f                = f * a % p;
    }
    ll tempf = f;
    f        = f * c % p;
    for (int i = 1; i <= m; i++) {
        if (hashk.find(f) != hashk.end()) {
            return i * m - hashk[f];
        }
        f = f * tempf % p;
    }
    return -1;
}
ll exBSGS(ll a, ll b, ll p) {
    a = a % p;
    b = b % p;
    if (b == 1)
        return 0;
    if (a == 0 && b == 0)
        return 1;
    if (a == 0)
        return -1;
    if (b == 0) {
        ll x = 0, apgcd;
        while ((apgcd = gcd(a, p)) != 1) {
            x++;
            p /= apgcd;
            if (p == 1)
                return x;
        }
        return -1;
    }
    ll A = a, B = b, P = p, C = 1, apgcd, x = 0;
    while ((apgcd = gcd(A, P)) != 1) {
        if (B % apgcd) {
            return -1;
        }
        P /= apgcd;
        B /= apgcd;
        C = C * (A / apgcd) % P;
        x++;
        if (C == B) {
            return x;
        }
    }
    ll ans = BSGS(A, B, P, C);
    if (ans < 0) {
        return -1;
    } else {
        return x + ans;
    }
}
ll n, m, B;
ll tmp = 0;
int main() {
    cin >> n >> m >> B;
    B = ((B - n) % m + m) % m;
    tmp = exBSGS((2 * n - 1) % m, B, m);
    if (tmp == -1) {
        cout << "INF";
        return 0;
    }
    cout << tmp << endl;
}