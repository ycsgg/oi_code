#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
ofstream score("score.txt");
ifstream inf("input");
int n, k;
string s;
int nxt[105];
void kmp(string s) {
    int len = s.length();
    nxt[0]  = -1;
    int k = -1, j = 0;
    while (j < len) {
        if (s[j] != 'H' && s[j] != 'T') {
            score << 0;
            cerr << s << "contains illegal character: " << s[j];
            exit(0);
        }
        if (k == -1 || s[k] == s[j]) {
            k++;
            j++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }
    }
}
typedef long long ll;
ll getEx(string s) {
    int len = s.length();
    ll res  = (1ll << len - 1);
    memset(nxt, 0, sizeof(nxt));
    kmp(s);
    int now = len;
    while (nxt[now] > 0) {
        int pos = nxt[now];
        res += (1 << pos - 1);
        now = nxt[now];
    }
    return res * 2;
}
int main(int argc, char *argv[]) {
    inf >> n >> k >> s;
    int now = 1;
    cout << s;
    ll atri = getEx(s);
    while (now <= k) {
        string ans;
        cin >> ans;
        if (ans.length() != n) {
            score << 0;
            cerr << "Answer is too looong!";
            return 0;
        }
        if(getEx(s)<=atri){
            score << 0;
            cerr << "You LOSE!";
        }else{
            
        }
    }
    score << 100;
    cerr << "TAT";
    return 0;
}