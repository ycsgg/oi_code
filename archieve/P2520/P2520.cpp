
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T;
int a, b, x, y, k;
bool check(int x, int y) { return x % k == 0 && y % k == 0; }
signed main() {
  cin >> T;
  while (T--) {
    cin >> a >> b >> x >> y;
    k = __gcd(a, b) * 2;
    if (check(x, y) || check(x + a, y + b) || check(x + b, y + a) ||
        check(x + a + b, y + a + b)) {
      cout << "Y" << endl;
    } else {
      cout << "N" << endl;
    }
  }
}
