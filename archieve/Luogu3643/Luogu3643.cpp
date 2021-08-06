#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
const int N = 505;
constexpr ll mod = 1e9 + 7;
namespace ModInt {
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
modint qpow(modint a, long long b) {
    b %= mod - 1;
    if (b < 0) {
        b += mod - 1;
    }
    modint res(1);
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b /= 2;
    }
    return res;
}
modint inv(modint a) {
    return qpow(a, -1);
}
} // namespace ModInt
using ModInt::inv;
using ModInt::modint;
int n;
ll a[N], b[N], c[N * 2];
modint dp[N * 2];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        ++b[i];
        c[i * 2 - 1] = a[i];

        c[i * 2] = b[i];
    }
    sort(c + 1, c + 1 + n * 2);
    int tot = unique(c + 1, c + 1 + n * 2) - c - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(c + 1, c + 1 + tot, a[i]) - c;
        b[i] = lower_bound(c + 1, c + 1 + tot, b[i]) - c;
    }
    dp[0] = 1;
    for (int cur = 1; cur < tot; cur++) {
        int len = c[cur + 1] - c[cur];
        vector<modint> C(n + 1);
        C[0] = 1;
        for (int i = 1; i <= n; i++) {
            C[i] = C[i - 1] * (len + i - 1) * inv(i);
        }
        for (int i = n; i; i--) {
            if (a[i] <= cur && cur < b[i]) {
                int now = 1;
                for (int j = i - 1; ~j; j--) {
                    dp[i] += C[now] * dp[j];
                    if (a[j] <= cur && cur < b[j]) {
                        now++;
                    }
                }
            }
        }
    }
    modint ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dp[i];
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours