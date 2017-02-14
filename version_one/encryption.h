/*************************************************************************
    > File Name: encryption.h
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月07日 星期二 20时11分29秒
 ************************************************************************/
#ifndef _ENCRYPTION_H_
#define _ENCRYPTION_H_


#include<iostream>
#include"parameters.h"
#include"userkeys.h"
#include"utility.h"
using namespace std;
using namespace NTL;

mat_ZZ_p Encryption(parameters & parameter,userkeys & userkey,long message)
{
	ZZ_p m;
	conv(m,message);
	
	mat_ZZ_p R=GenerateRandomMat(parameter,parameter.Get_n()*parameter.Get_log(),parameter.Get_m());

	//cout<<"R = "<<R<<endl;
	//cout<<"PK = "<<userkey.Get_PK()<<endl;

	mat_ZZ_p RMulPK = R*userkey.Get_PK();

	//cout<<"RMulPK = "<<RMulPK<<endl;

	//cout<<"Bitdecomp = "<<Bitcomp_mat(parameter,RMulPK)<<endl;
	mat_ZZ_p CipherText=Flatten_mat(parameter,message*GenerateONE(parameter,parameter.Get_n()*parameter.Get_log())+Bitcomp_mat(parameter,R*userkey.Get_PK()));

	//cout<<message*GenerateONE(parameter,parameter.Get_n()*parameter.Get_log())<<endl;

	return CipherText;
}


#endif

