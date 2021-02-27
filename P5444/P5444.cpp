#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 2e6 + 5;
__int128_t gcd128(__int128_t a, __int128_t b) {
    return b == 0 ? a : gcd128(b, a % b);
}
int n;
ll A, B;
ll prd;
struct Segment {
    ll l, r;
    Segment(){};
    Segment(ll a, ll b) {
        l = a;
        r = b;
    }
} line[N];
int cnt;
bool cmp(const Segment &a, const Segment &b) {
    return a.l < b.l;
}
int main() {
    cin >> n >> A >> B;
    __int128_t tprd = (__int128_t)1ll * A / gcd128(A, B + 1) * B;
    if (tprd >= 1e18) {
        prd = 1e18 + 1;
    } else {
        prd = tprd;
    }
    for (int i = 1; i <= n; i++) {
        ll li, ri;
        cin >> li >> ri;
        if (ri - li + 1 >= prd) {
            cout << prd << endl;
            return 0;
        }
        li %= prd;
        ri %= prd;
        if (li <= ri) {
            line[++cnt] = Segment(li, ri);
        } else {
            line[++cnt] = Segment(0, ri);
            line[++cnt] = Segment(li, prd - 1);
        }
    }
    sort(line + 1, line + 1 + cnt, cmp);
    ll nowl = line[1].l, nowr = line[1].r;
    ll ans = 0;
    for (int i = 2; i <= cnt; i++) {
        if (nowr < line[i].l) {
            ans += nowr - nowl + 1;
            nowl = line[i].l;
            nowr = line[i].r;
        } else {
            nowr = max(nowr, line[i].r);
        }
    }
    ans += nowr - nowl + 1;
    cout << ans;
    return 0;
}