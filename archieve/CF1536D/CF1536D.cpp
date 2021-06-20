#include <array>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
const int N = 2e5 + 5;
int T, n;
array<int, N> b;
set<int> s;
int main() {
    cin >> T;
    while (T--) {
        bool flag = 1;
        s.clear();
        cin >> n;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &b[i]);
            if (!s.count(b[i]))
                s.insert(b[i]);
            if (b[i] == b[i - 1])
                continue;
            if (b[i - 1] < b[i]) {
                if (s.upper_bound(b[i - 1]) != s.find(b[i])) {
                    flag = 0;
                }
            } else {
                if (s.upper_bound(b[i]) != s.find(b[i - 1])) {
                    flag = 0;
                }
            }
        }
        if (flag) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours
