#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
int n;
ll a[N], b[N];
int prime[N], pcnt;
bool vis[N];
map<ll, ll> cnt;
void pre() {
    for (int i = 2; i <= 3000; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > 3000) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
int main() {
    cin >> n;
    pre();
    for (int qaq = 1; qaq <= n; qaq++) {
        ll t;
        cin >> t;
        ll now = 1, inv = 1;
        for (int i = 1; i <= pcnt; i++) {
            int tot = 0;
            while (t % prime[i] == 0) {
                tot++;
                t /= prime[i];
            }
            tot %= 3;
            if (tot != 0) {
                for (int j = 1; j <= tot; j++) {
                    now *= prime[i];
                }
                for (int j = tot + 1; j <= 3; j++) {
                    inv *= prime[i];
                }
            }
        }
        now *= t;
        if ((ll)sqrt(t) * (ll)sqrt(t) == t) {
            inv *= (ll)sqrt(t);
        } else {
            inv *= t * t;
        }
        ++cnt[now];
        a[qaq] = now;
        b[qaq] = inv;
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 1)
            continue;
        ans += max(cnt[a[i]], cnt[b[i]]);
        cnt[a[i]] = cnt[b[i]] = 0;
    }
    ans += (cnt[1] > 0);
    cout << ans << endl;
}