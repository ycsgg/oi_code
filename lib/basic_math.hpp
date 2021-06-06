#pragma once
namespace math {
using ll = long long;
ll qpow(ll base, int expt, ll mod = 998244353) {
    ll res = 1;
    while (expt) {
        if (expt & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        expt /= 2;
    }
    return res;
}
//类型 T 必须具有初始化为乘法单位元的默认构造函数
//与返回类型 T 的二元运算 * (T A,T B)
template <typename T> T qpow(T base, int expt) {
    T res;
    while (expt) {
        if (expt & 1) {
            res = res * base;
        }
        base = base * base;
        expt /= 2;
    }
    return res;
}

} // namespace math
namespace Matrix {
struct Matrix {
    int row, col;
    int **arr;
    void init(int row, int col, int typ = 1) {
        arr = new int *[row];
        for (int i = 0; i < row; i++) {
            arr[i] = new int[col];
            for (int j = 0; j < col; j++) {
                if (i == j && row == col) {
                    arr[i][j] = 1 * typ;
                } else {
                    arr[i][j] = 0;
                }
            }
        }
    }
    int *operator[](int x) {
        return arr[x];
    }
    const int *operator[](int x) const {
        return arr[x];
    }
    Matrix(int row = 2, int rol = 2, int typ = 1) : row(row), col(col) {
        init(row, col, typ);
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
        Matrix res(row, m.col, 0);
        for (int k = 0; k < col; k++) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < m.col; j++) {
                    res[i][j] += arr[i][k] * m[k][j];
                }
            }
        }
        return res;
    }
};

} // namespace Matrix
