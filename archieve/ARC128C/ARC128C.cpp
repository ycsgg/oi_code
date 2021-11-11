#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int n, m, S;
int main() {
    cin >> n >> m >> S;
    vector<long long> a(n);
    for (auto &v : a) {
        cin >> v;
    }
    long double ans = 0;
    long double last = 0;
    while ("ycs") {
        long double sum = 0;
        for (int i = a.size() - 1; ~i; i--) {
            sum += a[i];
            ans = max(ans, last + min((long double)m,
                                      (long double)S / (a.size() - i)) *
                                      sum);
        }
        if (S < m) {
            break;
        }
        S -= m;
        last += (long double)a.back() * m;
        a.pop_back();
    }
    printf("%7Lf", ans);
    return 0;
}
// Asusetic eru quionours.
