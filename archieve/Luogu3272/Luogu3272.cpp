#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 105;
const int mod = 20110520;
int n, m;
int mp[N][N];
ll p3[N];
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

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (n < m) {
                mp[j][i] = (c == '_');
            } else {
                mp[i][j] = (c == '_');
            }
        }
    }
    if (n < m) {
        swap(n, m);
    }
    p3[0] = 1;
    for (int i = 1; i <= m + 1; i++) {
        p3[i] = p3[i - 1] * 3;
    }
    vector<modint> dp[2];
    dp[0].reserve(p3[m + 1]);
    dp[1].reserve(p3[m + 1]);
    dp[0][0] = 1;
    int cur = 0;
    static auto getpos = [&](int x, int pos) {
        return (x / p3[pos]) % 3;
    };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[cur ^ 1].assign(p3[m + 1], 0);
            for (int S = 0; S < p3[m + 1]; S++) {
                if (!dp[cur][S].val)
                    continue;
                auto l = getpos(S, j - 1);
                auto r = getpos(S, j);
                if (!mp[i][j]) {
                    if (!l && !r) {
                        dp[cur ^ 1][S] += dp[cur][S];
                    }
                    continue;
                }
                if (!l && !r) {         // no pin
                    if (mp[i + 1][j]) { // down
                        dp[cur ^ 1][S + p3[j - 1]] += dp[cur][S];
                    }
                    if (mp[i][j + 1]) { // right
                        dp[cur ^ 1][S + p3[j]] += dp[cur][S];
                    }
                    if (mp[i + 1][j] && mp[i][j + 1]) { // rotate
                        dp[cur ^ 1][S + 2 * p3[j - 1] + 2 * p3[j]] +=
                            dp[cur][S];
                    }
                } else if (l && !r) {
                    if (mp[i][j + 1]) { // continue
                        dp[cur ^ 1][S - l * p3[j - 1] + l * p3[j]] +=
                            dp[cur][S];
                    }
                    if (l == 1 && mp[i + 1][j]) { // Rotate
                        dp[cur ^ 1][S + p3[j - 1]] += dp[cur][S];
                    }
                    if (l == 2) { // end
                        dp[cur ^ 1][S - 2 * p3[j - 1]] += dp[cur][S];
                    }
                } else if (!l && r) {
                    if (mp[i + 1][j]) {
                        dp[cur ^ 1][S - r * p3[j] + r * p3[j - 1]] +=
                            dp[cur][S];
                    }
                    if (r == 1 && mp[i][j + 1]) {
                        dp[cur ^ 1][S + p3[j]] += dp[cur][S];
                    }
                    if (r == 2) {
                        dp[cur ^ 1][S - 2 * p3[j]] += dp[cur][S];
                    }
                } else if (l == 1 && r == 1) {
                    dp[cur ^ 1][S - p3[j] - p3[j - 1]] += dp[cur][S];
                }
            }
            cur ^= 1;
        }
        dp[cur ^ 1].assign(p3[m + 1], 0);
        for (int S = 0; S < p3[m]; S++) {
            dp[cur ^ 1][S * 3] = dp[cur][S];
        }
        cur ^= 1;
    }
    cout << dp[cur][0] << endl;
    return 0;
}
// Asusetic eru quionours