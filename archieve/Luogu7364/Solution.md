### P7364 有标号二分图计数

考虑 $n$ 个点黑白染色的图 

有 $\sum \binom{n}{i}2^{i(n-i)}$

即选 $i$ 个点染成黑色，然后黑白连边

设其 EGF 为 $F(x)$

设有标号联通二分图的 EGF 是 $Q(x)$

答案为 $G(x)=\exp Q(x)$

然后发现黑白染色其实是给二分图分配颜色的方案

则 $F(x)=\sum\frac{2^iQ^i(x)}{i!}=\exp2Q(x)$

因为每一块二分图分配一个初始颜色都会构成黑白染色的方案

所以 $G(x)=\sqrt{F(x)}$

$F(x)$ 的系数

$f_n=n!\sum \frac{1}{i!(n-i)!}2^{\binom{n}{2}-\binom{n-i}{2}-\binom{i}{2}}=n!2^{\binom{n}{2}}\sum\dfrac{1}{2^{\binom{n}{2}i!}}\dfrac{1}{2^{\binom{n-i}{2}(n-i)!}}$

可以卷积

#数学

#多项式