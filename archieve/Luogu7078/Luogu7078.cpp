#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    int n = 0;
    vector<int> a;
    cin >> T;
    while (T--) {
        if (!n) {
            cin >> n;
            a.resize(n);
            for (auto &v : a) {
                cin >> v;
            }
        } else {
            int k;
            cin >> k;
            for (int i = 1; i <= k; i++) {
                int x, y;
                cin >> x >> y;
                x--;
                a[x] = y;
            }
        }
        set<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            q.insert(make_pair(a[i], i));
        }
        int remain = 0, ans = 0;
        while ("ycs") {
            if (q.size() == 2) {
                q.erase(q.begin());
                if (remain) {
                    if ((remain - q.size()) % 2) {
                        cout << remain + 1 << '\n';
                    } else {
                        cout << remain << '\n';
                    }
                } else {
                    cout << 1 << '\n';
                }
                break;
            }
            auto now = q.end();
            now--;
            int x = now->first, id = now->second;
            int y = q.begin()->first;
            q.erase(now);
            q.erase(q.begin());
            q.insert(make_pair(x - y, id));
            if (q.begin()->second != id) {
                if (remain) {
                    if ((remain - q.size()) % 2) {
                        cout << remain + 1 << '\n';
                    } else {
                        cout << remain << '\n';
                    }
                    break;
                }
            } else {
                if (!remain) {
                    remain = q.size();
                }
            }
        }
    }
    return 0;
}
// Asusetic eru quionours.