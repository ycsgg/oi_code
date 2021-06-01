#include <iostream>
using namespace std;
int t;
long long x;
int main() {
    cin >> t;
    while (t--) {
        cin >> x;
        if (x >= 1100) {
            cout << "YES" << endl;
        } else {
            bool f = 0;
            for (int i = 1; i <= 10; i++) {
                if (x % 11 == 0) {
                    cout << "YES" << endl;
                    f = 1;
                    break;
                }
                x -= 111;
                if (x < 0) {
                    break;
                }
            }
            if (!f) {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
// Asusetic eru quionours