#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
using uint  = unsigned int;
int n;
char s[N];
uint dp[N];
int main() {
    cin >> n;
    if (n & 1) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    dp[0]   = 1;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '?') {
            for (int j = i / 2; j >= i - n / 2; j--) {
                if (j >= 1)
                    dp[j] += dp[j - 1];
            }
        } else {
            cnt++;
        }
    }
    uint ans = 1;
    for (int i = 1; i <= n / 2 - cnt; i++)
        ans = ans * 25;
    cout << ans * dp[n / 2];
    return 0;
}
// Asusetic eru quionours
