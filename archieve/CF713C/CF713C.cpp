#include <iostream>
#include <queue>
using namespace std;
const int N = 3005;
using ll = long long;
int n;
ll ans;
ll a[N];
priority_queue<int> S;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] -= i;
        S.push(a[i]);
        if (a[i] < S.top()) {
            ans += S.top() - a[i];
            S.pop();
            S.push(a[i]);
        }
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours.
