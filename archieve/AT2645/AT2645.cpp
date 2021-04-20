#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int N = 2e5 + 5;
int n, m, ans, qp[N], cnt;
struct Data {
    int l, r;
} a[N];
bool cmp(const Data &A, const Data &B) {
    if (A.l != B.l) {
        return A.l < B.l;
    }
    return A.r > B.r;
}
priority_queue<int, vector<int>, greater<int>> q;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
    }
    sort(a + 1, a + n + 1, cmp);
    int h = 1, t = m;
    for (int i = 1; i <= n; i++) {
        q.push(a[i].r);
        if (h <= t && h <= a[i].l) {
            h++;
        } else {
            qp[++cnt] = q.top();
            q.pop();
        }
    }
    sort(qp + 1, qp + cnt + 1);
    for (int i = cnt; i >= 1; i--) {
        if (h <= t && qp[i] <= t) {
            t--;
        } else {
            ans++;
        }
    }
    cout << ans;
}
//Asusetic eru quionours