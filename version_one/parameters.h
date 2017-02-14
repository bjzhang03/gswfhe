/*************************************************************************
    > File Name: parameters.h
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年01月10日 星期二 16时40分28秒
 ************************************************************************/

#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_


#include<iostream>
#include<NTL/ZZ.h>

using namespace std;
using namespace NTL;

class parameters{
	private:
		ZZ q;
		int log;
		long m;
		long n;


	public:
		parameters()
		{
			q=ZZ(127);
			log=8;
			n=30;
			m=50;
		}

		parameters(int length,long im,long in)
		{
			q=GenPrime_ZZ(length);
			log=length;
			m=im;
			n=in;
		}

		parameters(ZZ iq,int length,long im,long in)
		{
			q=iq;
			log=length;
			m=im;
			n=in;
		}

		ZZ Get_q()
		{
			return q;
		}

		int Get_log()
		{
			return log;
		}

		long Get_n()
		{
			return n;
		}

		long Get_m()
		{
			return m;
		}

		void PrintParameters()
		{
			cout<<"[q = "<<q<<",log = "<<log<<",m = "<<m<<",n = "<<n << "]"<<endl;
		}
};



#endif

