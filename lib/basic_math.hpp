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
