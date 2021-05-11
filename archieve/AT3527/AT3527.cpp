#include <iostream>
using namespace std;
const int N = 1000010;
int x, n;
int r[N];
int cur, down, k = -1, up, sum;
int main() {
    cin >> x >> n;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    int m;
    cin >> m;
    up = x;
    while (m--) {
        int t, a;
        cin >> t >> a;
        while (cur < n && r[cur + 1] <= t) {
            down = min(x, max(0, down + k * (r[cur + 1] - r[cur])));
            up   = min(x, max(0, up + k * (r[cur + 1] - r[cur])));
            sum  = sum + k * (r[cur + 1] - r[cur]);
            k    = -k;
            cur++;
        }
        int downnow = min(x, max(0, down + k * (t - r[cur])));
        int upnow   = min(x, max(0, up + k * (t - r[cur])));
        int sumnow  = sum + k * (t - r[cur]);
        cout << min(upnow, max(downnow, sumnow + a)) << endl;
    }
}
// Asusetic eru quionours