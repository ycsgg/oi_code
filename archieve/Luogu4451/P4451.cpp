
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const ll sqrt2 = 59713600;
const ll v1 = (1 - sqrt2 + mod) % mod, v2 = sqrt2 + 1;
const ll c1 = 485071604; // (sqrt(2)-1) / 2sqrt2
const ll c2 = 514928404; // (sqrt(2)+1) / 2sqrt2
ll read() {
  ll x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') {
      f = -1;
    }
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    x %= (mod - 1);
    c = getchar();
  }
  return x * f;
}
ll qpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) {
      res = res * a % mod;
    }
    a = a * a % mod;
    b /= 2;
  }
  return res;
}
int main() {
  ll n = read();
  cout << (c1 * qpow(v1, n - 1) % mod + c2 * qpow(v2, n - 1) % mod) % mod;
}
