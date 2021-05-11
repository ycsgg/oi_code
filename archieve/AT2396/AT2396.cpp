#include <iostream>
using namespace std;
const int N = 1000010;
typedef long long ll;
const ll mod = 1e9 + 7;
ll dp[N];
ll sum;
ll n;
int main() {
    cin >> n;
    dp[n]     = n;
    dp[n - 1] = (n * n) % mod;
    for (int i = n - 2; i >= 1; i--) {
        sum += dp[i + 3];
        sum %= mod;
        dp[i] = dp[i + 1];
        dp[i] += (n - 1) * (n - 1) % mod;
        dp[i] %= mod;
        dp[i] += sum;
        dp[i] %= mod;
        dp[i] += i + 1 % mod;
        dp[i] %= mod;
    }
    cout << dp[1] % mod;
    return 0;
}
// Asusetic eru quionours