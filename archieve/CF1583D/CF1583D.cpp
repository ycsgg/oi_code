#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int query(vector<int> &seq) {
    cout << "? ";
    for (auto v : seq) {
        cout << v << ' ';
    }
    cout.flush();
    int x;
    cin >> x;
    return x;
}
int n;
int main() {
    cin >> n;
    vector<int> qr(n, 1);
    vector<int> a(n, 0);
    for (int i = 1; i <= n; i++) {
        qr[n - 1] = n - i + 1;
        auto x = query(qr);
        if (x) {
            a[n - 1] = i;
            break;
        }
    }
    if (!a[n - 1]) {
        a[n - 1] = n;
    }
    for (int i = 0; i < n - 1; i++) {
        qr[i] = a[n - 1];
    }
    for (int i = 1; i <= n; i++) {
        if (a[n - 1] != i) {
            qr[n - 1] = i;
            auto x = query(qr);
            a[x - 1] = i;
        }
    }
    cout << "! ";
    for (auto v : a) {
        cout << v << ' ';
    }
    return 0;
}
// Asusetic eru quionours.
