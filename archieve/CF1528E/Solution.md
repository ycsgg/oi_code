###　CF1528E Mashtali and Hagh Trees

考虑这三个条件都限制了个啥，第二个条件限制了除了“根”节点都只能有两个儿子

第三个条件叶/根向树肯定是满足的，还有另一种情况是

[![Rxi678.png](https://z3.ax1x.com/2021/07/09/Rxi678.png)](https://imgtu.com/i/Rxi678)

思考一下能够发现没有其他的情况了

因为最后的情况是一个叶向树和一个根向树拼起来的，而且这两种树是同构的

所以暂时只考虑前两个条件，记 $f_{i}$ 为有根且根节点度数小于等于 $2$   同向边（因为根/叶向同构）最大链长为 $i$ 的方案

则 $f_i=f_{i-1}+f_{i-1}(\sum\limits_{j=0}^{i-2}f_j)+\binom{f_{i-1}}{2}+f_{i-1}$

根度数为 $1$ 就是 $f_{i-1}$

度数为 $2$ 需要分别讨论一下，如果深度不同则一定有一个 $i-1$ 深度的，另一个随便放

深度相同就是选俩，或者是一样的

那么只考虑有根的情况的答案是 

$2(f_{n}+f_{n-1}\binom{1+\sum\limits_{j=0}^{n-2}f_j}{2}+(\sum\limits_{j=0}^{n-2}f_j)\binom{f_{n-1}+1}{2}+\binom{f_{n-2}+2}{3})-1$

$f_{n}$ 是根度数小于等于二的情况，剩下的是三的分类讨论，即 $1/2/3$ 个子树深度为 $n-1$ 的情况

最后图上的比较特殊的情况可以考虑断开根向书和叶向树，考虑根向树不能为链，叶向树度数必须为 $2$ 得到

$\sum(f_i-1)(f_{n-i-1}-f_{n-i-2})$

差分是为了得到度数恰好为 $2$ 的数量

＃计数