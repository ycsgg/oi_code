#include <iostream>
#include <string>
using namespace std;
int n, m;
int a[2005][1005];
bool vis[2005];
string s;
int Gauss() {
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        int temp = i;
        while (!a[temp][i] && temp <= n) {
            temp++;
        }
        if (temp == n + 1) {
            ret++;
            continue;
        }
        vis[i] = 1;
        if (i != temp) {
            for (int j = i; j <= n + 1; j++) {
                swap(a[temp][j], a[i][j]);
            }
        }
        for (int j = i + 1; j <= n; j++) {
            if (!vis[j] && a[j][i]) {
                for (int k = i; k <= n + 1; k++) {
                    a[j][k] ^= a[i][k];
                }
            }
        }
    }
    return ret;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> s >> a[i][n + 1];
        for (int j = 0; j < n; j++) {
            a[i][j + 1] = s[j] - '0';
        }
    }
    int now = n;
    while (Gauss()) {
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                now++;
                if (now > m) {
                    cout << "Cannot Determine" << endl;
                    return 0;
                }
                swap(a[now], a[i]);
            }
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i - 1; j >= 1; j--) {
            if (a[j][i]) {
                a[j][n + 1] ^= a[i][n + 1];
            }
        }
    }
    cout << now << endl;
    for (int i = 1; i <= n; i++) {
        if (a[i][n + 1]) {
            cout << "?y7M#" << endl;
        } else {
            cout << "Earth" << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours