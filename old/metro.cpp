#include <iostream>
#include <map>
using namespace std;
int n, m;
const int N    = 3300;
const int MAXN = 1e5 + 5;
const int mod  = 1e9 + 7;
int tot, vis[N + 10], prime[N + 10];
void prime_table() {
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) {
            prime[++tot] = i;
        }
        for (int j = 1; j <= tot && i * prime[j] <= N; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
map<int, int> p_fac[100];
int main() {
    prime_table();
    scanf("%d%d", &n, &m);
    cerr << p_fac[1][1] << endl;
    for (int i = 1; i <= n; i++) {
        int tmp;
        scanf("%d", &tmp);
        for (int j = 1; j <= tot; j++) {
            if (tmp == 1) {
                break;
            }
            cerr << prime[j] << endl;
            while (tmp % prime[j] == 0) {
                p_fac[i][prime[j]]++;
                tmp /= prime[j];
            }
        }
        if (tmp != 1) {
            p_fac[i][tmp]++;
        }
    }
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        map<int, int> res;
        for (int i = l; i <= r; i++) {
            for (auto key : p_fac[i]) {
                res[key.first] += key.second;
            }
        }
        long long ans = 1;
        for (auto key : res) {
            ans = ans * (key.second + 1) % mod;
        }
        printf("%lld\n", ans);
    }
}