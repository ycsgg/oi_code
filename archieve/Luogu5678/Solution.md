### P5678 [GZOI2017]河神

比较naive的题，观察大法好

可以观察到如果我们吧矩阵的运算改成题中定义的递推运算

那么暴算可知有结合律，那就可以快速幂

那就快速幂

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef unsigned long long ull;
const int N = 105;
int n, k;
struct Matrix {
    ull a[N][N];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
    Matrix operator*(const Matrix &b) const {
        Matrix res;
        for (int mid = 0; mid < k; mid++) {
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    res.a[i][j] |= a[i][mid] & b.a[mid][j];
                }
            }
        }
        return res;
    }
};
Matrix qpow(Matrix a, int b) {
    Matrix res;
    for (int i = 0; i < k; i++) {
        res.a[i][i] = -1;
    }
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b /= 2;
    }
    return res;
}
ull ans = 0;
ull a[N], b[N];
Matrix B;
int main() {
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= k; i++) {
        cin >> b[i];
    }
    if (n <= k) {
        cout << a[n];
        return 0;
    }
    reverse(b + 1, b + 1 + k);
    for (int i = 0; i < k; i++) {
        B.a[i][0] = b[i + 1];
    }
    for (int i = 1; i < k; i++) {
        B.a[i - 1][i] = -1;
    }
    B = qpow(B, n - k + 1);
    for (int i = 0; i < k; i++) {
        ans |= a[k - i - 1] & B.a[i][0];
    }
    cout << ans;
}
```

