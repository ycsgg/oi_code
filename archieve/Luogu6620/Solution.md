### P6620 [省选联考 2020 A 卷] 组合数问题

先改写成下降幂多项式，变成$\sum\limits_{k=0}^nb_i\sum\limits_{i=0}^mx^kk^{\underline{i}}\binom{n}{i}$

$b_i$是下降幂多项式的系数

 对后面的系数记作$G_i(x)$

对$(1+x)^n=\sum\limits_{k=0}^nx^k\binom{n}{k}$求导得到

$n^{\underline{i}}(1+x)^{n-i}=\sum\limits_{k=0}^nx^{k-i}k^{\underline{i}}\binom{n}{k}$

乘$x^i$就是$G_i(x)$