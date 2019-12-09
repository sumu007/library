---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: mod/sqrt.cpp
* category: mod


[Back to top page](../../index.html)



## Required
* :heavy_check_mark: [polynomial/formalpowerseries.cpp](../polynomial/formalpowerseries.cpp.html)


## Verified
* :heavy_check_mark: [test/yosupo/sqrt_mod.test.cpp](../../verify/test/yosupo/sqrt_mod.test.cpp.html)


## Code
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T>
int jacobi(T a,T mod){
  int s=1;
  if(a<0) a=a%mod+mod;
  while(mod>1){
    a%=mod;
    if(a==0) return 0;
    int r=__builtin_ctz(a);
    if((r&1)&&((mod+2)&4)) s=-s;
    a>>=r;
    if(a&mod&2) s=-s;
    swap(a,mod);
  }
  return s;
}

template<typename T>
vector<T> mod_sqrt(T a,T mod){
  if(mod==2) return {a&1};
  int j=jacobi(a,mod);
  if(j== 0) return {0};
  if(j==-1) return {};

  using ll = long long;
  mt19937 mt;
  ll b,d;
  while(1){
    b=mt()%mod;
    d=(b*b-a)%mod;
    if(d<0) d+=mod;
    if(jacobi<ll>(d,mod)==-1) break;
  }

  ll f0=b,f1=1,g0=1,g1=0;
  for(ll e=(mod+1)>>1;e;e>>=1){
    if(e&1){
      ll tmp=(g0*f0+d*((g1*f1)%mod))%mod;
      g1=(g0*f1+g1*f0)%mod;
      g0=tmp;
    }
    ll tmp=(f0*f0+d*((f1*f1)%mod))%mod;
    f1=(2*f0*f1)%mod;
    f0=tmp;
  }
  if(g0>mod-g0) g0=mod-g0;
  return {T(g0),T(mod-g0)};
}
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif

```
{% endraw %}

[Back to top page](../../index.html)
