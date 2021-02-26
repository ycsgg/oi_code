#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const ll N   = 2e5 + 5;
const ll mod = 1e9 + 7, inv = 142857001;
int k, n;
int nxt[N];
ll qpow(ll a, ll b) {
    ll res = 1, base = a;
    while (b) {
        if (b & 1) {
            res = (res * base) % mod;
        }
        base = base * base % mod;
        b /= 2;
    }
    return res;
}
ll invx(ll x) {
    return qpow(x, mod - 2) % mod;
}
void kmp(int *s, int len) {
    nxt[0] = -1;
    int k = -1, j = 0;
    while (j < len) {
        if (k == -1 || s[k] == s[j]) {
            k++;
            j++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }
    }
}
int s[N];
int p[N];
ll mp[N];
ll sp = 1ll;
int t;
void init() {
    mp[n + 1] = 1ll;
    sp        = 1ll;
    memset(nxt, 0, sizeof(nxt));
}
int main() {
    cin >> t;
    while (t--) {
        bool flag = 1;
        init();
        cin >> n >> k;
        mp[n + 1] = 1ll;
        for (int i = 1; i <= k; i++) {
            cin >> p[i];
            p[i] = (p[i] * inv) % mod;
        }
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
        }
        for (int i = n; i >= 1; i--) {
            if (p[s[i]] == 0) {
                cout << -1 << endl;
                flag = 0;
                break;
            }
            mp[i] = (mp[i + 1] % mod * p[s[i]] % mod) % mod;
        }
        if (!flag)
            continue;
        kmp(s + 1, n);
        int now = n;
        while (nxt[now] > 0) {
            int pos = nxt[now];
            sp      = (sp + mp[pos + 1]) % mod;
            now     = nxt[now];
        }
        cout << sp * invx(mp[1]) % mod << endl;
    }
}