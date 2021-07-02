#include <cstdio>
#include <iostream>
#include <map>

using namespace std;
const int N = 50005;
int n, m, y[N], r[N];

map<int, int> mp;

namespace ST {
int st[17][N], lg2[N], mi[20];
void init() {
    for (int i = 2; i <= n; i++)
        lg2[i] = lg2[i / 2] + 1;
    mi[0] = 1;
    for (int i = 1; i <= n; i++) {
        st[0][i] = r[i];
    }
    for (int i = 1; i < 20; i++)
        mi[i] = mi[i - 1] * 2;
    for (int i = 1; i <= 16; i++)
        for (int j = 1; j <= n; j++)
            st[i][j] = max(st[i - 1][j], st[i - 1][j + mi[i - 1]]);
}
int query(int l, int r) {
    if (l > r)
        return 0;
    return max(st[lg2[r - l + 1]][l],
               st[lg2[r - l + 1]][r - mi[lg2[r - l + 1]] + 1]);
}
} // namespace ST

int fl(int x) //二分出第一个不大于x的位置
{
    int L = 0, R = n + 1, mid;
    while (L < R) {
        mid = (L + R + 1) >> 1;
        if (y[mid] < x)
            L = mid;
        else
            R = mid - 1;
    }
    return L;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> y[i] >> r[i];
        mp[y[i]] = i;
    }
    cin >> m;
    ST::init();
    while (m--) {
        int L, R;
        cin >> L >> R;
        if (mp.find(R) == mp.end()) {
            if (mp.find(L) == mp.end()) {
                cout << "maybe" << endl;
                continue;
            }
            if (ST::query(mp[L] + 1, fl(R)) < r[mp[L]]) {
                cout << "maybe" << endl;
                continue;
            }
            cout << "false" << endl;
            continue;
        } else if (mp.find(L) != mp.end()) {
            if (r[mp[L]] < r[mp[R]]) {
                cout << "false" << endl;
                continue;
            }
            if (ST::query(mp[L] + 1, mp[R] - 1) >= r[mp[R]]) {
                cout << "false" << endl;
                continue;
            }
            if (R - L == mp[R] - mp[L]) {
                cout << "true" << endl;
                continue;
            }
            cout << "maybe" << endl;
            continue;
        } else {
            if (ST::query(fl(L) + 1, mp[R] - 1) >= r[mp[R]]) {
                cout << "false" << endl;
                continue;
            }
            cout << "maybe" << endl;
            continue;
        }
    }
    return 0;
}
// Asusetic eru quionours.