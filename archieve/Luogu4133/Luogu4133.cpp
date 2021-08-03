#include <array>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
const int N = 90;
ll n;
ll fib[N], s[N];
map<pair<ll, ll>, ll> mp;
ll dfs(ll x, ll cur) {
    if (!x || !cur) {
        return !x;
    }
    auto &&now = make_pair(x, cur);
    if (mp.count(now)) {
        return mp[now];
    }
    if (x < fib[cur]) {
        mp[now] = dfs(x, cur - 1);
        return mp[now];
    }
    if (x > s[cur - 1]) {
        mp[now] = dfs(x - fib[cur], cur - 1);
        return mp[now];
    } else {
        mp[now] = dfs(x - fib[cur], cur - 1) + dfs(x, cur - 1);
    }
    return mp[now];
}
int main() {
    cin >> n;
    fib[0] = fib[1] = 1;
    s[0] = 1;
    s[1] = 2;
    for (int i = 2; i <= 89; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        s[i] = s[i - 1] + fib[i];
    }
    cout << dfs(n, 89);
    return 0;
}
// Asusetic eru quionours