#include <bitset>
#include <complex>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define LOCAL

typedef long long ll;
typedef long double ld;
typedef double db;
typedef string str;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<db, db> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<db> vd;
typedef vector<str> vs;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<pd> vpd;

#define mp      make_pair
#define f       first
#define s       second
#define sz(x)   (int)(x).size()
#define all(x)  begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define rsz     resize
#define ins     insert
#define ft      front()
#define bk      back()
#define pf      push_front
#define pb      push_back
#define eb      emplace_back
#define lb      lower_bound
#define ub      upper_bound

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a)    FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a)    ROF(i, 0, a)
#define trav(a, x)   for (auto &a : x)

// TO_STRING
#define ts to_string
str ts(char c) {
    return str(1, c);
}
str ts(const char *s) {
    return (str)s;
}
str ts(str s) {
    return s;
}
str ts(bool b) {
#ifdef LOCAL
    return b ? "true" : "false";
#else
    return ts((int)b);
#endif
}
template <class A> str ts(complex<A> c) {
    stringstream ss;
    ss << c;
    return ss.str();
}
str ts(vector<bool> v) {
    str res = "{";
    F0R(i, sz(v)) res += char('0' + v[i]);
    res += "}";
    return res;
}
template <size_t SZ> str ts(bitset<SZ> b) {
    str res = "";
    F0R(i, SZ) res += char('0' + b[i]);
    return res;
}
template <class A, class B> str ts(pair<A, B> p);
template <class T> str ts(T v) { // containers with begin(), end()
#ifdef LOCAL
    bool fst = 1;
    str res  = "{";
    for (const auto &x : v) {
        if (!fst)
            res += ", ";
        fst = 0;
        res += ts(x);
    }
    res += "}";
    return res;
#else
    bool fst = 1;
    str res  = "";
    for (const auto &x : v) {
        if (!fst)
            res += " ";
        fst = 0;
        res += ts(x);
    }
    return res;

#endif
}
template <class A, class B> str ts(pair<A, B> p) {
#ifdef LOCAL
    return "(" + ts(p.f) + ", " + ts(p.s) + ")";
#else
    return ts(p.f) + " " + ts(p.s);
#endif
}

// OUTPUT
template <class A> void pr(A x) {
    cout << ts(x);
}
template <class H, class... T> void pr(const H &h, const T &... t) {
    pr(h);
    pr(t...);
}
void ps() {
    pr("\n");
} // print w/ spaces
template <class H, class... T> void ps(const H &h, const T &... t) {
    pr(h);
    if (sizeof...(t))
        pr(" ");
    ps(t...);
}

// DEBUG
void DBG() {
    cerr << "]" << endl;
}
template <class H, class... T> void DBG(H h, T... t) {
    cerr << ts(h);
    if (sizeof...(t))
        cerr << ", ";
    DBG(t...);
}
#ifdef LOCAL // compile with -DLOCAL, chk -> fake assert
#define dbg(...)                                                               \
    cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [",         \
        DBG(__VA_ARGS__)
#define chk(...)                                                               \
    if (!(__VA_ARGS__))                                                        \
        cerr << "Line(" << __LINE__ << ") -> function(" << __FUNCTION__        \
             << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")"                    \
             << "\n",                                                          \
            exit(0);
#endif