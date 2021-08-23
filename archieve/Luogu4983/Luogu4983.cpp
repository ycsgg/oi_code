#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
using f80 = long double;
using ll = long long;
const ll INF = (1ll << 61);
ll f[N], g[N], q[N], s[N];
ll Y(int x) {
    return f[x] + s[x] * s[x] - 2 * s[x];
}
ll X(int x) {
    return s[x];
}
f80 slope(int x, int y) {
    return (f80)(Y(y) - Y(x)) / (f80)(X(y) - X(x));
}
int n, m;
ll check(ll mid) {
    memset(f, 0x3f, sizeof(f));
    memset(g, 0, sizeof(g));
    f[0] = 0;
    int head = 1, tail = 1;
    q[head] = 0;
    for (int i = 1; i <= n; i++) {
        while (head < tail && slope(q[head], q[head + 1]) < 2 * s[i]) {
            head++;
        }
        f[i] = f[q[head]] + (s[i] - s[q[head]] + 1) * (s[i] - s[q[head]] + 1) +
               mid;
        g[i] = g[q[head]] + 1;
        while (head < tail &&
               slope(q[tail - 1], q[tail]) > slope(q[tail - 1], i)) {
            tail--;
        }
        q[++tail] = i;
    }
    return g[n];
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        s[i] = s[i - 1] + x;
    }
    ll l = 0, r = (1ll << 61), ans = 0;
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (check(mid) <= m) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    auto _ = check(ans);
    cout << f[n] - m * ans << endl;
    return 0;
}
// Asusetic eru quionours
