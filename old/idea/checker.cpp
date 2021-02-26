#include <iostream>
using namespace std;
string s;
int nxt[105];
void kmp(string s) {
    int len = s.length();
    nxt[0]  = -1;
    int k = -1, j = 0;
    while (j < len) {
        if (k == -1 || s[k] == s[j]) {
            k++;
            j++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }
    }
}
int main() {
    cin >> s;
    kmp(s);
    int now = s.length();
    int Ex  = (1 << now - 1);
    while (nxt[now] > 0) {
        int pos = nxt[now];
        Ex += (1 << pos - 1);
        now = nxt[now];
    }
    cout << Ex * 2;
}