#include <iostream>
using namespace std;
const int N = 2e5 + 6;
int prime[N], pcnt;
long long phi[N + 12];
bool vis[N + 12];
void pre() {
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            phi[i]        = i - 1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    for (int i = 2; i <= N; i++) {
        phi[i] = 1ll * phi[i] + phi[i - 1];
    }
}
int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}
long long n;
int main() {
    pre();
    while (cin >> n) {
        if (n == 0)
            return 0;
        if (n == 1) {
            cout << "0/1" << endl;
            continue;
        }
        n--;
        n--;
        if(n==0){
            cout << "1/1" << endl;
            continue;
        }
        int pos = lower_bound(phi + 1, phi + 1 + N, n) - phi;
        if (phi[pos] == n) {
            cout << pos - 1 << "/" << pos << endl;
            continue;
        }
        n -= phi[pos - 1];
        if (n == 1) {
            cout << "1/" << pos << endl;
            continue;
        } else {
            n--;
            for (int j = 2; j < pos; j++) {
                if (gcd(j, pos) == 1) {
                    n--;
                }
                if (n == 0) {
                    printf("%d/%d\n", j, pos);
                    break;
                }
            }
        }
    }
    return 0;
}