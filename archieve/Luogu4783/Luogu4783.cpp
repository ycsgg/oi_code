#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using Matrix = vector<vector<int>>;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll b) {
    ll B = 1;
    while (b) {
        if (b & 1) {
            B = B * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return B;
}
void swap(Matrix &A, int i, int j) {
    swap(A[i], A[j]);
}
void output(Matrix &A) {
    for (auto &row : A) {
        for (auto &v : row) {
            cout << v << ' ';
        }
        cout << '\n';
    }
}
Matrix Inverse(Matrix A) {
    Matrix B(A);
    auto n = (int)B.size();
    for (auto &row : B) {
        row.assign(n, 0);
    }
    for (int i = 0; i < n; i++) {
        B[i][i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (!A[i][i]) {
            for (int j = i + 1; j < n; j++) {
                if (A[j][i]) {
                    swap(A, i, j);
                    swap(B, i, j);
                    break;
                }
            }
        }
        if (!A[i][i]) {
            cout << "No Solution";
            exit(0);
        }
        ll inv = qpow(A[i][i], mod - 2);
        for (int j = 0; j < n; j++) {
            A[i][j] = 1ll * A[i][j] * inv % mod;
            B[i][j] = 1ll * B[i][j] * inv % mod;
        }
        for (int j = i + 1; j < n; j++) {
            auto t = -A[j][i];
            for (int k = 0; k < n; k++) {
                A[j][k] = (A[j][k] + 1ll * A[i][k] * t % mod + mod) % mod;
                B[j][k] = (B[j][k] + 1ll * B[i][k] * t % mod + mod) % mod;
            }
        }
    }
    for (int i = n - 2; ~i; i--) {
        for (int j = i + 1; j < n; j++) {
            auto t = -A[i][j];
            for (int k = 0; k < n; k++) {
                A[i][k] = (A[i][k] + 1ll * A[j][k] * t % mod + mod) % mod;
                B[i][k] = (B[i][k] + 1ll * B[j][k] * t % mod + mod) % mod;
            }
        }
    }
    return B;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    Matrix A(n, vector<int>(n, 0));
    for (auto &row : A) {
        for (auto &v : row) {
            cin >> v;
        }
    }
    auto inv = Inverse(A);
    output(inv);
    return 0;
}
// Asusetic eru quionours.