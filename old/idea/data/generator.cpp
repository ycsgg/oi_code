#include "testlib.h"
#include <algorithm>
#include <iostream>
using namespace std;
int sum = 1000000;
int d[1000000];
bool pos[1000000];
int main(int argc, char *argv[]) {
    int pt = atoi(argv[1]);
    rnd.setSeed(time(0) * rnd.next());
    registerGen(argc, argv, 1);
    for (int u = 1; u <= pt; u++) {
        startTest(u);
        int t     = atoi(argv[2]);
        int paran = atoi(argv[3]);
        int parak = atoi(argv[4]);
        cout << t << endl;
        for (int i = 1; i <= t; i++) {
            memset(pos, 0, sizeof(pos));
            sum   = 1000000;
            int n = min(rnd.next(max(paran / 2, 1), paran) * u * 33,100000);
            int k = min(rnd.next(max(parak / 2, 1), parak) * u * 33,100000);
            cout << n << " " << k << endl;

            for (int i = 1; i < k; i++) {
                int dla = rnd.next(1, 1000000);
                while (pos[dla]) {
                    dla = rnd.next(1, 1000000);
                }
                pos[dla] = 1;
                d[i]     = dla;
            }
            sort(d + 1, d + k);
            d[k] = 1000000;
            for (int i = 1; i <= k; i++) {
                cout << d[i] - d[i - 1] << " ";
            }
            cout << endl;
            for (int i = 1; i <= n; i++) {
                cout << rnd.next(1, k) << " ";
            }
            cout << endl;
        }
    }
}