#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 15;
struct Triangle {
    ll x, y, r;
} A[N];
int n;
Triangle Intersect(const Triangle &A, const Triangle &B) {
    Triangle C;
    C.x = max(A.x, B.x);
    C.y = max(A.y, B.y);
    C.r = min(A.x + A.y + A.r, B.x + B.y + B.r) - C.x - C.y;
    if (C.r <= 0) {
        return {0, 0, 0};
    } else {
        return C;
    }
}
ll calc(int S) {
    int cnt = __builtin_popcount(S);
    Triangle res = {-1, -1, -1};
    for (int i = 0; i < n; i++) {
        if (S & (1 << i)) {
            if (~res.r) {
                res = Intersect(res, A[i]);
            } else {
                res = A[i];
            }
        }
    }
    auto tmp = res.r * res.r;
    cnt--;
    tmp <<= cnt;
    if (cnt & 1) {
        tmp = -tmp;
    }
    return tmp;
}
// 01101111

// 00010111

// 10000110

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i].x >> A[i].y >> A[i].r;
    }
    ll ans = 0;
    for (int S = 1; S < (1 << n); S++) {
        ans += calc(S);
    }
    if (ans & 1) {
        cout << ans / 2 << ".5";
    } else {
        cout << ans / 2 << ".0";
    }
    return 0;
}
// Asusetic eru quionours.