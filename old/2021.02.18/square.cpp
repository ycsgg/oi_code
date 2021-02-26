#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int N  = 1e5 + 5;
struct Matrix {
    int a[3][3];
    Matrix(int k = 0) {
        memset(a, 0, sizeof(a));
        for (int i = 0; i < 3; ++i) {
            a[i][i] = k;
        }
    }
    Matrix operator*(const Matrix &x) {
        Matrix res;
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                for (int j = 0; j < 3; j++) {
                    res.a[i][j] = (res.a[i][j] + (ll)a[i][k] * x.a[k][j]) % mod;
                }
            }
        }
        return res;
    }
};
Matrix qpow(Matrix a, int b) {
    Matrix res(1);
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b /= 2;
    }
    return res;
}
int n, m;
int a[N];
Matrix A, B;
Matrix ans;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
    }
    A.a[0][0] = A.a[0][1] = A.a[0][2] = A.a[1][1] = A.a[2][0] = A.a[2][1] = 1;
    A.a[1][2] = A.a[2][2] = 2;
    B.a[0][0] = B.a[0][1] = B.a[0][2] = B.a[1][1] = B.a[2][2] = 1;
    B.a[1][2]                                                 = 2;
    ans.a[0][0] = ans.a[0][1] = ans.a[0][2] = 1;
    for (int i = 1; i <= m; ++i) {
        ans = ans * qpow(A, (a[i] - a[i - 1] - 1));
        ans = ans * B;
    }
    ans = ans * qpow(A, n - a[m] - 1);
    cout << ans.a[0][2];
}