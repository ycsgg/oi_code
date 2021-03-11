#include <iostream>
using namespace std;
const int N = 2e5;
int n;
int a[N];
int ans;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = abs(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        int lans = 0, rans = 0;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i])
                lans++;
        }
        for (int j = i + 1; j <= n; j++) {
            if (a[j] < a[i])
                rans++;
        }
        ans += min(lans, rans);
    }
    cout << ans;
    return 0;
}