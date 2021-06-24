#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int q;
int main() {
    cin >> q;
    vector<ll> cost(q + 1), cnt(q + 1);
    vector<int> fa[20];
    for (int i = 0; i <= 19; i++) {
        fa[i].resize(q + 1);
    }
    cin >> cnt[0] >> cost[0];
    function<int(int)> find = [&](int x) -> int {
        for (int i = 19; ~i; i--) {
            if (cnt[fa[i][x]]) {
                x = fa[i][x];
            }
        }
        return x;
    };
    for (int i = 1; i <= q; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            cin >> fa[0][i] >> cnt[i] >> cost[i];
            for (int j = 1; j < 20; j++) {
                fa[j][i] = fa[j - 1][fa[j - 1][i]];
            }
        } else {
            int x, w;
            cin >> x >> w;
            ll ans = 0, tmp = w;
            while (cnt[x] && w) {
                int now = find(x);
                if (w > cnt[now]) {
                    w -= cnt[now];
                    ans += cnt[now] * cost[now];
                    cnt[now] = 0;
                } else {
                    cnt[now] -= w;
                    ans += w * cost[now];
                    w = 0;
                    break;
                }
            }
            cout << tmp - w << " " << ans << endl;
            cout.flush();
        }
    }
    return 0;
}