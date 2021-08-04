#include <array>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int mod = 65521;
namespace Matrix {
struct Matrix {
    int row, col;
    vector<vector<ll>> arr;
    void init(int row, int col, int typ = 1) {
        this->row = row;
        this->col = col;
        arr = vector<vector<ll>>(row, vector<ll>(col));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (i == j && row == col) {
                    arr[i][j] = 1 * typ;
                } else {
                    arr[i][j] = 0;
                }
            }
        }
    }
    auto &operator[](int x) {
        return arr[x];
    }
    const auto &operator[](int x) const {
        return arr[x];
    }
    Matrix(int row, int col) : row(row), col(col) {
        init(row, col, 0);
    }
    Matrix(int n = 2) {
        col = row = n;
        init(n, n, 0);
    }
    Matrix(const Matrix &m) {
        init(m.row, m.col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                arr[i][j] = m[i][j];
            }
        }
    }
    Matrix operator*(const Matrix &m) const {
        // cout << "MUL" << endl;
        Matrix res(row, m.col);
        for (int k = 0; k < col; k++) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < m.col; j++) {
                    res[i][j] += 1ll * (arr[i][k] * m[k][j]) % mod;
                    res[i][j] %= mod;
                }
            }
        }
        return res;
    }
};
ostream &operator<<(ostream &out, const Matrix &A) {
    for (int i = 0; i < A.col; i++) {
        cout << "{";
        for (int j = 0; j < A.row; j++) {
            if (j != A.row - 1) {
                cout << A[i][j] << ",";
            } else {
                cout << A[i][j];
            }
        }
        cout << "},";
        cout << endl;
    }
    return out;
}
Matrix qpow(Matrix A, ll b) {
    assert(A.col == A.row);
    Matrix res;
    res.init(A.row, A.col, 1);
    while (b) {
        if (b & 1) {
            res = res * A;
        }
        A = A * A;
        b /= 2;
    }
    return res;
}
} // namespace Matrix
const int N = 55;
ll S1[N] = {0, 1};
ll S2[N] = {0, 1, 1, 3};
ll S3[N] = {0, 1, 1, 3, 16, 75, 336, 1488};
ll S4[N] = {0,     1,     1,     3,     16,   125,   864,  5635,  35840,
            29517, 48795, 64376, 52310, 4486, 28336, 8758, 64387, 31184};
ll S5[N] = {0,     1,     1,     3,     16,    125,   1296,  12005,
            38927, 26915, 65410, 9167,  63054, 58705, 18773, 9079,
            38064, 46824, 48121, 50048, 47533, 30210, 24390, 51276,
            45393, 357,   44927, 15398, 15923, 31582, 56586, 25233,
            41258, 21255, 21563, 16387, 39423, 26418, 10008, 6962,
            42377, 50881, 54893, 50452, 23715, 53140};

ll F1[N] = {1};
ll F2[N] = {3, 65520, 0};
ll F3[N] = {5, 65518, 3, 65516, 1, 0, 0};
ll F4[N] = {7,  65520, 65496, 31, 65469, 65437, 300, 65437, 65469,
            31, 65496, 65520, 7,  65520, 0,     0,   0};
ll F5[N] = {8,     5,     65489, 40,    364,   63172, 62845, 2793,  7304,
            50170, 14272, 13974, 32712, 27590, 63226, 30516, 31431, 62449,
            44809, 2992,  62529, 20712, 3072,  34090, 35005, 2295,  37931,
            32809, 51547, 51249, 15351, 58217, 62728, 2676,  2349,  65157,
            65481, 32,    65516, 65513, 1,     0,     0,     0,     0};
ll solve(ll n, ll *F, ll *S, ll len) {
    Matrix::Matrix A(len);
    for (int i = 0; i < len; i++) {
        A[0][i] = F[i];
    }
    for (int i = 1; i < len; i++) {
        A[i][i - 1] = 1;
    }
    if (n <= len) {
        return S[n];
    }
    A = qpow(A, n - len);
    ll res = 0;
    for (int i = 0; i < len; i++) {
        res = (res + A[0][i] * S[len - i] % mod) % mod;
        res %= mod;
    }
    return res % mod;
}
ll n;
int k;
int main() {
    cin >> k >> n;
    ll ans = 0;
    switch (k) {
    case 1:
        ans = solve(n, F1, S1, 1);
        break;
    case 2:
        ans = solve(n, F2, S2, 3);
        break;
    case 3:
        ans = solve(n, F3, S3, 7);
        break;
    case 4:
        ans = solve(n, F4, S4, 17);
        break;
    case 5:
        ans = solve(n, F5, S5, 45);
        break;
    default:
        break;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours