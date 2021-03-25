### P4173 残缺的字符串

很技巧的题

对于两个字符$a,b$ 定义匹配函数$\delta(a,b)=(a-b)^2$

这样再定义两个字符串匹配的函数$p_{x}(A,B)=\sum\limits_{i=0}^{m-1}\delta(B[i],A[x-m+1+i])$ 表示$B[x,x+m-1]$与$A$匹配

为了便于计算，设$A^{op}$是$A$的反转串，那么$p_x(A,B)=\sum\limits_{i=0}^{m-1}\delta(A^{op}[m-i-1],B[x-m+i+1])$

有类似卷积的感觉，展开得到$p_x(A,B)=\sum\limits_{i=0}^{m-1}A[i]^2+\sum\limits_{i=0}^{m-1}B[x-m+i+1]^2-2\sum\limits_{i=0}^{m-1}A^{op}[m-i-1]B[x-m+i+1]$

前两项可以预处理出来，最后一项是个卷积

处理通配符的话可以定义$\delta(a,b)=(a-b)^2ab$ 

$p_x(A,B)=\sum\limits_{i=0}^{m-1}A^{op}[m-i-1]^3B[x-m+i+1]+\sum\limits_{i=0}^{m-1}A^{op}[m-i-1]B[x-m+i+1]^3-2\sum\limits_{i=0}^{m-1}A^{op}[m-i-1]^2B[x-m+i+1]^2$

都是卷积

写成比较好看的形式$p_x(A,B)=\sum\limits_{i+j=x}A^{op}[i]^3B[j]+\sum\limits_{i+j=x}A^{op}[i]B[j]^3-2\sum\limits_{i+j=x}A^{op}[i]^2B[j]^2$

多项式乘法

(NTT会被卡，只能写FFT)

```cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1100000;
namespace Poly {
double pi;
int rev[N];
struct Complex {
    double x, y;
    Complex() {
    }
    Complex(double xx, double yy) {
        x = xx, y = yy;
    }
    friend Complex operator*(Complex a, Complex b) {
        return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    friend Complex operator/(Complex a, double b) {
        return Complex(a.x / b, a.y / b);
    }
    friend Complex operator+(Complex a, Complex b) {
        return Complex(a.x + b.x, a.y + b.y);
    }
    friend Complex operator-(Complex a, Complex b) {
        return Complex(a.x - b.x, a.y - b.y);
    }
    friend Complex operator*(Complex a, double b) {
        return Complex(a.x * b, a.y * b);
    }
    friend Complex operator*(double b, Complex a) {
        return Complex(a.x * b, a.y * b);
    }
};
void FFT(Complex *a, int lim, int f) {
    for (int i = 0; i < lim; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        Complex wn(cos(pi / i), f * sin(pi / i));
        for (int j = 0; j < lim; j += (i << 1)) {
            Complex w(1, 0);
            for (int k = 0; k < i; k++) {
                Complex x = a[j + k], y = w * a[j + k + i];
                a[j + k]     = x + y;
                a[j + k + i] = x - y;
                w            = w * wn;
            }
        }
    }
    if (f == -1)
        for (int i = 0; i < lim; i++)
            a[i] = a[i] / lim;
}
int getLen(int deg) {
    int len = 1;
    while (len < deg) {
        len *= 2;
    }
    return len;
}
void getRev(int n) {
    for (int i = 1; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
}
void PreTransform(int deg) {
    getRev(getLen(2 * deg));
}
} // namespace Poly
using Poly::Complex;
int n, m;
Complex A[N], B[N], C[N];
char sA[300005], sB[300005];
int a[N], b[N],st[N],top;
int main() {
    Poly::pi = acos(-1);
    cin >> m >> n;
    Poly::PreTransform(n);
    int len = Poly::getLen(n * 2);
    cin >> sA >> sB;
    for (int i = 0; i < m; i++) {
        if (sA[i] != '*') {
            a[i] = sA[i] - 'a' + 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (sB[i] != '*') {
            b[i] = sB[i] - 'a' + 1;
        }
    }
    reverse(a, a + m);
    for (int i = 0; i < m; i++) {
        A[i] = Complex(a[i] * a[i] * a[i], 0);
    }
    for (int i = 0; i < n; i++) {
        B[i] = Complex(b[i], 0);
    }
    Poly::FFT(A, len, 1);
    Poly::FFT(B, len, 1);
    for (int i = 0; i < len; i++) {
        C[i] = A[i] * B[i];
    }
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    for (int i = 0; i < m; i++) {
        A[i] = Complex(a[i] * a[i], 0);
    }
    for (int i = 0; i < n; i++) {
        B[i] = Complex(b[i] * b[i], 0);
    }
    Poly::FFT(A, len, 1);
    Poly::FFT(B, len, 1);
    for (int i = 0; i < len; i++) {
        C[i] = C[i] - 2.0 * A[i] * B[i];
    }
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    for (int i = 0; i < m; i++) {
        A[i] = Complex(a[i], 0);
    }
    for (int i = 0; i < n; i++) {
        B[i] = Complex(b[i] * b[i] * b[i], 0);
    }
    Poly::FFT(A, len, 1);
    Poly::FFT(B, len, 1);
    for (int i = 0; i < len; i++) {
        C[i] = C[i] + A[i] * B[i];
    }
    Poly::FFT(C, len, -1);
    for (int i = m - 1; i < n; i++) {
        if (fabs(C[i].x) < 0.5) {
            st[++top] = i - m + 2;
        }
    }
    cout << top << endl;
    for (int i = 1; i <= top;i++){
        cout << st[i] << " ";
    }
        return 0;
}
```