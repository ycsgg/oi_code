#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n;
int a[N], b[N];
using ll = long long;
namespace BinaryIndexTree {
ll c[2 * N];
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int v) {
    while (pos <= 2 * n + 1) {
        c[pos] += v;
        pos += lowbit(pos);
    }
}
ll query(int pos) {
    ll res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
void clear() {
    memset(c, 0, sizeof(c));
}
} // namespace BinaryIndexTree
int s[N];
ll tot;
bool check(int mid) {
    ll cnt = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + (a[i] > mid ? -1 : 1);
    }
    BinaryIndexTree::clear();
    BinaryIndexTree::add(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        cnt += BinaryIndexTree::query(s[i] + n);
        BinaryIndexTree::add(s[i] + 1 + n, 1);
    }
    return cnt >= tot;
}

int main() {
    cin >> n;
    tot = 1ll * n * (n + 1) / 4 + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    int l = 1, r = n, res = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(b[mid])) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << b[l];
    return 0;
}
// Asusetic eru quionours.