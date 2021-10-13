#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int N = 1e3 + 5;

int t, n, k, c[N], pos[N];
string s;

/*int query(int l, int r) {
    cout << "? " << r - l + 1 << " ";
    for (int i = l; i <= r; i++) {
        cout << i << " ";
    }
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}*/
int query(int l, int r, vector<vector<int>> &pos) {
    int tot = 0;
    for (int i = l; i <= r; i++) {
        tot += pos[i].size();
    }
    cout << "? " << tot << " ";
    for (int i = l; i <= r; i++) {
        for (auto v : pos[i]) {
            cout << v << " ";
        }
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<vector<int>> pos(k);
        vector<int> mark(n + 1, 0);
        for (auto &vec : pos) {
            int c;
            cin >> c;
            vec.resize(c);
            for (auto &v : vec) {
                cin >> v;
            }
        }
        cout << "? " << n << " ";
        for (int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << endl;
        int mmax;
        cin >> mmax;

        int l = 0, r = k - 1, x = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (query(l, mid, pos) == mmax) {
                r = mid - 1;
                x = mid;
            } else {
                l = mid + 1;
            }
        }

        for (auto v : pos[x]) {
            mark[v] = 1;
        }
        cout << "? " << n - pos[x].size() << " ";
        for (int i = 1; i <= n; i++) {
            if (!mark[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
        int res;
        cin >> res;

        cout << "! ";
        for (int i = 0; i < k; i++) {
            cout << (i == x ? res : mmax) << " ";
        }
        cout << endl;
        cin >> s;
    }
    return 0;
}
// Asusetic eru quionours.