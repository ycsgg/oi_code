#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1005;
int n, q;
struct Data {
    int a, b, c;
};
struct Query {
    int m, s, k, id;
};
int main() {
    cin >> n;
    vector<Data> d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i].c >> d[i].a >> d[i].b;
    }
    sort(d.begin() + 1, d.end(), [&](const auto &A, const auto &B) -> bool {
        return A.a < B.a;
    });
    cin >> q;
    vector<Query> qr(q + 1);
    for (int i = 1; i <= q; i++) {
        cin >> qr[i].m >> qr[i].k >> qr[i].s;
        qr[i].id = i;
    }
    sort(qr.begin() + 1, qr.end(), [&](const auto &A, const auto &B) -> bool {
        return A.m < B.m;
    });
    int now = 1;
    vector<int> dp(100001);
    vector<bool> ans(q + 1);
    for (int i = 1; i <= q; i++) {
        while (d[now].a <= qr[i].m && now <= n) {
            for (int k = 100000; k >= d[now].c; k--) {
                dp[k] =
                    max(dp[k], (k - d[now].c ? min(dp[k - d[now].c], d[now].b)
                                             : d[now].b));
            }
            now++;
        }
        if (dp[qr[i].k] > qr[i].s + qr[i].m) {
            ans[qr[i].id] = 1;
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << (ans[i] ? "TAK" : "NIE") << endl;
    }
    return 0;
}
// Asusetic eru quionours