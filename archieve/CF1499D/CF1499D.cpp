#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int LIM = 2e7 + 10;
int prime[1400000], pcnt, cnt[LIM];
bool vis[LIM];
void Sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            cnt[i] = 1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (1ll * i * prime[j] > n) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                cnt[i * prime[j]] = cnt[i];
                break;
            }
            cnt[i * prime[j]] = cnt[i] + 1;
        }
    }
}
int main() {
    int _;
    cin >> _;
    Sieve(20000000);
    while (_--) {
        int b, c, x;
        cin >> b >> c >> x;
        long long ans = 0;
        for (int i = 1; 1ll * i * i <= x; i++) {
            if (x % i == 0) {
                if ((c + i) % b == 0) {
                    ans += 1ll << cnt[(c + i) / b];
                }
                if (1ll * i * i != x) {
                    if ((c + x / i) % b == 0) {
                        ans += 1ll << cnt[(c + (x / i)) / b];
                    }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.