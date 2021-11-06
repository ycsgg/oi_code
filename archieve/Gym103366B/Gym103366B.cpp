#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
vector<int> ContinuedFraction(ll a, ll b) {
    if (a % b == 0) {
        return vector<int>(1, a / b);
    }
    vector<int> res;
    res.push_back(a / b);
    auto tmp = ContinuedFraction(b, a % b);
    res.insert(res.end(), tmp.begin(), tmp.end());
    return res;
}
int main() {
    int _;
    cin >> _;
    while (_--) {
        ll a, b;
        cin >> a >> b;
        auto res = ContinuedFraction(a, b);
        cout << res.size() - 1 << ' ';
        for (auto v : res) {
            cout << v << ' ';
        }
        cout << '\n';
    }
    return 0;
}
// Asusetic eru quionours.