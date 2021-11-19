#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 3e5 + 10;
int n;
char s[N];
int main() {
    cin >> n;
    cin >> (s + 1);
    int len = 1, st = 0;
    long long res = 0;
    for (int i = 2; i <= n; i++) {
        if (s[i] == s[i - 1]) {
            len++;
        } else {
            res += len - st;
            len = 1;
        }
    }
    reverse(s + 1, s + n + 1);
    len = st = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] == s[i - 1]) {
            len++;
        } else {
            res += len - st;
            len = 1;
        }
    }
    cout << 1ll * n * (n - 1) / 2 - res << endl;
    return 0;
}
// Asusetic eru quionours.