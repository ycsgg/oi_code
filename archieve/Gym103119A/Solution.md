粒子初始速度为 $1$ ，有 $n$ 个加速器，每个加速器可以让粒子速度从 $v$ 变为 $a_iv+1$ 

随机排列加速器，求期望最终速度

$v_{末}=\prod\limits_{i=1}^{n}a_i+\prod\limits_{i=2}^{n}a_i+\dots+a_n+1$

$E(v_末)=E(\prod\limits_{i=1}^{n}a_i)+E(\prod\limits_{i=2}^{n}a_i)+\dots+E(a_n)+E(1)$

每一个 $E(\prod\limits_{i=k}^na_i)$ 即 $[x^{n-k}]\prod(a_ix+1)$ 除以选取方案 $\binom{n}{n-k}$

$\prod(a_ix+1)$ 分治+FFT
