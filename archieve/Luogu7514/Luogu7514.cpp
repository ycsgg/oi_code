#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e6 + 10;
typedef long long ll;
struct Data {
    ll val;
    int id, v;
    friend bool operator<(const Data &A, const Data &B) {
        return A.val < B.val;
    }
} a[N];
int n, m;
bool used[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].v  = 1;
        a[i].id = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i + n].val;
        a[i + n].id = i;
    }
    sort(a + 1, a + 1 + 2 * n);
    ll l = 0, r = n * 2 + 1, now = 0;
    while (!used[a[l + 1].id] && now + a[l + 1].v <= m) {
        now += a[l + 1].v;
        used[a[l + 1].id] = 1;
        l++;
    }
    while (!used[a[r - 1].id] && now + a[r - 1].v <= m) {
        now += a[r - 1].v;
        used[a[r - 1].id] = 1;
        r--;
    }
    ll ans = 2e18;
    while (l >= 0) {
        ans           = min(a[r - 1].val - a[l + 1].val, ans);
        used[a[l].id] = 0;
        now -= a[l--].v;
        while (!used[a[r - 1].id] && now + a[r - 1].v <= m) {
            now += a[r - 1].v;
            used[a[r - 1].id] = 1;
            r--;
        }
    }
    cout << ans << endl;
    return 0;
}