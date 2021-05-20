#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
ll n, p;
/*int prime[505], pcnt, mindiv[505];
bool vis[505];
void pre() {
    for (int i = 2; i <= 500; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mindiv[i]     = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > 500) {
                break;
            }
            vis[i * prime[j]]    = 1;
            mindiv[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}*/
const int prime[] = {0, 2, 3, 5, 7, 11, 13, 17, 19};
struct Data {
    int p, res;
    bool operator<(const Data &B) const {
        return res < B.res;
    }
} a[808];
const int U = (1 << 8) - 1;
ll dp[3][U + 1][U + 1];
int main() {
    cin >> n >> p;
    // pre();
    for (int i = 2; i <= n; i++) {
        int tmp = i;
        for (int j = 1; j <= 8; j++) {
            if (tmp % prime[j] == 0) {
                a[i - 1].p |= (1 << (j - 1));
                while (tmp % prime[j] == 0) {
                    tmp /= prime[j];
                }
            }
        }
        if (tmp != 1) {
            a[i - 1].res = tmp;
        }
    }
    sort(a + 1, a + n);
    dp[0][0][0] = 1;
    for (int i = 1; i < n; i++) {
        if (i == 1 || a[i].res != a[i - 1].res || !a[i].res) {
            memcpy(dp[1], dp[0], sizeof(dp[1]));
            memcpy(dp[2], dp[0], sizeof(dp[2]));
        }
        for (int S = U; S >= 0; S--) {
            for (int T = U; T >= 0; T--) {
                if (S & T) {
                    continue;
                }
                if ((a[i].p & S) == 0) {
                    dp[2][S][T | a[i].p] += dp[2][S][T];
                    dp[2][S][T | a[i].p] %= p;
                }
                if ((a[i].p & T) == 0) {
                    dp[1][S | a[i].p][T] += dp[1][S][T];
                    dp[1][S | a[i].p][T] %= p;
                }
            }
        }
        if (i == n - 1 || a[i].res != a[i + 1].res || !a[i].res) {
            for (int S = 0; S <= U; S++) {
                for (int T = 0; T <= U; T++) {
                    if (S & T) {
                        continue;
                    }
                    dp[0][S][T] =
                        ((dp[1][S][T] + dp[2][S][T]) % p - dp[0][S][T] + p) % p;
                }
            }
        }
    }
    ll ans = 0;
    for (int S = 0; S <= U; S++) {
        for (int T = 0; T <= U; T++) {
            if (S & T) {
                continue;
            }
            ans = (ans + dp[0][S][T]) % p;
        }
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours