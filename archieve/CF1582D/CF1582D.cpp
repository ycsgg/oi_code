#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        if (n & 1) {
            if (a[1] + a[2] != 0) {
                cout << -a[3] << " " << -a[3] << " " << a[1] + a[2] << ' ';
            } else if (a[2] + a[3] != 0) {
                cout << a[2] + a[3] << " " << -a[1] << " " << -a[1] << ' ';
            } else {
                cout << -a[2] << " " << a[1] + a[3] << " " << -a[2] << ' ';
            }
        }
        for (int i = (n & 1 ? 4 : 1); i <= n; i += 2) {
            cout << -a[i + 1] << " " << a[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
// Asusetic eru quionours.