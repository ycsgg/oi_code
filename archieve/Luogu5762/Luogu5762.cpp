#include <iostream>
#include <algorithm>
using namespace std;
const int OFFSET = 1000;
int val[2005][2005];
struct Data {
    int x1, yOO1, x2, y2, tag, z;
} B[250];
int n;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, z, r;
        cin >> x >> y >> z >> r;
        x += OFFSET;
        y += OFFSET;
        z += OFFSET;
        B[i * 2]     = {x - r + 1, y - r + 1, x + r, y + r, 1, z - r};
        B[i * 2 + 1] = {x - r + 1, y - r + 1, x + r, y + r, -1, z + r};
    }
    n *= 2;
    sort(B, B + n, [&](const auto &A, const auto &B) -> bool {
        return A.z < B.z;
    });
    int S = 0, ans = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = B[i].x1; j <= B[i].x2; j++)
            for (int k = B[i].yOO1; k <= B[i].y2; k++) {
                val[j][k] += B[i].tag;
                if (B[i].tag == 1 && val[j][k] == 1) {
                    S++;
                }
                if (B[i].tag == -1 && val[j][k] == 0) {
                    S--;
                }
            }
        ans += (B[i + 1].z - B[i].z) * S;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours