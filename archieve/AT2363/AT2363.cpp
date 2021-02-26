
#include <iostream>
using namespace std;
int p[202], q[202], cnt;
long long n;
void base2(long long n) {
  if (!n)
    return;
  if (~n & 1) {
    q[++q[0]] = cnt++;
    base2(n - 1);
  } else {
    p[++p[0]] = cnt++;
    base2(n >> 1);
  }
}

int main() {
  cin >> n;
  base2(n);
  printf("%d\n", cnt + 100);
  for (int i = 1; i <= q[0]; ++i)
    printf("%d ", cnt - q[i]);
  for (int i = p[0]; i; --i)
    printf("%d ", cnt - p[i]);
  for (int i = 1; i <= 100; ++i)
    printf("%d ", i);
  return 0;
}
