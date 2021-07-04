#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 20005;
int n;
namespace BIT {
int c[N * 5];
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int v) {
    while (pos <= n) {
        c[pos] = max(c[pos], v);
        pos += lowbit(pos);
    }
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res = max(res, c[pos]);
        pos -= lowbit(pos);
    }
    return res;
}
} // namespace BIT
vector<int> pos[N];
int main() {
    cin >> n;
    n *= 5;
    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        pos[c].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        for (int j = 4; ~j; j--) {
            BIT::add(pos[c][j], BIT::query(pos[c][j] - 1) + 1);
        }
    }
    cout << BIT::query(n) << endl;
    return 0;
}
// Asusetic eru quionours
