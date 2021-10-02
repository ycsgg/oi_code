#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll A = 1000000000000000000ll;
ll mod;
int main() {
    cin >> mod;
    ll l = 1ll * mod - A % mod * 9ll % mod * 9ll % mod;
    ll r = l + 999999999999999999ll;
    cout << l << " " << r << '\n';
    return 0;
}
// Asusetic eru quionours.