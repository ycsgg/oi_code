### P4213 【模板】杜教筛（Sum）

杜教筛用来在亚线性时间复杂度内求出积性数论函数的前缀和，复杂度为$O(n^\frac{2}{3})$，跑$10^{10}$还是挺稳的

考虑我们需要计算的$S(n)=\sum\limits_{i=1}^n f(i)$，目标是搞出一个关于$S(\lfloor\frac{n}{i}\rfloor)$的递推式

对于一个数论函数$g(i)$，有$\sum\limits_{i=1}^n(f*g)(i)=\sum\limits_{i=1}^ng(i)S(\lfloor\frac{n}{i}\rfloor)$

证明：

​	$\huge\sum\limits_{i=1}^n\sum\limits_{d|i}f(d)g(\lfloor\frac{i}{d}\rfloor)=\sum\limits_{i=1}^ng(i)\sum\limits_{d=1}^{\lfloor\frac{n}{d}\rfloor}f(i)=\sum\limits_{i=1}^ng(i)S(\lfloor\frac{n}{i}\rfloor)$

于是$g(1)S(n)=\sum\limits_{i=1}^n(f*g)(i)-\sum\limits_{i=2}^ng(i)S(\lfloor\frac{n}{i}\rfloor)$