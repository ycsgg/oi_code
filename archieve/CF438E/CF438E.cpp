
#include <cstdio>
#include <cstring>
#include <iostream>
//这里是 Poly 板子
namespace Poly {} // namespace Poly
const int N = 4e5 + 5, mod = 998244353;
int n, m;
long long a[N], g[N];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    a[x] = 1;
  }
  g[0] = 1;
  for (int i = 1; i <= m; i++) {
    g[i] = (mod - 4 * a[i] + mod) % mod;
  }
  Poly::Sqrt(g, g, m + 1);
  g[0]++;
  Poly::Inv(g, a, m + 1);
  for (int i = 1; i <= m; i++) {
    cout << a[i] * 2 % mod << endl;
  }
}
