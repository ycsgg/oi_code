### P5444 [APIO2019]奇怪装置

看到个数大概就知道是找同余循环节

设$t_1,t_2$是两个相同的位置，那么
$$
\begin{equation}
\left\{
	\begin{array}{c}
	t_1 + \lfloor \frac{t_1}{B} \rfloor \equiv t_2 + \lfloor \frac{t_2}{B} \rfloor (\bmod A)\\
	t_1\equiv t_2 (\bmod B)
	\end{array}
\right.
\end{equation}
$$
 设$t_2=t_1+kB$

带入上式

$\large t_1 + \lfloor \frac{t_1}{B} \rfloor \equiv t_1+ kB + \lfloor \frac{t_1 + kB}{B} \rfloor (\bmod A)$

$\large t_1 + \lfloor \frac{t_1}{B} \rfloor \equiv t_1+ kB + \lfloor \frac{t_1}{B} +k \rfloor (\bmod A)$

$\large k(B+1)\equiv0(\bmod A) \Rightarrow A|k(B+1) \Rightarrow \frac{A}{gcd(A,B+1)}|k$

那么循环节$kB=\frac{AB}{gcd(A,B+1)}$

如果有一段区间完全包含整个循环节，那就直接输出

否则的话按$\bmod kB$分类，如果取完仍然是$l\le r$那么一定是被一个循环节完全包含

否则的话就是$[0,r]$与$[l-1,kB)$的覆盖

求一个线段覆盖就好了

比较憨憨的地方是循环节会炸long long，虽然没这个数据，而且也没影响

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 2e6 + 5;
__int128_t gcd128(__int128_t a, __int128_t b) {
    return b == 0 ? a : gcd128(b, a % b);
}
int n;
ll A, B;
ll prd;
struct Segment {
    ll l, r;
    Segment(){};
    Segment(ll a, ll b) {
        l = a;
        r = b;
    }
} line[N];
int cnt;
bool cmp(const Segment &a, const Segment &b) {
    return a.l < b.l;
}
int main() {
    cin >> n >> A >> B;
    __int128_t tprd = (__int128_t)1ll * A / gcd128(A, B + 1) * B;
    if (tprd >= 1e18) {
        prd = 1e18 + 1;
    } else {
        prd = tprd;
    }
    for (int i = 1; i <= n; i++) {
        ll li, ri;
        cin >> li >> ri;
        if (ri - li + 1 >= prd) {
            cout << prd << endl;
            return 0;
        }
        li %= prd;
        ri %= prd;
        if (li <= ri) {
            line[++cnt] = Segment(li, ri);
        } else {
            line[++cnt] = Segment(0, ri);
            line[++cnt] = Segment(li, prd - 1);
        }
    }
    sort(line + 1, line + 1 + cnt, cmp);
    ll nowl = line[1].l, nowr = line[1].r;
    ll ans = 0;
    for (int i = 2; i <= cnt; i++) {
        if (nowr < line[i].l) {
            ans += nowr - nowl + 1;
            nowl = line[i].l;
            nowr = line[i].r;
        } else {
            nowr = max(nowr, line[i].r);
        }
    }
    ans += nowr - nowl + 1;
    cout << ans;
    return 0;
}
```