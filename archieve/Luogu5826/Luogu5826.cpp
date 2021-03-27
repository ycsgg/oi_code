#include <iostream>
#include <vector>
using namespace std;
typedef vector<int>::iterator iter;
const int N = 100010;
int n, q;
vector<int> v[N];
int t;
int main() {
    cin >> t >> n >> q >> t;
    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        v[tmp].push_back(i);
    }
    while (q--) {
        int l;
        int x;
        int now   = 0;
        bool flag = true;
        cin >> l;
        while (l--) {
            cin >> x;
            if (!flag) {
                continue;
            }
            iter it = lower_bound(v[x].begin(), v[x].end(), now + 1);
            if (it == v[x].end()) {
                flag = false;
            } else {
                now = *it;
            }
        }
        if (flag) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}