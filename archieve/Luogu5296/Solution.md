### P5296 [北京省选集训2019]生成树计数

考虑 $k=1$ 的时候怎么从边权积之和变成边权和之和，发现只要矩阵元素放一个多项式 $1+wx$ 就好了

因为 $[x]\sum\prod (1+w_ix)$ 就是所有边权之和的和

对于其他的 $k$ 可以发现因为 $(w_1+w_2)^k=\sum \binom{k}{i}w_1^iw_2^{k-i}$ 是个二项卷积

所以把权值改成 $e^{w_ix}$ 即可