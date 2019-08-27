//
// Created by 赵婉如 on 2019-08-26.
// BIT 区间加,区间求和
//
#include<cstdio>
#include<algorithm>
using namespace std;
using LL=long long;

struct Finwick
{
    int n;
    LL C[100005];

    void init(int x)
    {
        n=x;
    }

    LL sum(int x)
    {
        LL res=0;
        while(x)
            res+=C[x],x-=x&-x;
        return res;
    }

    void add(int x, LL d)
    {
        while(x<=n)
            C[x]+=d,x+=x&-x;
    }
}F[2];

int x,y,k,n,m,o,a;

void Interval_Add(int x, int y, LL t)
{
    --x;
    F[0].add(max(x,1),t);
    if(x)
        F[1].add(x,-t*x);
    F[0].add(y,-t);
    F[1].add(y,t*y);
}

LL Interval_Query(int x, int y)
{
    --x;
    return F[0].sum(y)*y+F[1].sum(y)-F[0].sum(x)*x-F[1].sum(x);
}

int main()
{
    scanf("%d%d",&n,&m);
    F[0].init(n),F[1].init(n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a),Interval_Add(i,i,a);
    while(m--)
    {
        scanf("%d%d%d",&o,&x,&y);
        if(o==1)
        {
            scanf("%d",&k);
            Interval_Add(x,y,k);
        }
        else
            printf("%lld\n",Interval_Query(x,y));
    }
    return 0;
}