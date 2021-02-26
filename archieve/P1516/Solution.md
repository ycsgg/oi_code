### P1516 青蛙的约会

https://www.luogu.com.cn/problem/P1516

本质求解同余方程$x+km\equiv y+kn \;(mod \; l)$

变形后可以得到

$k(n-m)+lz=x-y \quad z\in Z$

exgcd然后求最小正解即可

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
ll ans, x1, y1;

ll exgcd(ll a, ll b, ll &x1, ll &y1) {
    if (!b) {
        x1 = 1;
        y1 = 0;
        return a;
    }
    ans  = exgcd(b, a % b, x1, y1);
    ll t = x1;
    x1   = y1;
    y1   = t - a / b * y1;
    return ans; 
}

int main() {
    ll n, m, x, y, l;
    cin >> x >> y >> m >> n >> l;
    ll b = n - m, a = x - y;
    if (b < 0) {
        b = -b;
        a = -a;
    }
    exgcd(b, l, x1, y1);
    if (a % ans != 0){
        cout << "Impossible";
    }
    else{
        int mod = l / ans;
        int res=((x1*(a/ans))%mod+mod)%mod;
        cout << res;
    }
}
```

