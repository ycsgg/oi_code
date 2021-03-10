#include <iostream>
using namespace std;
double n;
int main() {
    cin >> n;
    printf("%.9f", n * (n + 1) / (2 * (2 * n - 1)));
    return 0;
}