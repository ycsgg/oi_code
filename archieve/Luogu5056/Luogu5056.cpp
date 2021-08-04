#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
#define int ll
const int N = 14;
int n, m;
int mp[N][N];
ll p4[N];
signed main() {
    cin >> n >> m;
    int edx, edy;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            mp[i][j] = (c == '.');
            if (c == '.') {
                edx = i;
                edy = j;
            }
        }
    }
    unordered_map<ll, ll> dp[2];
    static auto getS = [&](ll x, ll y) -> ll {
        return x << (y << 1);
    };
    int cur = 0;
    dp[cur][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[cur ^ 1].clear();
            for (auto k : dp[cur]) {
                auto [S, val] = k;
                auto L = (S >> ((j - 1) << 1)) & 3;
                auto R = (S >> (j << 1)) & 3;
                if (!mp[i][j]) {
                    if (!L && !R)
                        dp[cur ^ 1][S] += val;
                    continue;
                }
                if (!L && !R) {
                    if (mp[i][j + 1] && mp[i + 1][j])
                        dp[cur ^ 1][S ^ getS(1, j - 1) ^ getS(2, j)] += val;
                }
                if (!L && R) {
                    if (mp[i][j + 1])
                        dp[cur ^ 1][S] += val;
                    if (mp[i + 1][j])
                        dp[cur ^ 1][S ^ getS(R, j) ^ getS(R, j - 1)] += val;
                }
                if (L && !R) {
                    if (mp[i][j + 1])
                        dp[cur ^ 1][S ^ getS(L, j - 1) ^ getS(L, j)] += val;
                    if (mp[i + 1][j])
                        dp[cur ^ 1][S] += val;
                }
                if (L == R) {
                    if (L == 1 && R == 1) {
                        int nowar = 0;
                        for (int p = j;; p++) {
                            int T = (S >> (p << 1)) & 3;
                            if (T == 1)
                                nowar++;
                            if (T == 2)
                                nowar--;
                            if (nowar == 0) {
                                dp[cur ^ 1][S ^ getS(L, j - 1) ^ getS(R, j) ^
                                            getS(2, p) ^ getS(1, p)] += val;
                                break;
                            }
                        }
                    }
                    if (L == 2 && R == 2) {
                        int nowar = 0;
                        for (int p = j - 1;; p--) {
                            int T = (S >> (p << 1)) & 3;
                            if (T == 2)
                                nowar++;
                            if (T == 1)
                                nowar--;
                            if (nowar == 0) {
                                dp[cur ^ 1][S ^ getS(L, j - 1) ^ getS(R, j) ^
                                            getS(1, p) ^ getS(2, p)] += val;
                                break;
                            }
                        }
                    }
                }
                if (L == 2 && R == 1) {
                    dp[cur ^ 1][S ^ getS(L, j - 1) ^ getS(R, j)] += val;
                }
                if (L == 1 && R == 2 && i == edx && j == edy) {
                    cout << val << endl;
                    return 0;
                }
            }
            cur ^= 1;
        }
        dp[cur ^ 1].clear();
        int U = (1 << ((m + 1) << 1)) - 1;
        for (auto p : dp[cur]) {
            dp[cur ^ 1][(p.first << 2) & U] += p.second;
        }
        cur ^= 1;
    }
    cout << 0 << endl;
    return 0;
}
// Asusetic eru quionours