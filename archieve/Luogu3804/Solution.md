### SAM

SAM被定义为接受一个串$S$的所有后缀的最小DFA

为了构造SAM，我们定义$E(t)$为串$t$在$S$中所有的出现位置，同时把$S$所有的字串$t$按$E(t)$划分为几个等价类，即$P(S)/E(t)$

每一个等价类都是SAM的一个状态，对于特定的状态$v$，有一个或多个子串与之匹配

为了方便设初始状态$t_0$的$E(t_0)$为每一个位置

定义状态的后缀链接$\mathrm{link}(v)$，设$w$是$v$中最长的串，那么$w$至少有一个后缀（至少是空后缀）在其他状态中，$\mathrm{link}(v)$就指向最长的不在$v$中的$w$的后缀所在的状态

易见$\mathrm{link}(v)$构成一个树

而同时$\mathrm{link}(v)$实际上就是$E(t)$集合由包含关系构成的树，在此略去证明

记$\max(v),\min(v)$分别是$v$中的最长最短子串，且$l_{\max},l_{\min}$为其长度

那么$v$中所有字符串$t$都是$\max(v)$的后缀，且长度覆盖$[l_{\min},l_{\max}]$

且对于非初始状态的$v$有$\mathrm{len}(\min(v))=\mathrm{len}(\mathrm{link}(v))+1$

而且沿着$\mathrm{link}(v)$开始遍历会回到初始状态并且所有经过的点的子串的长度的并集为$[0,l_{\max}]$

具体的构造上

对于添加新字符$c$

记录当前状态$last$

创建一个新状态$cur$，并使$len(cur)=len(last)+1$，从$last$开始，如果没有$c$的转移就加一个到$cur$的，然后跳后缀链接，如果有，就停止且记状态为$p$

如果没有，$link(cur)=0$

否则，记录$p$通过$c$转移到$q$

如果$len(p)+1=len(q)$，那么$link(cur)=q$

不然就创建一个$q$的复制状态$c_q$，令$len(c_q)=len(p)+1$，$link(cur)=c_q,link(q)=c_q$随后继续沿$p$的后缀链接走，把所有到$q$转移改为$c_q$

```cpp
void insert(int c) {
    int p    = last;
    int cur  = ++cnt;
    last     = cur;
    len[cur] = len[p] + 1;
    while (p && !nxt[p][c]) {
        nxt[p][c] = cur;
        p         = link[p];
    }
    if (!p)
        link[cur] = 1;
    else {
        int q = nxt[p][c];
        if (len[p] + 1 == len[q])
            link[cur] = q;
        else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[q], sizeof(nxt[q]));
            link[cq] = link[q];
            link[q] = link[cur] = cq;
            while (nxt[p][c] == q) {
                nxt[p][c] = cq;
                p         = link[p];
            }
        }
    }
    siz[cur] = 1;
}
```

