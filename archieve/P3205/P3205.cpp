
#include <iostream>
using namespace std;
#define Err(args...)
const int N   = 1004;
const int Mod = 19650827;
int n;
int h[N];
int dp_left[N][N], dp_right[N][N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        dp_left[i][i] = 1;
        // dp_right[i][i] = 1;
    }
    for (int len = 1; len <= n; len++) {
        for (int i = 1, j = i + len; j <= n; i++, j++) {
            if (h[i] < h[i + 1]) {
                dp_left[i][j] += dp_left[i + 1][j];
            }
            if (h[i] < h[j]) {
                dp_left[i][j] += dp_right[i + 1][j];
            }
            if (h[j] > h[i]) {
                dp_right[i][j] += dp_left[i][j - 1];
            }
            if (h[j] > h[j - 1]) {
                dp_right[i][j] += dp_right[i][j - 1];
            }
            dp_left[i][j] %= Mod;
            dp_right[i][j] %= Mod;
            Err(i << "|" << j);
            Err(dp_left[i][j]);
            Err(dp_right[i][j]);
        }
    }
    cout << (dp_left[1][n] + dp_right[1][n]) % Mod;
}


