#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ans = __gcd(x, ans);
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours.