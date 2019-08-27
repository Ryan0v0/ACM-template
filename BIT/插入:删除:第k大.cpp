//
// Created by 赵婉如 on 2019-08-27.
// P3369 【模板】普通平衡树(BIT实现)
// 操作:
// 1.插入xx数
// 2.删除xx数(若有多个相同的数，因只删除一个)
// 3.查询xx数的排名(排名定义为比当前数小的数的个数+1+1。若有多个相同的数，因输出最小的排名)
// 4.查询排名为xx的数
// 5.求xx的前驱(前驱定义为小于xx，且最大的数)
// 6.求xx的后继(后继定义为大于xx，且最小的数)
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
const int N = 100005;
int n, opt[N], num[N], lcnt, lsh[N];
struct BIT{
    int c[N];
    int getKth(int k) {
        int ret = 0, sum = 0;
        for (int i = 20; i >= 0; --i)
            if (ret + (1 << i) <= lcnt && sum + c[ret + (1 << i)] < k) {
                sum += c[ret + (1 << i)];
                ret += 1 << i;
            }
        for (int i = 0; i <= 20; ++i)
            if (sum + c[ret + (1 << i)] >= k) {
                ret += 1 << i;
                break;
            }
        return ret;
    }
    void insert(int x) {
        for (;x<=n;x+=x&-x)
            c[x]++;
    }
    void erase(int x) {
        for (;x<=n;x+=x&-x)
            c[x]--;
    }
    LL getsum(int x){
        LL res=0;
        for(;x>0;x-=x&-x)
            res+=c[x];
        return res;
    }
    int rank(int x) { return getsum(x - 1) + 1; }
    int pre(int x) { return getKth(getsum(x - 1)); }
    int suc(int x) { return getKth(getsum(x) + 1); }
} T;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &opt[i], &num[i]);
        if (opt[i] != 4) lsh[++lcnt] = num[i];
    }
    sort(lsh + 1, lsh + lcnt + 1);
    lcnt = unique(lsh + 1, lsh + lcnt + 1) - lsh - 1;
    for (int i = 1; i <= n; ++i) {
        if (opt[i] == 4) {
            printf("%d\n", lsh[T.getKth(num[i])]);
        } else {
            int x = lower_bound(lsh + 1, lsh + lcnt + 1, num[i]) - lsh;
            if (opt[i] == 1) T.insert(x);
            else if (opt[i] == 2) T.erase(x);
            else if (opt[i] == 3) printf("%d\n", T.rank(x));
            else if (opt[i] == 5) printf("%d\n", lsh[T.pre(x)]);
            else if (opt[i] == 6) printf("%d\n", lsh[T.suc(x)]);
        }
    }
    return 0;
}