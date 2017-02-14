/*************************************************************************
    > File Name: decryption.h
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月08日 星期三 15时22分06秒
 ************************************************************************/
#ifndef _DECRYPTION_H_
#define _DECRYPTION_H_
#include<iostream>
#include<NTL/ZZ.h>
#include<NTL/ZZ_p.h>
#include"parameters.h"
#include"userkeys.h"
#include"utility.h"
using namespace std;
using namespace NTL;

ZZ_p Decryption(parameters & parameter,userkeys &userkey,mat_ZZ_p ciphertext)
{
	vec_ZZ_p V=PowOf2_vec(parameter,userkey.Get_SK());

	//cout<<"SK = "<<userkey.Get_SK()<<endl;
	//cout<<"V = "<<V<<endl;

	vec_ZZ_p result=ciphertext*V;

	//cout<<"result = "<<result<<endl;

	//ZZ m;
	//conv(m,result[parameter.Get_log()-1]);

	ZZ_p m=result[parameter.Get_log()-1];
	cout<<"m = "<<m<<endl;

	ZZ_p MUL;
	conv(MUL,1);
	for(int i=1;i<parameter.Get_log();i++)
	{
		ZZ_p Temp;
		conv(Temp,2);
		MUL=MUL*Temp;
	}
	cout<<"MUL = "<<MUL<<endl;


	return m/MUL;

}

#endif

