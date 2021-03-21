#include <iostream>
using namespace std;
typedef long long ll;
const int N    = 10000001;
const int PLim = 664585;
int prime[PLim], pcnt;
int fac[N], inv[N], ans[N];
ll m, n, t, r;
bool vis[N];
void init() {
    fac[0] = fac[1] = inv[0] = inv[1] = ans[0] = ans[1] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = 1ll * fac[i - 1] * i % r;
        inv[i] = 1ll * inv[r % i] * (r - r / i) % r;
        if (!vis[i]) {
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (prime[j] * i > N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
    for (int i = 2; i < N; i++) {
        ans[i] = ans[i - 1];
        if (!vis[i]) {
            ans[i] = 1ll * ans[i] * (i - 1) % r * inv[i] % r;
        }
    }
}
int main() {
    cin >> t >> r;
    init();
    while (t--) {
        cin >> n >> m;
        cout << 1ll * fac[n] * ans[m] % r << endl;
    }
    return 0;
}