#include <cstdio>
#include <iostream>
using namespace std;
const double eps = 1e-8;
int n, cnt[1 << 21], LIM;
double P[1 << 21], ans;
int main() {
    cin >> n;
    LIM = 1 << n;
    for (int i = 0; i < LIM; ++i) {
        cin >> P[i];
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    for (int i = 1; i < LIM; i <<= 1) {
        int p = i << 1;
        for (int j = 0; j < LIM; j += p) {
            for (int k = 0; k < i; ++k) {
                P[i + j + k] += P[j + k];
            }
        }
    }
    for (int i = 1; i < LIM; ++i) {
        if (1 - P[(LIM - 1) ^ i] > eps) {
            ans += ((cnt[i] & 1) ? 1 : -1) / (1 - P[(LIM - 1) ^ i]);
        }
    }
    if (ans < 1e-10)
        cout << "INF" << endl;
    else
        printf("%.10lf\n", ans);
    return 0;
}