#include <array>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
int n, k;
map<int, int> cnt;
int main() {
    cin >> n >> k;
    vector<vector<int>> record(k, vector<int>(n));
    vector<ll> s(k), s2(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> record[i][j];
            s[i] += record[i][j];
            s2[i] += record[i][j] * record[i][j];
        }
    }
    for (int i = 0; i < k - 1; i++) {
        cnt[s[i + 1] - s[i]]++;
    }
    int pos;
    int cpos = 1;
    for (int i = 0; i < k - 1; i++) {
        if (cnt[s[i + 1] - s[i]] == 1) {
            pos  = i + 1;
            cpos = (pos < 3 ? 4 : 1); // FIX
            break;
        }
    }
    int d  = (s[cpos] - s[cpos - 1]);
    int d2 = s2[cpos + 1] + s2[cpos - 1] - 2 * s2[cpos];
    cout << pos << " ";
    for (int i = 0; i < n; i++) {
        int now = record[pos][i];
        int res = record[pos][i] + d - (s[pos] - s[pos - 1]);
        int dif = res * res - now * now;
        if (s2[pos + 1] + s2[pos - 1] - 2 * (s2[pos] + dif) == d2) {
            cout << res;
            cout.flush();
            return 0;
        }
    }
    return 0;
}
// Asusetic eru quionours