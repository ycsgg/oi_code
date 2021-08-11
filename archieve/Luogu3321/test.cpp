#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#define size          3000010
#define ll            long long
#define db            double
#define il            inline
#define rint          int
#define gc            getchar()
#define rep(i, s, n)  for (int i = s; i <= n; i++)
#define drep(i, n, s) for (int i = n; i >= s; --i)
#ifdef WIN32
#define ld "%I64d"
#else
#define ld "%lld"
#endif
#define Mod 1004535809

using namespace std;

il ll r() {
    char c;
    ll x, f = 1;
    for (c = gc; !isdigit(c); c = gc)
        if (c == '-')
            f = -1;
    x = c - '0';
    for (c = gc; isdigit(c); c = gc)
        x = x * 10 + c - '0';
    return x * f;
}

ll F1[size], F0[size], c[size], A[size], po[size], pv[size];
int Lg, L, l1, l2, rev[size], n, m, S, X, g, pg[size];

il ll ksm(ll x, ll y, ll mod) {
    ll res = 1;
    while (y) {
        if (y & 1)
            res = (res * x) % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

int G(int s) {
    int q[1010] = {0};
    rep(i, 2, s - 2) if ((s - 1) % i == 0) q[++q[0]] = i;
    for (int i = 2;; i++) {
        bool B = 1;
        for (int j = 1; j <= q[0] && B; j++)
            if (ksm(i, q[j], s) == 1)
                B = 0;
        if (B)
            return i;
    }
    return -1;
}

void Rader(int tmp) {
    Lg = 0, L = 1;
    while (L < tmp)
        L <<= 1, Lg++;
    L <<= 1, Lg++;
    rep(i, 0, L - 1) for (int t = i, j = 1; j <= Lg; j++) rev[i] <<= 1,
        rev[i] |= t & 1, t >>= 1;
    ll I = ksm(3, Mod - 2, Mod);
    for (int i = 1; i <= L; i <<= 1)
        po[i] = ksm(3, (Mod - 1) / i, Mod), pv[i] = ksm(I, (Mod - 1) / i, Mod);
}

void dft(ll F[], int sgn) {
    rep(i, 0, L - 1) A[i] = F[rev[i]];
    rep(i, 0, L - 1) F[i] = A[i];
    for (int i = 2; i <= L; i <<= 1) {
        ll wi = po[i];
        if (sgn == -1)
            wi = pv[i];
        for (int k = 0; k < L; k += i) {
            ll ww = 1, x = 0, y = 0;
            rep(j, 0, i / 2 - 1) {
                x = F[k + j];
                y = ww * F[k + j + i / 2] % Mod;
                F[k + j] = (x + y) % Mod;
                F[i / 2 + j + k] = (x - y + Mod) % Mod;
                ww = (ww * wi) % Mod;
            }
        }
    }
    if (sgn == -1)
        for (ll I = ksm(L, Mod - 2, Mod), i = 0; i < L; i++)
            F[i] = (F[i] * I) % Mod;
}

void Ksm(int y) {
    F1[0] = 1;
    while (y) {
        dft(F0, 1);
        if (y & 1) {
            dft(F1, 1);
            rep(i, 0, L - 1) F1[i] = (F1[i] * F0[i]) % Mod;
            dft(F1, -1);
            drep(i, L - 1, m - 1) F1[i - m + 1] = (F1[i - m + 1] + F1[i]) % Mod,
                                             F1[i] = 0;
            rep(i, 0, m - 1) cout << F1[i] << " ";
            cout << endl;
        }
        rep(i, 0, L - 1) F0[i] = (F0[i] * F0[i]) % Mod;
        dft(F0, -1);
        drep(i, L - 1, m - 1) F0[i - m + 1] = (F0[i - m + 1] + F0[i]) % Mod,
                                         F0[i] = 0;
        rep(i, 0, m - 1) cout << F0[i] << " ";
        cout << endl;
        y >>= 1;
    }
}

int main() {
    n = r();
    m = r();
    X = r();
    S = r();
    g = G(m);
    ll Q = 1, qx;
    rep(i, 1, m - 2) Q = Q * g % m, pg[Q] = i;
    rep(i, 1, S) {
        qx = r();
        if (qx)
            F0[pg[qx]] = 1;
    }
    Rader(m);
    Ksm(n);
    printf("%lld\n", F1[pg[X]]);
    return 0;
}
