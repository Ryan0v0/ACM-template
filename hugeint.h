#pragma once
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std; 

const char chg[37]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int id[128]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

//注意最低位是从0开始计算的！

template<class LL, int max_size, int L, int inc> struct hugeint
{
	LL d[max_size],l,base;
	bool sig;
	char buf[20];
	int len;
	
	inline bool isdigit(char c)
	{
		return id[c]>=0&&id[c]<inc;
	}
	
	void write(LL x, bool fill, FILE *out)
	{
		while(x>0)
			buf[len++]=chg[x%inc],x/=inc;
		if(fill)
			while(len<L)
				buf[len++]='0';
		while(len)
			fputc(buf[--len],out);
	}
	
	inline bool equals_zero() const
	{
		return l==0;
	}
	
	inline bool odd() const
	{
		return l>0&&(d[0]&1);
	}
	
	void operator = (const char *p)
	{
		const char *q=p;
		int f=0;
		sig=false;
		if(p[0]=='-')
		{
			++q;
			sig=true;
		}
		while(isdigit(q[f]))
			++f;
		l=f/L;
		for(int i=0,tmp;i<l;i++)
		{
			d[i]=0;
			for(int j=L;j>=1;j--)
				d[i]=d[i]*inc+id[q[f-i*L-j]];
		}
		if(f%L)
		{
			d[l]=0;
			for(int i=L*l;i<f;i++)
				d[l]=d[l]*inc+id[q[i-L*l]];
			l++;
		}
		while(l>0&&d[l-1]==0)
			--l;
	}
	
	void operator = (const hugeint &t)
	{
		l=t.l,sig=t.sig;
		for(int i=0;i<l;i++)
			d[i]=t.d[i];
	}
	
	void operator = (char *p)
	{
		const char *x=p;
		*this=x;
	}
	
	template<class T1>
	void operator = (T1 x)
	{
		char str[max_size*L];
		int t=0;
		T1 y=x;
		while(y!=0)
			y/=inc,++t;
		str[t]='\0';
		if(x<0)
			str[0]='-',t++,x=-x;
		while(x!=0)
		{
			str[--t]=chg[x%inc];
			x/=inc;
		}
		*this=str; 
	}
	
	template<class T1>
	hugeint(const T1 &x)
	{
		*this=x;
		base=1;
		len=0;
		for(int i=0;i<L;i++)
			base*=inc;
	}
	
	hugeint()
	{
		l=0;
		sig=false;
		base=1;
		len=0;
		for(int i=0;i<L;i++)
			base*=inc;
	}
	
	bool operator == (const hugeint &t) const
	{
		if((sig^t.sig)&&(l>0||t.l>0)||l!=t.l)
			return false;
		for(int i=0;i<l;i++)
			if(d[i]!=t.d[i])
				return false;
		return true;
	}
	
	bool operator < (const hugeint &t) const
	{
		if(sig&&!t.sig)
			return true;
		if(l<t.l)
			return sig^true;
		if(l>t.l)
			return sig^false;
		int i;
		for(i=l-1;i>=0&&t.d[i]==d[i];i--);
		if(i<0)
			return false;
		if(d[i]<t.d[i])
			return sig^true;
		if(d[i]>t.d[i])
			return sig^false;
	}
	
	bool operator > (const hugeint &t) const
	{
		return t<*this;
	}
	
	bool operator <= (const hugeint &t) const
	{
		return *this<t||*this==t;
	}
	
	bool operator >= (const hugeint &t) const
	{
		return t<=*this;
	}
	
	hugeint operator - () const
	{
		hugeint res=*this;
		res.sig^=true;
		return res;
	}
	
	hugeint abs() const
	{
		hugeint res=*this;
		res.sig=false;
		return res;
	}
	
	template<class T1>
	hugeint operator << (T1 k) const
	{
		hugeint res=*this;
		res.l+=k;
		for(int i=res.l-1;i>=k;i--)
			res.d[i]=res.d[i-k];
		for(int i=k-1;i>=0;i--)
			res.d[i]=0;
		return res;
	}
	
	template<class T1>
	hugeint operator >> (T1 k) const
	{
		hugeint res=*this;
		res.l=max(res.l-k,(LL)0);
		for(int i=0;i<res.l;i++)
			res.d[i]=res.d[i+k];
		return res;
	}
	
	hugeint operator + (const hugeint &t) const
	{
		hugeint res;
		res.sig=sig;
		res.l=max(l,t.l);
		LL c=0,k;
		if(t.sig^sig)
		{
			k=this->abs()<t.abs()?1:-1;
			res.sig^=k==1;
			for(int i=0;i<res.l;i++)
			{
				res.d[i]=((i<t.l?t.d[i]:0)-(i<l?d[i]:0))*k-c;
				c=res.d[i]<0;
				res.d[i]+=c*base;
			}
			while(res.l>0&&res.d[res.l-1]==0)
				--res.l;
			return res;
		}
		for(int i=0;i<res.l;i++)
		{
			res.d[i]=(i<l?d[i]:0)+(i<t.l?t.d[i]:0)+c;
			c=res.d[i]>=base;
			res.d[i]-=c*base;
		}
		if(c)
			res.d[res.l++]=c;
		return res;
	}
	
	hugeint operator - (const hugeint &t) const
	{
		return *this+(-t);
	}
	
	hugeint operator * (const hugeint &t) const
	{			
		hugeint res;
		if(t.equals_zero()||this->equals_zero())
		{
			res.l=0;
			return res;
		}
		res.sig=sig^t.sig;
		res.l=l+t.l-1;
		LL c;
		for(int i=0;i<=res.l;i++)
			res.d[i]=0;
		for(int i=0;i<l;i++)
		{
			c=0;
			for(int j=0;j<t.l;j++)
			{
				res.d[i+j]=res.d[i+j]+d[i]*t.d[j]+c;
				c=res.d[i+j]/base;
				res.d[i+j]%=base;
			}
			if(c)
				res.d[i+t.l]=c;
		}
		if(res.d[res.l])
			++res.l;
		while(res.l>0&&res.d[res.l-1]==0)
			--res.l;
		return res;
	}
	
	friend hugeint positive_div(const hugeint g, const hugeint &t, hugeint &r)
	{
		hugeint res;
		res.sig=false;
		if(t.equals_zero()||g<t)
			res.l=0,r=g;
		else
		{
			res.l=g.l-t.l+1;
			LL le,re,me;
			r=g>>(res.l-1);
			for(int i=res.l-1;i>=0;i--)
			{
				le=((r.l>=t.l?r.d[t.l-1]:0)+(r.l>t.l?r.d[t.l]*g.base:0))/(t.d[t.l-1]+1);
				re=((r.l>=t.l?r.d[t.l-1]:0)+(r.l>t.l?r.d[t.l]*g.base:0)+1)/t.d[t.l-1];
				while(le<re)
				{
					me=re+le+1>>1;
					if(r<t*me)
						re=me-1;
					else
						le=me;
				}
				res.d[i]=le;
				r=r-t*le;
				if(i)
					r=(r<<1)+g.d[i-1];
			}
			if(res.d[res.l-1]==0)
				--res.l;
		}
		return res;
	}
	
	hugeint operator / (const hugeint &t) const
	{
		hugeint res,c;
		moddiv(*this,t,res,c);
		return res;
	}
	
	hugeint operator % (const hugeint &x) const
	{
		hugeint c,res;
		moddiv(*this,x,res,c);
		return c;
	}
	
	friend void moddiv(const hugeint x, const hugeint y, hugeint &res, hugeint &c)
	{
		res=positive_div(x.abs(),y.abs(),c);
		if(x.sig^y.sig)
		{
			res.sig=!res.sig;
			if(!c.equals_zero())
			{
				res=res-1;
				if(y.sig)
					c=y+c;
				else
					c=y-c;
			}
		}
		else if(x.sig&&y.sig)
			c.sig=true;
	}
	
	friend hugeint gcd(hugeint a, hugeint b)
	{
		hugeint c;
		while(!(a%b).equals_zero())
		{
			c=a%b;
			a=b;
			b=c;
		}
		return b;
	}
	
	friend hugeint quick_power(hugeint p, hugeint q, hugeint mo)
	{
		hugeint res=1,base=p;
		while(!q.equals_zero())
		{
			if(q.odd())
				res=res*base%mo;
			base=base*base%mo;
			q=q/2;
		}
		return res;
	}
	
	friend hugeint inv(hugeint x, hugeint y)
	{
		hugeint q,u=0,v=1,lu=1,lv=0,tu,tv,tmp,yy=y;
		while(!(x%y).equals_zero())
		{
			q=x/y;
			tu=u,tv=v;
			u=lu-q*u;
			v=lv-q*v;
			lu=tu,lv=tv;
			tmp=y,y=x%y,x=tmp;
		}
		return u<0?u+yy:u;
	}

	
	void print(FILE *out)
	{
		if(l==0)
		{
			fputs("0",out);
			return ;
		}
		if(sig)
			fputc('-',out);
		write(d[l-1],false,out);
		for(int i=l-2;i>=0;i--)
			write(d[i],true,out);
		fputs("\n",out);
	}
};
