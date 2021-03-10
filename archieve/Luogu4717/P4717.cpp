#include <iostream>
using namespace std;
const int mod = 998244353;
#define int long long
int k;
int n;
int A[(1 << 17) + 1], B[(1 << 17) + 1];
int a[(1 << 17) + 1], b[(1 << 17) + 1];
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
void cpy() {
    for (int i = 0; i < n; i++) {
        a[i] = A[i];
        b[i] = B[i];
    }
}
void OR(int *f, int type) {
    for (int len = 2, k = 1; len <= n; len *= 2, k *= 2) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < k; j++) {
                f[i + j + k] += f[i + j] * type % mod;
                f[i + j + k] %= mod;
            }
        }
    }
}
void AND(int *f, int type) {
    for (int len = 2, k = 1; len <= n; len *= 2, k *= 2) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < k; j++) {
                f[i + j] += f[i + j + k] * type % mod;
                f[i + j] %= mod;
            }
        }
    }
}
void XOR(int *f, int type) {
    for (int len = 2, k = 1; len <= n; len *= 2, k *= 2) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < k; j++) {
                f[i + j] += f[i + j + k];
                f[i + j] %= mod;
                f[i + j + k] = ((f[i + j] - f[i + j + k] + mod) % mod -
                                f[i + j + k] + mod) %
                               mod;
                f[i + j + k] %= mod;
                f[i + j]     = (f[i + j] * type) % mod;
                f[i + j + k] = (f[i + j + k] * type) % mod;
            }
        }
    }
}
void _mul(int *a, int *b) {
    for (int i = 0; i < n; i++) {
        a[i] = (a[i] * b[i]) % mod;
    }
}
signed main() {
    cin >> k;
    n = 1 << k;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    cpy();
    OR(a, 1);
    OR(b, 1);
    _mul(a, b);
    OR(a, mod - 1);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    cpy();
    AND(a, 1);
    AND(b, 1);
    _mul(a, b);
    AND(a, mod - 1);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    cpy();
    XOR(a, 1);
    XOR(b, 1);
    _mul(a, b);
    XOR(a, qpow(2, mod - 2));
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}