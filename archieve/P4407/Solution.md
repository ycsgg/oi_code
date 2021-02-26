### P4407 [JSOI2009]电子字典

https://www.luogu.com.cn/problem/P4407

建个trie树暴力dfs枚举所有编辑就好

没啥技术含量

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N = 10007;
int n, m;
char s[25];
int tr[N * 20][27],tot;
int endpos[N * 20];
void insert(char *s) {
    int now=0;
    int len = strlen(s);
    for (int i = 0; i < len;i++){
        if(!tr[now][s[i]-'a']){
            tr[now][s[i] - 'a'] = ++tot;
        }
        now = tr[now][s[i] - 'a'];
    }
    endpos[now] = 1;
}
bool word;
bool vis[N*20];
int visx[N];
int vistot;
void dfs(int rt, int cur, bool used, int len) {
    if(cur==len&&endpos[rt]&&!used){
        word = 1;
        return;
    }
    if(cur==len&&endpos[rt]&&used){
        if(!vis[rt]){
            visx[++vistot]      = rt;
            vis[rt] = 1;
        }
        return;
    }
    if(!used){
        if(cur<len){
            dfs(rt, cur + 1, 1, len);
        }
        for (int i = 0; i < 26;i++){
            if(tr[rt][i]){
                dfs(tr[rt][i], cur, 1, len);
                if(i!=s[cur]-'a'){
                    dfs(tr[rt][i], cur + 1, 1, len);
                }
            }
        }
    }
    if(cur>=len){
        return;
    }
    if(tr[rt][s[cur]-'a'])
        dfs(tr[rt][s[cur] - 'a'], cur + 1, used, len);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n;i++){
        cin >> s;
        insert(s);
    }
    for (int i = 1; i <= m;i++){
        cin >> s;
        int len = strlen(s);
        dfs(0, 0,0,len);
        if(word){
            cout << -1 << endl;
        } else {
            cout << vistot << endl;
        }
        while(vistot){
            vis[visx[vistot--]] = 0;
        }
        word = 0;
    }
    return 0;
}
```

