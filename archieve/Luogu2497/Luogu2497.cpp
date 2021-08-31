#include <array>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using f80 = long double;
const int N = 5 * 100000 + 5;
const f80 INF = 1e15 + 10;
int n;
f80 m, ans = INF;
f80 x[N], R[N], v[N], dp[N], X[N], Y[N];
int A[N], q[N];
f80 Slope(int a, int b) {
    return (Y[b] - Y[a]) / (X[b] - X[a]);
}
void solve(int l, int r) {
    if (l == r) {
        Y[l] = x[l] * X[l] - dp[l];
        return;
    }
    int mid = (l + r) / 2;
    solve(l, mid);
    int tail = 0;
    for (int i = l; i <= mid; i++) {
        while (tail > 1) {
            if (X[q[tail]] == X[A[i]]) {
                if (Y[q[tail]] < Y[A[i]]) {
                    --tail;
                }
                break;
            } else if (Slope(q[tail - 1], q[tail]) <= Slope(q[tail], A[i])) {
                --tail;
            } else {
                break;
            }
        }
        q[++tail] = A[i];
    }
    for (int i = mid + 1; i <= r; i++) {
        while (tail > 1) {
            if (Slope(q[tail - 1], q[tail]) <= x[i]) {
                --tail;
            } else {
                break;
            }
        }
        dp[i] =
            min(dp[i], dp[q[tail]] + (x[i] - x[q[tail]]) * X[q[tail]] + v[i]);
    }
    solve(mid + 1, r);
    tail = l - 1;
    for (int i = l, j = mid + 1; i <= mid || j <= r;)
        if (i <= mid && j <= r) {
            if (X[A[i]] < X[A[j]]) {
                q[++tail] = A[i];
                ++i;
            } else {
                q[++tail] = A[j];
                ++j;
            }
        } else if (i <= mid)
            q[++tail] = A[i], ++i;
        else
            q[++tail] = A[j], ++j;
    for (int i = l; i <= r; i++)
        A[i] = q[i];
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> R[i] >> v[i];
        X[i] = sqrt(R[i]) / (2 * R[i]);
        A[i] = i;
    }
    dp[1] = v[1];
    for (int i = 2; i <= n; i++) {
        dp[i] = INF;
    }
    solve(1, n);
    for (int i = 1; i <= n; i++) {
        if (x[i] + R[i] >= m) {
            ans = min(ans, dp[i]);
        }
    }
    printf("%.3lf\n", (double)ans);
    return 0;
}
// Asusetic eru quionours