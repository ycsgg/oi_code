### P5591 小猪佩奇学数学

单位根反演

~~虽然说纯数学题不好，但是划着舒服~~

$\large\sum\binom{n}{i}p^i\lfloor\dfrac{i}{k}\rfloor$

~~因为我们事先知道了这是单位根反演题所以拆成能搞的形式~~

考虑到 $\lfloor\dfrac{i}{k}\rfloor=\sum\limits_{j\le i}[k|j]-1$

又 $[k|j]=\dfrac{1}{k}\sum\limits_{d \le k-1}\omega_k^{dj}$

带入 $\lfloor\dfrac{i}{k}\rfloor=\sum\limits_{j}\dfrac{1}{k}\sum\limits_{d}\omega^{dj}_k-1$

然后大力推式子

$\large\dfrac{1}{k}\sum\limits_{i}\binom{n}{i}p^i\sum\limits_{j}\sum\limits_{d}\omega^{dj}_k$

$\large = \dfrac{1}{k}\sum\limits_d\sum\limits_i\binom{n}{i}p^i\dfrac{\omega_k^{d(i+1)-1}}{\omega^d_k-1}$

$\large =\dfrac{1}{k}\sum\limits_d\dfrac{\sum\limits_i\binom{n}{i}(p\omega^d_k)^k-\sum\limits_i\binom{n}{i}p^i}{\omega^d_k-1}$

$\large\dfrac{1}{k}\sum\limits_d\dfrac{\omega_k^d(p\omega_k^d+1)^n-(p+1)^n}{\omega_k^d-1}$

当然最后有一个 $-(p+1)^n$

显然 $\omega_k$ 在 $\bmod p$ 意义下就是 $g^{\frac{p-1}{k}}$

还得特判 $ d=0 $ 

**Asusetic eru quionours**