### P3978 [TJOI2015]概率论

https://www.luogu.com.cn/problem/P3978

设数列$f_i$为点数为$i$的二叉树子叶个数,$g_i$为点数为$i$的二叉树个数

于是答案就是$\dfrac{f_i}{g_i}$

$$\large g_i=\sum_{i=0}^{n-1}g_ig_{n-i-1}$$,也就是两个子树方案乘积，实际上这就是卡特兰数

$f_i=2\sum_{i=0}^{n-1}f_ig_{n-i+1}$，$g_{n-i+1}$是因为卷积的形式好做，并且这个有对称性，这么做是对的

用标准技术可得$G(z)=zG^2(z)+1 \Rightarrow G(z)=\dfrac{1-\sqrt{1-4x}}{2x}$ 

然后$F(z)=2zF(z)G(z)+x \Rightarrow \dfrac{x}{\sqrt{(1-4x)}}$

根据强有力的观察法可以的到$(zG(z))'=\dfrac{1}{\sqrt{1-4z}}=\dfrac{F(z)}{z}$

根据生成函数基本操作$(zG(z))'$是$(n+1)g_n$的生成函数那么把$z$乘过去（右移一位）

就得到了$f_n=ng_n$

带入卡特兰数公式得到$\dfrac{f_i}{g_i}=\dfrac{n(n+1)}{2(2n+1)}$