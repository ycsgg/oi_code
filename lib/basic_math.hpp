#pragma once
namespace ModInt {
using i32 = int;
using u32 = unsigned int;
using u64 = unsigned long long;
using i64 = long long;
// P should be a odd number
template <u32 P>
struct modint {
    private:
    u32 val;
    static constexpr u32 get_r() {
        u32 iv = P;
        for (u32 i = 0; i != 4; ++i)
            iv *= 2U - P * iv;
        return -iv;
    }
    static constexpr u32 r = get_r(), r2 = -u64(P) % P;

    public:
    modint(u32 val) : val(reduce(u64(val) * r2)) {
    }
    modint(const modint &b) : val(b.val) {
    }
    static u32 reduce(u64 x) {
        return x + (u64(u32(x) * r) * P) >> 32;
    }
    static u32 norm(u32 x) {
        return x - (P & -(x >= P));
    }
    u32 get() const {
        u32 res = reduce(val) - P;
        return res + (P & -(res >> 31));
    }
    operator u32() const {
        return get();
    }
    operator i32() const {
        return i32(get());
    }
    modint &operator=(const modint &rhs) {
        val = rhs.val;
        return *this;
    }
    modint operator-() const {
        modint res;
        res.val = (P << 1 & -(val != 0)) - val;
        return res;
    }
    modint &operator+=(const modint &rhs) {
        return val += rhs.val - (P << 1), val += P << 1 & -(val >> 31), *this;
    }
    modint &operator-=(const modint &rhs) {
        return val -= rhs.val, val += P << 1 & -(val >> 31), *this;
    }
    modint &operator*=(const modint &rhs) {
        return val = reduce(u64(val) * rhs.val), *this;
    }
    friend modint operator+(const modint &lhs, const modint &rhs) {
        return ModInt(lhs) += rhs;
    }
    friend modint operator-(const modint &lhs, const modint &rhs) {
        return ModInt(lhs) -= rhs;
    }
    friend modint operator*(const modint &lhs, const modint &rhs) {
        return ModInt(lhs) *= rhs;
    }
    friend bool operator==(const modint &lhs, const modint &rhs) {
        return norm(lhs.val) == norm(rhs.val);
    }
    friend bool operator!=(const modint &lhs, const modint &rhs) {
        return norm(lhs.val) != norm(rhs.val);
    }
    friend std::istream &operator>>(std::istream &in, modint &rhs) {
        in >> rhs.val;
        rhs.val = reduce(u64(rhs.val)) * r2;
        return in;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) {
        return os << rhs.get();
    }
};
// assume P is a prime number in qpow
template <u32 P>
modint<P> qpow(modint<P> a, i64 b) {
    b %= P - 1;
    if (b < 0) {
        b += P - 1;
    }
    modint<P> res(1);
    while (b) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}
template <u32 P>
modint<P> inv(const modint<P> &x) {
    return qpow(x, -1);
}
template <u32 P>
modint<P> &operator/=(const modint<P> lhs, const modint<P> &rhs) {
    return lhs *= (inv(rhs));
}
template <u32 P>
modint<P> operator/(const modint<P> &lhs, const modint<P> &rhs) {
    return ModInt(lhs) /= rhs;
}
} // namespace ModInt
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
