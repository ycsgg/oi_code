#include <iostream>
#include <string>
using namespace std;
int n;
string a, b;
char c;
void solve(int x) {
    if (x == 1) {
        c = 'A';
        a.clear();
        b = c;
        return;
    }
    if (x == 2) {
        c = 'B';
        a = "B";
        b = "AB";
        return;
    }
    if (x & 1) {
        solve(x / 2);
        c++;
        a = a + c + c;
        b = b + c;
    } else {
        solve(x / 2 - 1);
        c++;
        a = c + a + c + c;
        b = b + c;
    }
}
int main() {
    cin >> n;
    solve(n);
    cout << b + a << ' ' << b;
    return 0;
}
// Asusetic eru quionours
