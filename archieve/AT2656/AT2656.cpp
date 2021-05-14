#include <iostream>
using namespace std;
typedef long long ll;
bool query(ll x) {
    cout << "? " << x << endl;
    char s[5];
    cin >> s;
    return (s[0] == 'Y');
}
void output(ll x) {
    cout << "! " << x << endl;
    exit(0);
}
int main() {
    ll x = 1;
    if (query(1000000000)) {
        x = 1e9;
        for (int i = 9; i; i--) {
            if (!query(x - 1)) {
                break;
            }
            x /= 10;
        }
        output(x);
        return 0;
    }
    while (query(x)) {
        x *= 10;
    }
    x /= 10;
    ll l = x, r = x * 10 - 1, ans;
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (query(mid * 10)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    output(ans);
}
// Asusetic eru quionours