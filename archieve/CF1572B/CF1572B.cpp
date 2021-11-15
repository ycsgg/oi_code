#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> solve(int l, int r) {
    vector<int> op;
    if (r - l + 1 < 3) {
        return vector<int>();
    }
    int pos = r - 2;
    while (pos >= l) {
        op.push_back(pos);
        pos -= 2;
    }
    pos = l;
    while (pos < r) {
        op.push_back(pos);
        pos += 2;
    }
    return op;
}
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int flag = 0;
        for (auto &v : a) {
            cin >> v;
            flag ^= v;
        }
        if (flag) {
            cout << "NO\n";
        } else {
            if (n & 1) {
                auto oper = solve(1, n);
                cout << "YES\n";
                cout << oper.size() << '\n';
                for (auto v : oper) {
                    cout << v << ' ';
                }
                cout << '\n';
            } else {
                if (n == 2) {
                    cout << 0 << '\n';
                    continue;
                }
                int pre = 0, pos = -1;
                for (int i = 0; i < a.size(); i++) {
                    pre ^= a[i];
                    if (!(i & 1) && !pre) {
                        pos = i;
                        break;
                    }
                }
                if (pos == -1) {
                    cout << "NO\n";
                    continue;
                }
                auto op1 = solve(1, pos + 1);
                auto op2 = solve(pos + 2, n);
                cout << "YES\n";
                cout << op1.size() + op2.size() << '\n';
                for (auto v : op1) {
                    cout << v << ' ';
                }
                for (auto v : op2) {
                    cout << v << ' ';
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
// Asusetic eru quionours.