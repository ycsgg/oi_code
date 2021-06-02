#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int N = 100004;
string s;
int t;
int tmp[N];
long long qres;
int a[N];
void msort(int l, int r) {
    if (l >= r)
        return;
    int m = l + r >> 1;
    msort(l, m);
    msort(m + 1, r);
    int i = l, j = m + 1;
    int k = 0;
    while (i <= m && j <= r) {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            qres += 1ll * m - i + 1ll;
        }
    }
    while (i <= m)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = tmp[k];
}
int main() {
    cin >> t;
    auto turn = [&](char c) -> int {
        if (c == 'A') {
            return 1;
        }
        if (c == 'N') {
            return 2;
        }
        if (c == 'O') {
            return 3;
        }
        if (c == 'T') {
            return 4;
        }
    };
    while (t--) {
        cin >> s;
        vector<int> v[5];
        for (int i = 0; i < s.length(); i++) {
            v[turn(s[i])].push_back(i + 1);
        }
        char chr[]     = {'A', 'N', 'O', 'T'};
        string ans     = "";
        long long mmax = 0;
        do {
            qres       = 0;
            string res = "";
            int cnt    = 0;
            for (int i = 0; i < 4; i++) {
                for (auto p : v[turn(chr[i])]) {
                    res += chr[i];
                    a[++cnt] = p;
                }
            }
            msort(1, cnt);
            if (qres >= mmax) {
                mmax = qres;
                ans  = res;
            }
        } while (next_permutation(chr, chr + 4));
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours