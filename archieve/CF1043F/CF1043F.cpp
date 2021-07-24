#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll     = long long;
const ll mod = 1e9 + 7;
const int N  = 3e5 + 5;
struct modint {
    ll val;
    modint() {
    }
    modint(ll v) {
        val = v;
    }
    modint(const modint &v) {
        val = v.val;
    }
    modint &operator=(const modint &b) {
        val = b.val;
        return *this;
    }
    modint &operator=(const ll &b) {
        val = b;
        return *this;
    }
};
modint operator+(const modint &a, const ll &b) {
    return modint((a.val + b) % mod);
}
modint operator+(const ll &b, const modint &a) {
    return modint((a.val + b) % mod);
}
modint operator+(const modint &a, const modint &b) {
    return modint((a.val + b.val) % mod);
}
modint operator-(const modint &a, const ll &b) {
    return modint((a.val - b + mod) % mod);
}
modint operator-(const ll &b, const modint &a) {
    return modint((b - a.val + mod) % mod);
}
modint operator-(const modint &a, const modint &b) {
    return modint((a.val - b.val + mod) % mod);
}
modint operator*(const modint &a, const ll &b) {
    return modint((a.val * b) % mod);
}
modint operator*(const ll &b, const modint &a) {
    return modint((a.val * b) % mod);
}
modint operator*(const modint &a, const modint &b) {
    return modint((a.val * b.val) % mod);
}
modint &operator+=(modint &a, const modint &b) {
    return a = a + b;
}
modint &operator+=(modint &a, const ll &b) {
    return a = a + b;
}
modint &operator-=(modint &a, const modint &b) {
    return a = a - b;
}
modint &operator-=(modint &a, const ll &b) {
    return a = a - b;
}
modint &operator*=(modint &a, const modint &b) {
    return a = a * b;
}
modint &operator*=(modint &a, const ll &b) {
    return a = a * b;
}
ostream &operator<<(ostream &out, const modint &v) {
    out << v.val;
    return out;
}
int n;
modint fac[N], ifac[N];
modint qpow(modint a, int b) {
    modint res(1);
    while (b) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
        b /= 2;
    }
    return res;
}
modint C(int n, int m) {
    if (n < m) {
        return 0;
    }
    return fac[n] * ifac[m] * ifac[n - m];
}
array<int, N> cnt, divcnt;
array<modint, N> dp, a;
int main() {
    cin >> n;
    ll lim = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].val;
        cnt[a[i].val]++;
        lim = max(lim, a[i].val);
    }
    n      = lim;
    fac[1] = ifac[1] = fac[0] = ifac[0] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = fac[i - 1] * i;
    }
    ifac[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 2; i >= 2; i--) {
        ifac[i] = ifac[i + 1] * (i + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            divcnt[i] += cnt[j];
        }
    }
    for (int k = 1; k <= 7; k++) {
        for (int i = n; i >= 1; i--) {
            dp[i] = C(divcnt[i], k);
            for (int j = i * 2; j <= n; j += i) {
                dp[i] -= dp[j];
            }
        }
        if (dp[1].val) {
            cout << k << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
// Asusetic eru quionours
