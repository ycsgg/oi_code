
#include "Polynomial.h"
using namespace Poly;
using namespace std;
Polynomial<long long> f;
const int maxn = 4e5 + 5;
long long fac[maxn];
int n;
int main() {
    cin >> n;
    f.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    for (int i = 0; i <= n; i++) {
        f[i] = qpow(2, 1ll * i * (i - 1) / 2) * qpow(fac[i], mod - 2) % mod;
    }
    cout << 1ll * fac[n] * Ln(f)[n] % mod;
}
