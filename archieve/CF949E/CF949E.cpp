#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> solve(vector<int> &a, int pos) {
    if (pos > 19) {
        return vector<int>(0);
    }
    int flag = 0;
    for (int &x : a) {
        if (x & 1) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        for (int &x : a) {
            x >>= 1;
        }
        return solve(a, pos + 1);
    }
    vector<int> cur = a;
    for (int &x : a) {
        if (x & 1) {
            x = (x + 1) >> 1;
        } else {
            x >>= 1;
        }
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    vector<int> resx = solve(a, pos + 1);
    a = cur;
    for (int &x : a) {
        if (x & 1) {
            x = (x - 1 >> 1);
        } else {
            x >>= 1;
        }
    }
    a.erase(unique(a.begin(), a.end()), a.end());
    vector<int> resy = solve(a, pos + 1);
    resx.push_back(-(1 << pos));
    resy.push_back((1 << pos));
    return resx.size() < resy.size() ? resx : resy;
}
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v : a) {
        cin >> v;
    }
    vector<int> res = solve(a, 0);
    cout << res.size() << '\n';
    for (int x : res) {
        cout << x << ' ';
    }
}