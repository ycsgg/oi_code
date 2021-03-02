#include <iostream>
#include <map>
using namespace std;
const int N = 2e6 + 5;
typedef unsigned long long ull;
const ull base = 20050207;
map<ull, int> s;
ull dpow[N], Hash[N];
ull getHash(int l, int r) {
    return Hash[r] - Hash[l - 1] * dpow[r - l + 1];
}
bool check(int len, ull val, int m) {
    for (int i = 1; i <= m; i += len) {
        if (getHash(i, i + len - 1) != val) {
            return false;
        }
    }
    return true;
}
int n, m;
char a[N];
int main() {
    cin >> n;
    dpow[0] = 1;
    for (int i = 1; i < N; i++) {
        dpow[i] = dpow[i - 1] * base;
    }
    for (int i = 1; i <= n; i++) {
        cin >> m;
        cin >> a + 1;
        for (int i = 1; i <= m; i++) {
            Hash[i] = Hash[i - 1] * base + a[i];
        }
        for (int i = 1; i <= m; i++) {
            if (m % i == 0) {
                ull now = getHash(1, i);
                if (check(i, now, m)) {
                    s[now]++;
                    break;
                }
            }
        }
    }
    ull ans = 0;
    for (auto d : s) {
        ans += 1ll * d.second * d.second;
        s[d.first] = 0;
    }
    cout << ans;
    return 0;
}