
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 200100;
char a[N], b[N];
unsigned long long n;
unsigned long long cnt_forward[27][N], cnt_backward[27][N];
int main() {
    cin >> n;
    cin >> a + 1;
    cin >> b + 1;
    for (int i = 1; i <= n; i++) {
        cnt_forward[a[i] - 'A'][i] = i;
    }
    for (int i = n; i >= 1; i--) {
        cnt_backward[a[i] - 'A'][i] = n - i + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            cnt_forward[j][i] += cnt_forward[j][i - 1];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 26; j++) {
            cnt_backward[j][i] += cnt_backward[j][i + 1];
        }
    }
    double sum = 0;
    for (int i = 1; i <= n;i++){
        char c = b[i] - 'A';
        sum += cnt_forward[c][i] * (n - i + 1);
        sum += cnt_backward[c][i + 1] * i;
    }
    double ans = (double)sum / (double)(n * (n + 1) * (2 * n + 1) / 6.0);
    printf("%.9lf", ans);
    return 0;
}




