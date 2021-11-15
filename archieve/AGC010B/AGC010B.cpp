#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 7;
ll n, a[N], sum, d[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    ll op = (n + 1ll) * n / 2;
    if (sum % op != 0) {
        cout << "NO\n";
        return 0;
    }
    sum /= op;
    for (int i = 1; i < n; i++) {
        d[i] = a[i + 1] - a[i];
    }
    d[n] = d[1] - d[n];
    for (int i = 1; i <= n; i++) {
        if ((sum - d[i]) % n != 0) {
            cout << "NO\n";
            return 0;
        }
        ll cnt = (sum - d[i]) / n;
        if (cnt < 0) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES";

    return 0;
}
// Asusetic eru quionours.