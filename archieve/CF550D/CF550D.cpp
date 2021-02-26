
#include <iostream>
using namespace std;
int k;
struct RevEdge {
  int u, v;
  RevEdge(int a, int b) {
    u = a;
    v = b;
  }
};
int n, m;
ostream &operator<<(ostream &os, const RevEdge e) {
  os << e.u << " " << e.v << endl;
  os << e.u + n / 2 << " " << e.v + n / 2;
  return os;
}
int main() {
  cin >> k;
  if (!(k & 1)) {
    cout << "NO";
    return 0;
  }
  cout << "YES" << endl;
  n = 4 * k - 2;
  m = n * k / 2;
  cout << n << " " << m << endl;
  cout << 1 << " " << n / 2 + 1 << endl;
  for (int i = 2; i <= k; i++) {
    cout << RevEdge(1, i) << endl;
  }
  for (int i = 2; i <= k; i++) {
    for (int j = k + 1; j <= 2 * k - 1; j++) {
      cout << RevEdge(i, j) << endl;
    }
  }
  for (int j = k + 1; j <= 2 * k - 1; j += 2) {
    cout << RevEdge(j, j + 1) << endl;
  }
  return 0;
}
