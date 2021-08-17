#include <array>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
int n;
string s;
int a[N];
int Cmod2(int n, int m) {
    return (n & m) == m;
}
int main() {
    cin >> n;
    cin >> s;
    n--;
    int flag = 0;
    for (int i = 1; i < s.length(); i++) {
        a[i] = abs(s[i] - s[i - 1]);
        flag |= (a[i] & 1);
    }
    if (!flag) {
        for (int i = 1; i <= n; i++) {
            a[i] >>= 1;
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum ^= (a[i] & 1) * Cmod2(n - 1, i - 1);
    }
    if (!sum) {
        cout << 0 << endl;
    } else if (!flag)
        cout << 2 << endl;
    else {
        cout << 1 << endl;
    }
    return 0;
}
// Asusetic eru quionours