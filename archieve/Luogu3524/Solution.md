### P3524 [POI2011]IMP-Party

https://www.luogu.com.cn/problem/P3524

显然两个没有连边的点不在一个团里

所以把没有两两连边的点删掉

剩下的一定全都有连边

输出n个就好

```cpp
#include<iostream>
using namespace std;
const int N = 3005;
int G[N][N];
int n, m;
int in[N];
bool vis[N];
int main() {
    cin>>n>>m;
    for (int i = 1; i <= m;i++){
        int u, v;
        cin >> u >> v;
        G[u][v] = G[v][u] = 1;
        in[u]++;
        in[v]++;
    }
    for (int i = 1; i <= n;i++){
        if(!vis[i]){
            for (int j = i + 1; j <= n;j++){
                if(!vis[j]&&!G[i][j]){
                    vis[i] = vis[j] = 1;
                    break;
                }
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n;i++){
        if(!vis[i]){
            cout << i << " " << endl;
            cnt++;
            if(cnt*3==n){
                return 0;
            }
        }
    }
    return 0;
}
```

