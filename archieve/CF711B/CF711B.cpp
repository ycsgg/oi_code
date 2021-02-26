
#include <iostream>
using namespace std;
typedef long long ll;
ll a[1001][1001];
ll r[1001];
ll c[1001];
int n;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  int x, y;
  ll pdsum = 0;
  ll sdsum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      if (a[i][j] == 0) {
        x = i;
        y = j;
      } else {
        r[i] += a[i][j];
        c[j] += a[i][j];
        if (i == j) {
          pdsum += a[i][j];
        }
        if (i + j == n - 1) {
          sdsum += a[i][j];
        }
      }
    }
  }
  if (n == 1) {
    cout << 233 << '\n';
    return 0;
  }
  ll commonsum = r[0];
  if (x == 0) {
    commonsum = r[1];
  }
  ll rowsum = -1;
  ll colsum = -1;
  ll d1sum = -1;
  ll d2sum = -1;
  for (int i = 0; i < n; i++) {
    if (i != x) {
      if (r[i] != commonsum) {
        cout << -1 << endl;
        return 0;
      }
    } else {
      rowsum = r[i];
    }
  }
  for (int i = 0; i < n; i++) {
    if (i != y) {
      if (c[i] != commonsum) {
        cout << -1 << endl;
        return 0;
      }
    } else {
      colsum = c[i];
    }
  }
  bool isd1 = false;
  bool isd2 = false;
  if (x == y)
    isd1 = true;
  if (x + y == n - 1)
    isd2 = true;
  if (!isd1) {
    if (pdsum != commonsum) {
      cout << -1 << endl;
      return 0;
    }
  } else {
    d1sum = pdsum;
  }
  if (!isd2) {
    if (sdsum != commonsum) {
      cout << -1 << endl;
      return 0;
    }
  } else {
    d2sum = sdsum;
  }
  if (rowsum == colsum) {
    if (isd1 && d1sum != rowsum) {
      cout << -1 << endl;
      return 0;
    }
    if (isd2 && d2sum != rowsum) {
      cout << -1 << endl;
      return 0;
    }
    ll value = commonsum - rowsum;
    if (value > 0) {
      cout << value << '\n';
      return 0;
    } else {
      cout << -1 << endl;
      return 0;
    }
  } else {
    cout << -1 << endl;
    return 0;
  }
}
