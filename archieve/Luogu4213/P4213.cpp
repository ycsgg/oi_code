#include <iostream>
#include <unordered_map>
using namespace std;
const int N = 5000000;
int prime[N / 10], pcnt, mu[N + 2];
bool vis[N + 2];
long long phi[N + 2];
unordered_map<int, int> mu_s;
unordered_map<int, long long> phi_s;
void init() {
    mu[1] = phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            phi[i]        = i - 1;
            mu[i]         = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]]  = 0;
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            mu[i * prime[j]]  = -mu[i];
        }
    }
    for (int i = 1; i <= N; i++) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}
long long Phi_Sum(int x) {
    if (x <= N) {
        return phi[x];
    }
    if (phi_s.count(x)) {
        return phi_s[x];
    }
    long long ans = 1ll * ((1ll + x) * x) / 2ll;
    for (long long l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= 1ll * (r - l + 1) * Phi_Sum(x / l);
    }
    phi_s[x] = ans;
    return ans;
}
int Mu_Sum(int x) {
    if (x <= N) {
        return mu[x];
    }
    if (mu_s.count(x)) {
        return mu_s[x];
    }
    long long ans = 1ll;
    for (long long l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= 1ll * (r - l + 1) * Mu_Sum(x / l);
    }
    mu_s[x] = ans;
    return ans;
}
int T;
int main() {
    init();
    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        cout << Phi_Sum(x) << " " << Mu_Sum(x) << endl;
    }
    return 0;
}
