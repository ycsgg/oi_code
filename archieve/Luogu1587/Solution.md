### P1587 [NOI2016] 循环之美

考虑在十进制下如果循环节长度为 $l$ ，则 $\dfrac{10^lp}{q}, \dfrac{p}{q}$ 的小数部分相同，同理 $\dfrac{k^lp}{q}, \dfrac{p}{q}$  也是

则 $\dfrac{k^lp}{q}-\lfloor\dfrac{k^lp}{q}\rfloor = \dfrac{p}{q}-\lfloor\dfrac{p}{q}\rfloor$

$\Rightarrow k^lp -q\lfloor\dfrac{k^lp}{q}\rfloor=p-q\lfloor\dfrac{p}{q}\rfloor$

$\Rightarrow k^lp \equiv p \pmod q \land p \perp q$

$\Rightarrow k^l \equiv 1 \pmod q$

$\Rightarrow k \perp q$

则要计算 $\sum\sum[i\perp j][ j \perp k]$

$\sum\sum [\gcd(i,j)=1][j\perp k]$

$\sum\sum\sum\limits_{d|i,d|j}\mu(d)[j \perp k]$

传统艺能 $d$ 提前

$\sum\limits_{d}\mu(d)\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}[jd \perp k]$

$\sum\limits_{d}\mu(d)\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}[j \perp k][d \perp k]$

$\sum\limits_{d}\mu(d)\lfloor\frac{n}{d}\rfloor[d \perp k] \sum\limits_{i=1}^{\lfloor\frac{m}{d}\rfloor}[i \perp k]$

最后那个和式 $g(n)=\sum\limits_{i=1}^{n} [i \perp k]$

因为 $\gcd(i,k)=\gcd(i+k,k)$

所以有 $g(n)=\lfloor\frac{n}{k}\rfloor\varphi(k)+g(n \bmod k)$

可以预处理

考虑 $f(n)=\sum\limits_{d=1}^n\mu(d)[d \perp k]$

$f(n)=\sum\limits_{i=1}^n [i \perp k] f(\lfloor\frac{n}{i}\rfloor)-\sum\limits_{i=2}^n[i \perp k]f(\lfloor\frac{n}{i}\rfloor)$

$\sum\limits_{i=1}^n [i \perp k] f(\lfloor\frac{n}{i}\rfloor)=\sum\limits_{i=1}^n[i \perp k]\sum\limits_{j=1}^{\lfloor\frac{n}{i}\rfloor}[j \perp k]\mu(j)$

$=\sum\limits_{i=1}^m \sum\limits_{j=1}^{\lfloor\frac{n}{i}\rfloor}[ij \perp k]\mu(j)=\sum\limits_{T=1}^n\sum\limits_{d|T}[T \perp k]\mu(d)=\sum\limits_{T=1}^n[T \perp k][T=1]=1$

$f(n)=1-\sum\limits_{i=2}^n[i \perp k]f(\lfloor\frac{n}{i}\rfloor)$

杜教筛即可