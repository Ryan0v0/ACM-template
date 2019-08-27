//
// Created by 赵婉如 on 2019-08-26.
// 逆康托展开 O(nlogn)
// UVA11525 Permutation (UVa挂了未提交)
//

#include <bits/stdc++.h>
#define F(i, s, t) for(int i=(s);i<=(t);i++)
#define D(i, s, t) for(int i=(s);i>=(t);i--)
#define R(i,x) for(int i=head[(x)];i;i=e[i].next)
#define mec(a, x) memset(a,x,sizeof(a))
using namespace std;
typedef long long LL;
inline LL read()
{
    LL x=0LL,f=1LL;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1LL;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=10LL*x+ch-'0';ch=getchar();}
    return x*f;
}
const int N=2e6+10;
int n;
struct BIT{
    LL t[N];
    void init(){
        mec(t,0);
    }
    void add(int x,LL v){
        for(;x<=n;x+=x&-x)
            t[x]+=v;
    }
    LL getsum(int x){
        LL res=0;
        for(;x>0;x-=x&-x)
            res+=t[x];
        return res;
    }
    int search(LL sum){
        int x=0;
        LL cur=0;
        for(int i=21;i>=0;i--){
            if((x+(1<<i)<=n) && (cur+t[x+(1<<i)]<=sum)){
                x+=(1<<i);
                cur+=t[x];
            }
        }
        return x+1;
    }
}T;
LL s[N],ans[N];
int main()
{
    int tt=read();
    while(tt--) {
        n = read();
        T.init();
        F(i, 1, n) {
            T.add(i, 1);
            s[i] = read();
        }
        F(i, 1, n) {
            ans[i] = T.search(s[i]);
            T.add(ans[i], -1);
        }
        F(i, 1, n) cout << ans[i] << ' ';cout<<endl;
    }
    return 0;
}
/*
4
3
2 1 0
3
1 0 0
4
2 1 1 0
4
1 2 1 0

 */