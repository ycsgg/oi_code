
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1005;
int n;
int a[N], e[N];
bool vis[N];
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int b;
        cin >> a[i] >> b;
        if (b != n) {
            cout << "NO" << endl;
            return 0;
        }
    }
    sort(a + 1, a + n);
    for (int i = 1; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            e[i]      = a[i];
            vis[a[i]] = 1;
        } else {
            bool f = 0;
            for (int j = 1; j <= a[i]; j++) {
                if (!vis[j]) {
                    e[i]   = j;
                    vis[j] = 1;
                    f      = 1;
                    break;
                }
            }
            if (!f) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl;
    e[n] = n;
    for (int i = 1; i < n; i++) {
        cout << e[i] << " " << e[i + 1] << endl;
    }
}


