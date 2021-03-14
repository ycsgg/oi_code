### CF717A Festival Organization

$\newcommand{\Strling}[2]{\begin{bmatrix}#1 \\ #2\end{bmatrix}}$

设$f_i$是长度为$i$的符合条件的串的数量，如果设$g_{i,j}$表示长度为$i$的串结尾是$j$

容易列出转移方程$\large\begin{equation*}\left\{\begin{array}\left g_{i,0}=g_{i-1,1}\\g_{i,1}=g_{i-1,1}+g_{i-1,0}\end{array}\right.\end{equation*}$，带入式子就能发现其实是斐波那契数列，即$f_i=F_{i+2}$，题目要求的就是$\large\sum\limits_{i=l+2}^{r+2}\binom{F_{i}}{k}$

(为了方便用$l,r$代替了$l+2,r+2$)

$\large \sum\limits_{i=l}^r\binom{F_i}{k}=\sum\limits_{i=l}^r\frac{F_i!}{k!(F_i-k)!}=\frac{1}{k!}\sum\limits_{i=l}^rF^{\underline{k}}_i=$

$\large\frac{1}{k!}\sum\limits_{i=0}^k\Strling{k}{i}\sum\limits_{j=l}^rF^i_j=\frac{1}{k!}\sum\limits_{i=0}^k\Strling{k}{i}\sum\limits_{j=l}^r(ax^j+by^j)^i$ (设$F_i$通项为$ax^i+by^i$)

$\large=\frac{1}{k!}\sum\limits_{i=0}^k\Strling{k}{i}\sum\limits_{j=l}^r\sum\limits_{m=0}^i \binom{i}{m}a^mb^{i-m}(x^my^{i-m})^j$

交换一下顺序得到

$\large\frac{1}{k!}\sum\limits_{i=0}^k\Strling{k}{i}\sum\limits_{m=0}^i \binom{i}{m}a^mb^{i-m}\sum\limits_{j=l}^r(x^my^{i-m})^j$

众所周知$F_i=\frac{1}{\sqrt{5}}(\frac{1+\sqrt{5}}{2})^i-\frac{1}{\sqrt{5}}(\frac{1-\sqrt{5}}{2})^i$

另一个大问题是$\sqrt{5}$在$\bmod10^9+7$下不存在（或者说没有二次剩余

所以我们只能采用Cipolla那种扩域的手段扩展到$\mathbb{Z_p}(\sqrt{5})$来算