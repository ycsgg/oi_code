#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using f80 = long double;
const f80 eps = 1e-8;
const int N = 2005;
int n, A, B;
f80 a[N], b[N], c[N];
struct Data {
    f80 val;
    int Acnt, Bcnt;
    friend Data max(const Data &x, const Data &y) {
        return x.val > y.val ? x : y;
    }
    friend Data operator+(const Data &x, const Data &y) {
        return Data{x.val + y.val, x.Acnt + y.Acnt, x.Bcnt + y.Bcnt};
    }
};
int main() {
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    static auto dp = [&](f80 da, f80 db) -> auto {
        auto res = Data{0, 0, 0};
        for (int i = 1; i <= n; ++i)
            res = res + max(max(Data{a[i] - da, 1, 0}, Data{b[i] - db, 0, 1}),
                            max(Data{a[i] + b[i] - a[i] * b[i] - da - db, 1, 1},
                                Data{0, 0, 0}));
        res.val += da * A + db * B;
        return res;
    };
    static auto check = [&](f80 x) -> auto {
        double l = 0, r = 1;
        while (l + eps < r) {
            auto mid = (l + r) / 2;
            auto res = dp(x, mid);
            if (res.Bcnt >= B) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return dp(x, l);
    };
    double l = 0, r = 1;
    while (l + eps < r) {
        auto mid = (l + r) / 2;
        auto res = check(mid);
        if (res.Acnt >= A) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << check(l).val << endl;
};
// Asusetic eru quionours
