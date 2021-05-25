#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int N = 105;
char a[N], b[N], c[N];
int nxt[N];
string dp[N][N][N];
vector<int> to[N][N];
string ans;
int main() {
    cin >> a + 1 >> b + 1 >> c + 1;
    int la = strlen(a + 1);
    int lb = strlen(b + 1);
    int lc = strlen(c + 1);
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= lc; i++) {
        while (j && c[i] != c[j + 1]) {
            j = nxt[j];
        }
        if (c[i] == c[j + 1]) {
            j++;
        }
        nxt[i] = j;
    }
    for (int i = 0; i <= lc; i++) {
        for (int j = 0; j <= 25; j++) {
            int now = i;
            while (now && (c[now + 1] - 'A') != j) {
                now = nxt[now];
            }
            if ((c[now + 1] - 'A') == j) {
                now++;
            }
            to[now][j].push_back(i);
        }
    }
    auto qaq = [&](string &A, const string &B) -> void {
        if (A.size() < B.size()) {
            A = B;
        }
    };
    for (int i = 1; i <= la; i++) {
        for (int j = 1; j <= lb; j++) {
            for (int k = 0; k < lc; k++) {
                if (a[i] == b[j]) {
                    for (auto p : to[k][a[i] - 'A']) {
                        qaq(dp[i][j][k], dp[i - 1][j - 1][p] + a[i]);
                    }
                }
                qaq(dp[i][j][k], dp[i - 1][j][k]);
                qaq(dp[i][j][k], dp[i][j - 1][k]);
            }
        }
    }
    for (int i = 0; i < lc; i++) {
        qaq(ans, dp[la][lb][i]);
    }
    if (ans.size() == 0) {
        cout << 0 << endl;
    } else {
        cout << ans;
    }
    return 0;
}
// Asusetic eru quionours