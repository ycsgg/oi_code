### P4449 于神之怒加强版

$$
\sum\limits_{i}\sum\limits_{j}\gcd(i,j)^k \\
=\sum\limits_{i}\sum\limits_{j}\sum\limits_{d}d^k[gcd(i,j)=d] \\
=\sum\limits_{d}d^k\sum\limits_{i}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j}^{\lfloor\frac{m}{d}\rfloor}\sum\limits_{k|i,k|j}\mu(k)\\
=\sum\limits_{d}d^k\sum\limits_{x}^{\lfloor\frac{n}{d}\rfloor}\mu(x)\lfloor\dfrac{n}{dx}\rfloor\lfloor\dfrac{m}{dx}\rfloor\\
T=dx\\
=\sum\limits_{T}\lfloor\dfrac{n}{T}\rfloor\lfloor\dfrac{m}{T}\rfloor\sum\limits_{d|T} d^k\mu(\dfrac{T}{d})
$$

以上是套路

然后考虑 $g(T)=\sum\limits_{d|T} d^k\mu(\dfrac{T}{d})$ 这个东西是个卷积形式 $\sigma_k * \mu$，所以是积性的

然后可以筛了

具体的

$g(T)=\prod g(p_i^{a_i})=\prod(p_i^{k(a_i-1)}\times\mu(p_i)+p_i^{ka_i}\times \mu(1))=\prod(p_i^{k(a_i-1)}(p_i^k-1))$

#数学

