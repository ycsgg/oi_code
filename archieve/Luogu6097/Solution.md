### P6097 【模板】子集卷积

也许会有用的技术

枚举子集可以 $O(3^n)$ 来做，不过可以使用更加优秀的技术

考虑FWT的位运算卷积 $C_k=\sum\limits_{i|j=k}A_iB_j$

如果想让他们满足 $i\&j=0$ 即 $\mathrm{pop}(i)+\mathrm{pop}(j)=\mathrm{pop}(k)$

$\mathrm{pop}(i)$ 为 $i$ 二进制中 $1$ 的个数

将 $A$ 替换为多项式 $A(x)=\sum A_ix^{\mathrm{pop}(i)}$

这样位运算卷积后提取 $[x^{\mathrm{pop}(k)}]C(x)$ 的系数就是我们想要的

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 1000000009;
const int N   = 1058576;
int m;
struct Poly {
    int a[21];
    void operator+=(const Poly &B) {
        for (int i = 0; i <= m; i++)
            a[i] = (a[i] + B.a[i]) % mod;
    }
    int &operator[](int x) {
        return a[x];
    }
    const int &operator[](const int &x) const {
        return a[x];
    }
    void operator-=(const Poly &B) {
        for (int i = 0; i <= m; i++)
            a[i] = (a[i] - B[i]) % mod;
    }
    Poly operator*(const Poly &B) const {
        Poly R;
        for (int i = 0; i <= m; i++)
            R[i] = 0;
        for (int i = 0; i <= m; i++)
            for (int j = 0; i + j <= m; j++)
                R.a[i + j] = (R[i + j] + 1ll * a[i] * B[j]) % mod;
        return R;
    }
};
Poly operator*(const int &x, const Poly &A) {
    Poly res;
    for (int i = 0; i <= m; i++) {
        res[i] = x * A[i];
    }
    return res;
}
void FWT(Poly *f, int n, int type) {
    for (int l = 1; l < n; l *= 2)
        for (int p = 0; p < n; p += 2 * l)
            for (int k = 0; k < l; k++)
                f[p | l | k] += type * f[p | k];
}
Poly F[N], G[N], T[N];
int n, cnt[N];
int main() {
    scanf("%d", &m);
    n = (1 << m);
    for (int i = 1; i < n; i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &F[i][cnt[i]]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &G[i][cnt[i]]);
    }
    FWT(F, n, 1);
    FWT(G, n, 1);
    for (int i = 0; i < n; i++)
        F[i] = F[i] * G[i];
    FWT(F, n, -1);
    for (int i = 0; i < n; i++)
        printf("%d ", (F[i][cnt[i]] + mod) % mod);
    return 0;
}
// Asusetic eru quionours

```

