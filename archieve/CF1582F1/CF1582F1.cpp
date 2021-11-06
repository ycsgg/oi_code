#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
const int Lim = 511;
int n;
int a[N], pos[Lim + 10];
bool vis[Lim + 10];
int main() {
    memset(pos, 0x3f, sizeof(pos));
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        pos[a[i]] = min(pos[a[i]], a[i]);
        vis[a[i]] = 1;
        for (int S = 0; S <= Lim; S++) {
            if (pos[S ^ a[i]] < a[i]) {
                vis[S] = 1;
                pos[S] = min(pos[S], a[i]);
            }
        }
    }
    vis[0] = 1;
    int cnt = 0;
    for (int i = 0; i <= Lim; i++) {
        if (vis[i]) {
            cnt++;
        }
    }
    cout << cnt << '\n';
    for (int i = 0; i <= Lim; i++) {
        if (vis[i]) {
            cout << i << ' ';
        }
    }
    return 0;
}
// Asusetic eru quionours.
