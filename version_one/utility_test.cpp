/*************************************************************************
    > File Name: utility_test.cpp
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年01月10日 星期二 14时30分44秒
 ************************************************************************/

#include<iostream>
#include<NTL/ZZ_p.h>
#include"parameters.h"
#include"utility.h"
#include<NTL/mat_ZZ_p.h>

using namespace std;
using namespace NTL;

int main()
{
//	cout<<GeneratePrimeOfLength(5);

	parameters p(16,3,5);
	p.PrintParameters();


	ZZ_p::init(p.Get_q());
	vec_ZZ_p Test;
	ZZ_p ZZPData;


	/*
	//Test gauss noise performance
	double var=13,mea=0;
	for(int i=0;i<100;i++)
	{
		cout<<GaussRand(var,mea)<<" ";
	}
	cout<<endl;
		//cout<<GaussRand(var,mea)<<endl;
		//
	*/



	/*
	cout<<endl<<endl<<"Vec Test Start!"<<endl;
	//ZZ TempData=ZZ(5);
	//conv(ZZPData,TempData);

	//Test.SetLength(10,ZZPData);
	Test.SetLength(p.Get_n());

	for(int i=0;i<p.Get_n();i++)
	{
		random(ZZPData);
		Test[i]=ZZPData;
	}

	cout<<"Test = "<<Test<<endl;
	vec_ZZ_p result = Bitcomp_vec(p,Test);
	cout<<"Bitcomp_vec result = "<<result<<endl;
	vec_ZZ_p deresult=Bitdecomp_vec(p,result);
	cout<<"Bitdecomp_vec deresult = "<<deresult<<endl;

	
	vec_ZZ_p powoftwo=PowOf2_vec(p,Test);
	cout<<"PowOf2_vec powoftwo = "<<powoftwo<<endl;

	cout<<"ONE = "<<GenerateONE(p,20)<<endl;
	cout<<"GenerateRandomMat = "<<GenerateRandomMat(p,10,10)<<endl;


	ZZ TT1;
	conv(TT1,1);
	ZZ TT2;
	conv(TT2,4);
	ZZ rr;
	div(rr,TT1,TT2);
	cout<<"rr = "<<rr<<endl;

	*/

	cout<<endl<<endl<<"Mat Test Start!"<<endl;
	mat_ZZ_p TestMat;
	TestMat.SetDims(p.Get_n(),p.Get_m());
	for(int i=0;i<p.Get_n();i++)
	{
		for(int j=0;j<p.Get_m();j++)
		{
			random(ZZPData);
			TestMat[i][j]=ZZPData;
		}
	}
	cout<<TestMat<<endl;


	mat_ZZ_p TestMatresult=Bitcomp_mat(p,TestMat);

	cout<<"Bitcomp_mat TestMatresult = "<<TestMatresult<<endl;

	mat_ZZ_p TestDeresult=Bitdecomp_mat(p,TestMatresult);
	cout<<"Bitdecomp_mat TestDeresult = "<<TestDeresult<<endl;
	

	cout<<"Flatten_mat = "<<Flatten_mat(p,TestMatresult)<<endl;

	mat_ZZ_p RData=GenerateRandomMat(p,10,6);
	cout<<"RData = "<<RData<<endl;

	

	return 0;
}

