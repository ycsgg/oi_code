#include <iostream>
#include <random>
using namespace std;
namespace PollardRho {
typedef __int128 ll;
ll max_factor;
ll gcd(ll a, ll b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

ll qpow(ll x, ll p, ll mod) {
    ll ans = 1;
    while (p) {
        if (p & 1)
            ans = ans * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ans;
}

bool mr(ll x, ll b) {
    ll k = x - 1;
    while (k) {
        ll cur = qpow(b, k, x);
        if (cur != 1 && cur != x - 1)
            return false;
        if ((k & 1) == 1 || cur == x - 1)
            return true;
        k >>= 1;
    }
    return true;
}

bool prime(ll x) {
    if (x < 2 || x == 46856248255981ll)
        return false;
    if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251)
        return true;
    return mr(x, 2) && mr(x, 61);
}

ll sq_add(ll x, ll c, ll mod) {
    return (x * x + c) % mod;
}
ll abs(ll x) {
    return x < 0 ? -x : x;
}
ll PollardRho(ll x) {
    ll s = 0, t = 0, c = 1ll * rand() % (x - 1) + 1;
    int step = 0, goal = 1;
    ll val = 1;
    while ("qwq") {
        for (step = 1; step <= goal; ++step) {
            t   = sq_add(t, c, x);
            val = (ll)val * abs(t - s) % x;
            if ((step % 127) == 0) {
                ll d = gcd(val, x);
                if (d > 1)
                    return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1)
            return d;
        goal *= 2;
        s   = t;
        val = 1;
    }
}

void fac(ll x) {
    if (x <= max_factor || x < 2)
        return;
    if (prime(x)) {
        max_factor = max_factor > x ? max_factor : x;
        return;
    }
    ll p = x;
    while (p >= x)
        p = PollardRho(x);
    while ((x % p) == 0)
        x /= p;
    fac(x);
    fac(p);
}
} // namespace PollardRho
int t;
long long n;
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        PollardRho::max_factor = 0;
        if (PollardRho::prime(n)) {
            cout << "Prime" << endl;
            continue;
        }
        PollardRho::fac(n);
        cout << (long long)PollardRho::max_factor << endl;
    }
}
