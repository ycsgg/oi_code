#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, m;
struct Data {
    int val, rk;
} a[N];
int main() {
    cin >> n >> m;
    n++;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].rk = i;
    }
    sort(a + 1, a + 1 + n, [&](const Data &A, const Data &B) -> bool {
        if (A.val == B.val) {
            return A.rk < B.rk;
        }
        return A.val < B.val;
    });
    int now = a[1].rk;
    for (int i = 1; i < n; i++) {
        cout << a[now].val << " ";
        now = a[now].rk;
    }
    return 0;
}
//Asusetic eru quionours