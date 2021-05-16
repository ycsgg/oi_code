#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll n, m, ans;
char s[N];
int main() {
    cin >> n >> m;
    cin >> s + 1;
    s[0]   = "/QAQ"[0];
    ans    = 1ll * n * (m - 1);
    ll len = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] != s[i - 1]) {
            ans += n * (m - 1);
            if (len == 1) {
                len++;
                continue;
            }
        }
        if (len != 1) {
            if (s[i] == s[i - 2]) {
                len++;
            } else {
                ans -= len * (len - 1) / 2;
                if (s[i] == s[i - 1]) {
                    len = 1;
                } else {
                    len = 2;
                }
            }
        }
    }
    // cout << len << endl;
    if (len > 1)
        ans -= 1ll * len * (len - 1) / 2;
    cout << ans << endl;
    return 0;
}
//Asusetic eru quionours.