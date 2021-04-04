### P4988 重排DL

观察$a_{n+1}=(\sqrt[k]{a_n-n}+2)^k+n+1$

移项得到$a_{n+1}-(n+1)=(\sqrt[k]{a_n-n}+2)^k$

取$k$次方根得到$\sqrt[k]{a_{n+1}-(n+1)}=\sqrt[k]{a_n-n}+2$

发现$\{(a_{n}-n)^k\}$是等差数列且通项为$2n-1$

代入得$(2n-1)^k\equiv b-n \pmod m$

BSGS