#include <array>
#include <ctime>
#include <iostream>
#include <random>
using namespace std;
const int N = 12;
array<int, (1 << N) + 1> p, a, q, list;
array<bool, (1 << N) + 1> vispos, visval;
int n;
int main() {
    srand(time(0));
    cin >> n;
    int flag = 0;
    for (int i = 0; i < (1 << n); i++) {
        cin >> a[i];
        flag ^= a[i];
        list[i] = i;
    }
    if (flag) {
        cout << "Fou" << endl;
        return 0;
    }
    int tot = (1 << n);
    int cnt = 0;
    while (cnt < (1 << n)) {
        int pos = rand() % tot;
        int val = list[pos];
        if (pos != tot - 1) {
            list[pos] = list[tot - 1];
        }
        tot--;
        vector<int> tmp;
        bool flag = 0;
        for (int j = 0; j < (1 << n); j++) {
            if (!vispos[j] && !visval[val ^ a[j]]) {
                flag = visval[val ^ a[j]] = vispos[j] = 1;
                p[j]                                  = val;
                q[val ^ a[j]]                         = j;
                cnt++;
                break;
            } else if (!vispos[j]) {
                tmp.push_back(j);
            }
        }
        if (flag) {
            continue;
        }
        int j                 = tmp[rand() % tmp.size()];
        vispos[q[val ^ a[j]]] = 0;
        list[tot]             = p[q[val ^ a[j]]];
        tot++;
        p[j]               = val;
        vispos[j]          = 1;
        visval[val ^ a[j]] = 1;
        q[val ^ a[j]]      = j;
        cnt--;
        cnt++;
    }
    cout << "Shi" << endl;
    for (int i = 0; i < (1 << n); i++) {
        cout << p[i] << " ";
        ;
    }
    cout << endl;
    for (int i = 0; i < (1 << n); i++) {
        cout << (a[i] ^ p[i]) << " ";
        ;
    }
    return 0;
}
// Asusetic eru quionours