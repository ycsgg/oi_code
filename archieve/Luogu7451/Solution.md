### P7451 [THUSCH2017] 杜老师

先参考 [[CF1100F Ivan and Burgers]] 的计数方法，但是发现这个区间长度实在是太大了

所以我们合理的想到当区间长度大于一个特定的值的时候，一定有一个方案使得每一个出现过的质因数都能够在线性基里面占据一个单独的位置

预处理质数然后用 $\frac{L-1}{p_i}=\frac{R}{p_i}$ 检查是否出现过

```cpp
#include <array>
#include <bitset>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
using ll    = long long;
const int N = 1e7 + 9, C = 500;
const ll mod    = 998244353;
const int SQRTN = 3165;
namespace Sieve {
array<bool, N> vis;
array<int, N> prime, id, maxp;
int pcnt;
void init() {
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            maxp[i]       = i;
            id[i]         = pcnt;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (prime[j] * i >= N) {
                break;
            }
            vis[prime[j] * i]  = 1;
            maxp[prime[j] * i] = max(maxp[i], prime[j]);
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
} // namespace Sieve
namespace XorBasis {
bitset<C> basis[C];
bool insert(bitset<C> x) {
    for (int i = C - 1; ~i; i--) {
        if (x[i]) {
            if (!basis[i].any()) {
                basis[i] = x;
                return true;
            }
            x ^= basis[i];
        }
    }
    return false;
}
void clear() {
    for (int i = 0; i < C; i++) {
        basis[i].reset();
    }
}
} // namespace XorBasis

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
unordered_map<int, bitset<C>> mp;
int cnt;
void insert(int x) {
    using namespace Sieve;
    bitset<C> div;
    for (int i = 1; i <= pcnt && x != 1 && prime[i] <= SQRTN; i++) {
        while (x % prime[i] == 0) {
            x /= prime[i];
            div[i].flip();
        }
    }
    if (x != 1) {
        if (!mp.count(x)) {
            mp[x] = div;
            cnt++;
            return;
        }
        div ^= mp[x];
    }
    cnt += XorBasis::insert(div);
}
void clear() {
    cnt = 0;
    mp.clear();
    XorBasis::clear();
}
namespace Task1 {
void solve(int l, int r) {
    for (int i = l; i <= r; i++) {
        insert(i);
    }
}
} // namespace Task1
namespace Task2 {
void solve(int l, int r) {
    for (int i = 1; i <= Sieve::pcnt && Sieve::prime[i] <= r; i++) {
        if (r / Sieve::prime[i] != (l - 1) / Sieve::prime[i]) {
            cnt++;
        }
    }
}
} // namespace Task2
int T;
int main() {
    Sieve::init();
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        if (r - l + 1 <= 7000) {
            Task1::solve(l, r);
        } else {
            Task2::solve(l, r);
        }
        cout << qpow(2, (r - l + 1) - cnt) << endl;
        clear();
    }
    return 0;
}
// Asusetic eru quionours

```

#线性基 