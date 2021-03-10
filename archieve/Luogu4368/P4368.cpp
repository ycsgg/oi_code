#include <iostream>
using namespace std;
typedef long long ll;
ll t, ans, n, h, x, y, a, b, f[2][2];
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> h >> x >> y >> a >> b;
        if ((x - 1) % a == 0)
            f[0][0] = (x - 1) / a;
        else
            f[0][0] = -1;
        if ((n - x) % a == 0)
            f[0][1] = (n - x) / a;
        else
            f[0][1] = -1;
        if ((y - 1) % b == 0)
            f[1][0] = (y - 1) / b;
        else
            f[1][0] = -1;
        if ((h - y) % b == 0)
            f[1][1] = (h - y) / b;
        else
            f[1][1] = -1;
        ans = -1;
        for (register int i = 0; i <= 1; i++) {
            for (register int j = 0; j <= 1; j++) {
                if (f[0][i] != -1 && f[1][j] != -1 &&
                    (f[1][j] - f[0][i]) % 2 == 0) {
                    ll tmp = max(f[1][j], f[0][i]);
                    if (ans > tmp || ans == -1)
                        ans = tmp;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}