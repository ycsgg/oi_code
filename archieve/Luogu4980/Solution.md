### P4980 【模板】Pólya 定理

直接给出Burnside引理

$G$是一个置换群，$X$是一个集合，$|X/G|$为$X$在$G$作用下等价类个数

$|X/G|=\frac{1}{|G|}\sum\limits_{g\in G}|X^g|$

$X^g=\{x\in X|g(x)=x\}$ 

证明随便找本近世代数就有

对本题的$G$为旋转$0,1,\dots,n-1$的置换

定义$M$为$1,2\dots,n$的所有可能排列

那么答案为$\frac{1}{|G|}\sum\limits_{g \in G}|M^g|$

对于旋转$k$来说一个元素是不动点意味着存在一个长度为$m$的循环节满足$m|k$，且必定$m|n$

故可以改为存在长度为$\gcd(k,n)$的循环节，而对于$k$来说前$\gcd(k,n)$任意，故大小为$n^{\gcd(k,n)}$

剩下的就是简单的莫反得到$\frac{1}{n}\sum\limits_{d|n}n^d\varphi(\frac{n}{d})$

而Pólya则是把置换拆成群然后得到$\frac{1}{|G|}\sum\limits_{g \in G}m^{c(g)}$

$c(g)$为轮换数，$m$为颜色数