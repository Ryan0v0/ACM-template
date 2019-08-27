//
// Created by 赵婉如 on 2019-08-26.
// 洛谷P5367 【模板】康托展开 O(nlogn)
// BIT上二分 binary-lifting
// (注意模数可能会有更改)
//

#include <bits/stdc++.h>

#define F(i, s, t) for(int i=(s);i<=(t);i++)
#define D(i, s, t) for(int i=(s);i>=(t);i--)
#define R(i, x) for(int i=head[(x)];i;i=e[i].next)
#define mec(a, x) memset(a,x,sizeof(a))
using namespace std;
typedef long long LL;
#define mod 998244353

inline LL read() {
    LL x = 0LL, f = 1LL;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')f = -1LL;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = 10LL * x + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int n;

struct BIT {
    LL t[N];

    void init() {
        mec(t, 0);
    }

    void add(int x, LL v) {
        for (; x <= n; x += x & -x)
            t[x] += v;
    }

    LL getsum(int x) {
        LL res = 0;
        for (; x > 0; x -= x & -x)
            res += t[x];
        return res;
    }

    int search(LL sum) {
        int x = 0;
        LL cur = 0;
        for (int i = 21; i >= 0; i--) {
            if ((x + (1 << i) <= n) && (cur + t[x + (1 << i)] <= sum)) {
                x += (1 << i);
                cur += t[x];
            }
        }
        return x + 1;
    }
} T;

LL p[N], ans;
LL fac[N];

int main() {
    n = read();
    fac[0] = 1;
    F(i, 1, n) fac[i] = fac[i - 1] * i % mod;
    T.init();
    ans = 0;
    F(i, 1, n) p[i] = read();
    D(i, n, 1) {
        LL tmp = T.getsum(p[i]) % mod;
        //cout<<i<<' '<<tmp<<' '<<n-i<<' '<<fac[n-i]<<endl;
        ans = (ans + fac[n - i] * tmp % mod) % mod;
        T.add(p[i], 1);
    }
    cout << (ans + 1) % mod << endl;
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

5
1 4 5 2 3


 */