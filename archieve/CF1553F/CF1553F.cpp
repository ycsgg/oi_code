#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll    = long long;
const int N = 3e5 + 10;
namespace BIT {
struct BIT {
    array<ll, N> c;
    int lowbit(int x) {
        return x & (-x);
    }
    ll query(int x) {
        ll res = 0;
        while (x) {
            res += c[x];
            x -= lowbit(x);
        }
        return res;
    }
    void add(int x, ll v) {
        while (x < N) {
            c[x] += v;
            x += lowbit(x);
        }
    }
};
} // namespace BIT
BIT::BIT val, num;
int n;
ll res, sum;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        res += 1ll * sum + 1ll * x * (i - 1) - val.query(x);
        for (int j = x; j < N; j += x) {
            int l = min(j + x - 1, N - 1);
            res -= j * (num.query(l) - num.query(j - 1));
            val.add(j, j);
            val.add(l + 1, -j);
        }
        num.add(x, 1);
        sum += x;
        cout << res << " ";
    }
    return 0;
}
// Asusetic eru quionours