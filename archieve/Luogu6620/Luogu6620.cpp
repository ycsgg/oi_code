#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
int n, m, k;
char a[31];
int nxt[31];
int match[31][31];
void kmp() {
    nxt[0] = -1;
    for (int i = 1; i <= m; i++) {
        int j = nxt[i - 1];
        while (j != -1 && a[j + 1] != a[i])
            j = nxt[j];
        nxt[i] = j + 1;
    }
    nxt[0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = '0'; j <= '9'; j++) {
            int temp = i;
            while (a[temp + 1] != j && temp > 0)
                temp = nxt[temp];
            if (a[temp + 1] == j)
                temp++;
            if (temp < m)
                match[i][temp]++;
        }
    }
}
struct Matrix {
    ll v[31][31];
    Matrix() {
        memset(v, 0, sizeof(v));
    }
    ll *operator[](int x) {
        return v[x];
    }
    Matrix operator*(Matrix &b) const {
        Matrix res;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                for (int d = 0; d < m; d++) {
                    res[i][j] += v[i][d] * b[d][j] % k;
                    res[i][j] %= k;
                }
            }
        }
        return res;
    }
};
Matrix qpow(Matrix a, int b) {
    Matrix res;
    for (int i = 0; i < m; i++) {
        res[i][i] = 1;
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
Matrix F, G;
int main() {
    cin >> n >> m >> k;
    cin >> a + 1;
    kmp();
    F[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            G[i][j] = match[i][j];
        }
    }
    G      = qpow(G, n);
    F      = F * G;
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        ans += F[0][i];
        ans %= k;
    }
    cout << ans;
    return 0;
}