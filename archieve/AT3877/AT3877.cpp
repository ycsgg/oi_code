#include <iostream>
using namespace std;
int A, B;
int d[11][11];
int f[101][101];
int main() {
    cin >> A >> B;
    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= B; j++) {
            cin >> d[i][j];
        }
    }
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            for (int x = 1; x <= A; x++) {
                for (int y = 1; y <= B; y++) {
                    f[i][j] = max(f[i][j], d[x][y] - i * x - j * y);
                }
            }
        }
    }
    for (int x = 1; x <= A; x++) {
        for (int y = 1; y <= B; y++) {
            int now = 0x7f7f7f7f;
            for (int i = 0; i <= 100; i++) {
                for (int j = 0; j <= 100; j++) {
                    now = min(now, f[i][j] + i * x + j * y);
                }
            }
            if (now != d[x][y]) {
                cout << "Impossible";
                return 0;
            }
        }
    }
    cout << "Possible" << endl;
    cout << "202 10401" << endl;
    for (int i = 1; i <= 100;i++){
        cout << i << " " << i + 1 << " X" << endl;
    }
    for (int i = 102; i <= 201;i++){
        cout << i << " " << i + 1 << " Y" << endl;
    }
    for (int i = 0; i <= 100;i++){
        for (int j = 0; j <= 100;j++){
            cout << i + 1 << " " << 202 - j << " " << f[i][j] << endl;
        }
    }
    cout << "1 202";
    return 0;
}
// Asusetic eru quionours