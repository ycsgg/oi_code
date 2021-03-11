### 【集训队作业2018】矩阵玩小凹

$\newcommand{\EulerNumber}[2]{\left\langle\begin{matrix}#1 \\ #2\end{matrix}\right\rangle}$

#### 题意：

一个$n\times m$的矩阵$A_{n,m}$，其中的元素是$[0,1]$中的随机实数，设$s_i=\sum A_{i,j}$求$Ex(\lfloor\min s_i\rfloor^k)$

(因为没发现能交的地方，random了几组数据放在了[矩阵玩小凹](https://www.luogu.com.cn/problem/U155600)上（并不保证写对了）)

#### 解：

因为每一行本质相同，所以我们只考虑第一行

记$f_i$为$\lfloor s_1 \rfloor=i$的概率，$d_i$是$\lfloor\min(s_i)\rfloor=i$的概率，那么答案就是$\sum\limits_{i=1}^{m-1}i^kd_i$

同时$d_i=(\sum\limits_{j=1}^{i} f_j)^n-(\sum\limits_{j=1}^{i-1}f_j)^n$

这都是好算的，我们考虑$f_i$怎么算

记$g_i=\sum_{j=1}^{i}A_{1,j}-\lfloor\sum_{j=1}^{i}A_{1,j}\rfloor$，容易发现这也是$[0,1]$内随机生成的

那么$\lfloor s_1\rfloor=\sum\limits_{i=2}^m[g_i<g_{i-1}]$

因为如果当前的$g_i$小于上一个$g_{i-1}$说明一定“溢出”了一个整数位（因为$A_{i,j}\in[0,1]$）

也就是说$f_i$就是随机$[0,1]$排列种上升的位置有$i$个的概率（这里我们忽略了存在相同的数字，因为在实数里随机出两个同样的数字的概率基本无）

那这个东西，我们把随机排列$n$中有$i$个上升位置的方案数

就是欧拉数$\left\langle\begin{matrix}n \\ i\end{matrix}\right\rangle$

实际上我们有$\left\langle\begin{matrix}n \\ i\end{matrix}\right\rangle=\sum(-1)^{i}\binom{n+1}{i}(m-i+1)^n$

证明有亿点难

对于$x_1+x_2+\dots+x_n \le x \quad x_i \ge 0$的超立方体体积记作$V_n(x)$

容易发现$h_1(x)=x$

$V_i(x)=\int_0^nh_{i-1}(t)\rm{d}t$

并不需要技巧就能得出$V_i(n)=\frac{n^i}{i!}$

考虑最原始的含义，$\sum\limits_{i=0}^m\left\langle\begin{matrix}n \\ i\end{matrix}\right\rangle$就是$\lfloor s_1\rfloor\le i+1$的概率，容斥$x> 1$的个数（因为$A_{i,j}\in[0,1]$），那么

$\sum\limits_{i=0}^m\left\langle\begin{matrix}n \\ i\end{matrix}\right\rangle=\sum\limits_{i=0}^{m+1}(-1)^i\binom{n}{i}V_n(m-i+1)$

差分一下就能得到$\left\langle\begin{matrix}n \\ i\end{matrix}\right\rangle=\sum(-1)^{i}\binom{n+1}{i}(m-i+1)^n$

这个是$i^n$与$(-1)^i\binom{n+1}{i}$的卷积，NTT $O(n\log n)$解决