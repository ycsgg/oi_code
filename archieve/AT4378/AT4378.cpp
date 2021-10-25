#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int LIM = 500 * 500 + 10;
int prime[LIM], pcnt;
bool vis[LIM];
void Sieve() {
    for (int i = 2; i < LIM; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (prime[j] * i >= LIM) {
                break;
            }
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
ll lcm(ll a, ll b) {
    if (!a || !b) {
        return a + b;
    }
    return a / gcd(a, b) * b;
}
ll ans[505][505];
int main() {
    Sieve();
    int n;
    cin >> n;
    if (n == 2)
        return puts("4 7\n23 10\n"), 0;
    for (int i = 1; i <= n; i++) {
        for (int j = ((i - 1) & 1) + 1; j <= n; j += 2) {
            ans[i][j] =
                prime[(i + j) / 2] * prime[n + (i - j) / 2 + (n + 1) / 2];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = (i & 1) + 1; j <= n; j += 2) {
            ans[i][j] = lcm(lcm(ans[i - 1][j], ans[i][j - 1]),
                            lcm(ans[i + 1][j], ans[i][j + 1])) + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
// Asusetic eru quionours.
