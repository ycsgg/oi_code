#include <iostream>
using namespace std;
const int N = 300005;
int n, mmax, P;
int inv[N], cnt[N];
int a[N], p[22], pw[22];
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % P;
        }
        a = 1ll * a * a % P;
        b /= 2;
    }
    return res;
}
namespace BIT {
int c[N];
int lowbit(int x) {
    return x & (-x);
}
void add(int x, int v) {
    while (x <= mmax) {
        c[x] += v;
        x += lowbit(x);
    }
}
int query(int x) {
    int res = 0;
    while (x) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}
}; // namespace BIT
int Mul(int w, int x) {
    for (int i = 1; i <= p[0]; i++) {
        while (w % p[i] == 0) {
            w /= p[i];
            pw[i]++;
        }
    }
    return 1ll * x * w % P;
}
int Div(int x, int w) {
    for (int i = 1; i <= p[0]; i++) {
        while (w % p[i] == 0) {
            w /= p[i];
            pw[i]--;
        }
    }
    return 1ll * x * inv[w] % P;
}
int calc(int x) {
    int res = x;
    for (int i = 1; i <= p[0]; i++) {
        res = 1ll * res * qpow(p[i], pw[i]) % P;
    }
    return res;
}
int main() {
    cin >> n >> P;
    int lim = P, phi = P;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mmax = max(mmax, a[i]);
    }
    for (int i = 2; i * i <= lim; i++) {
        if (lim % i == 0) {
            p[++p[0]] = i;
            phi       = phi / i * (i - 1);
            while (lim % i == 0) {
                lim /= i;
            }
        }
    }
    if (lim != 1) {
        p[++p[0]] = lim;
        phi       = phi / lim * (lim - 1);
    }
    BIT::add(a[n], 1);
    inv[1] = 1;
    cnt[a[n]]++;
    int now = 1, ans = 0;
    for (int i = n - 1; i; i--) {
        int w = BIT::query(a[i] - 1);
        now   = Mul(n - i, now);
        BIT::add(a[i], 1);
        inv[n - i + 1] = qpow(n - i + 1, phi - 1); //
        ++cnt[a[i]];
        now = Div(now, cnt[a[i]]);
        if (!w) {
            continue;
        }
        now = Mul(w, now);
        ans = (1ll * ans + calc(now)) % P;
        now = Div(now, w);
    }
    cout << (ans + 1) % P << endl;
}