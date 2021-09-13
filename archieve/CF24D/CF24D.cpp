#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e3 + 10;
int n, m, x, y;

double M[N][N];
double dp[N][N];
void build(int x) {
    M[1][1] = M[m][m] = 2;
    M[1][2] = M[m][m - 1] = -1;
    M[1][m + 1] = dp[x + 1][1] + 3;
    M[m][m + 1] = dp[x + 1][m] + 3;
    for (int i = 2; i < m; i++) {
        M[i][i - 1] = M[i][i + 1] = -1;
        M[i][i] = 3;
        M[i][m + 1] = dp[x + 1][i] + 4;
    }
}
void Gauss(int x) {
    for (int i = 1; i < m; i++) {
        double k = M[i + 1][i] / M[i][i];
        M[i + 1][i] = 0;
        M[i + 1][i + 1] -= M[i][i + 1] * k;
        M[i + 1][m + 1] -= M[i][m + 1] * k;
    }
    dp[x][m] = M[m][m + 1] / M[m][m];
    for (int i = m - 1; i >= 1;i--){
        dp[x][i] = (M[i][m + 1] - dp[x][i + 1] * M[i][i + 1]) / M[i][i];
    }
}
int main() {
    cin >> n >> m >> x >> y;
    if(m==1){
        cout << (n - x) * 2;
        return 0;
    }
    for (int i = n - 1; i >= x; i--) {
        build(i);
        Gauss(i);
    }
    cout << dp[x][y];
    return 0;
}
// Asusetic eru quionours.