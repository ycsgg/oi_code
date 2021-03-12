#include <iostream>
using namespace std;
const int N   = 1e6;
const int mod = 1e9 + 7;
int prime[N + 10], vis[N + 10], pcnt, mindiv[N + 10];
void pre() {
    mindiv[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mindiv[i]     = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > N) {
                break;
            }
            vis[i * prime[j]]    = 1;
            mindiv[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
int f[N + 10][25];
int main() {
    pre();
    f[0][0] = 1;
    for (int i = 1; i <= 20; i++) {
        f[0][i] = 2;
    }
    for (int i = 1; i <= N; i++) {
        f[i][0] = f[i - 1][0] % mod;
        for (int j = 1; j <= 20; j++) {
            f[i][j] = (f[i][j] + (f[i][j - 1] + f[i - 1][j]) % mod) % mod;
        }
    }
    int T;
    cin >> T;
    while (T--) {
        long long ans = 1;
        int r, n;
        scanf("%d%d", &r, &n);
        while (n != 1) {
            int d = mindiv[n], cnt = 0;
            while (n % d == 0) {
                cnt++;
                n /= d;
            }
            ans = ans * f[r][cnt] % mod;
        }
        cout << ans << endl;
    }
    return 0;
}