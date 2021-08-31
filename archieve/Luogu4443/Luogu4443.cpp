#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <vector>
using ll = long long;
using namespace std;
int n;
int a[1 << 20];
int id[1 << 20];
int q[1 << 20][2];
map<pair<int, int>, int> cnt[4];
int main() {
    srand(time(0));
    cin >> n;
    int lim = 1 << n;
    if (n == 1) {
        cout << 2 << endl;
        return 0;
    }
    for (int i = 0; i < lim; i++) {
        cin >> a[i];
        id[a[i]] = i;
    }
    ll ans = 1ll * (lim + 1) * 1ll * lim / 2;
    for (int i = 0; i < lim / 2; i++) {
        q[id[i]][0] = (rand() | rand() << 15);
        q[id[i]][1] = (rand() | rand() << 15);
        q[id[(lim - 1) ^ i]][0] = q[id[i]][0];
        q[id[(lim - 1) ^ i]][1] = q[id[i]][1];
    }
    for (int i = 1; i < lim; i++) {
        q[i][0] ^= q[i - 1][0];
        q[i][1] ^= q[i - 1][1];
    }
    cnt[0][make_pair(0, 0)]++;
    for (int i = 0; i < lim; i++) {
        auto qwq = make_pair(q[i][0], q[i][1]);
        ans -= cnt[(i + 1) % 4][qwq];
        cnt[(i + 1) % 4][qwq]++;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours.