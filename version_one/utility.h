/*************************************************************************
    > File Name: utility.h
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年01月10日 星期二 14时30分22秒
 ************************************************************************/

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include<NTL/ZZ.h>
#include<NTL/ZZ_p.h>
#include<NTL/vec_ZZ_p.h>
#include<NTL/mat_ZZ_p.h>
#include<NTL/matrix.h>
#include<NTL/vector.h>
#include"parameters.h"
#include<cmath>

using namespace NTL;
using namespace std;

//generate gauss noise function
ZZ GaussRand(double var,double mea)
{
	static double V1,V2,S;
	static int phase=0;
	double X;

	if(0==phase)
	{
		do
		{
			double U1=(double)rand()/RAND_MAX;
			double U2=(double)rand()/RAND_MAX;

			V1=2*U1-1;
			V2=2*U2-1;

			S=V1*V1+V2*V2;
		}
		while(S>=1||0==S);

		X=V2*sqrt(-2*log(S)/S);
	}
	else
		X=V2*sqrt(-2*log(S)/S);

	phase=1-phase;

	X=X*var+mea;
	//cout<<"X = "<<X<<endl;
	long LIX=(long) floor(X+0.5);

	ZZ result;
	conv(result,LIX);

	return result;
}


//bitcomp vector function
vec_ZZ_p Bitcomp_vec(parameters & parameter,const vec_ZZ_p & data)
{
	//cout<<"Bitcomp start"<<endl;
	vec_ZZ_p result;
	ZZ_p::init(parameter.Get_q());
	//ZZ q=parameter.Get_q();
	//cout<<"q= "<<q<<endl;
	//ZZ_p::init(q);
	const ZZ TWO=ZZ(2);
	for(int i=0;i<data.length();i++)
	{
		ZZ Temp;
		conv(Temp,data[i]);
		for(int j=0;j<parameter.Get_log();j++)
		{
			ZZ res;
			rem(res,Temp,TWO);
			//cout<<res<<" ";
			div(Temp,Temp,TWO);
			ZZ_p myres;
			conv(myres,res);
			result.append(myres);
		}
		//cout<<endl;
	}
	//cout<<"result = "<<result<<endl;
	return result;
}

//inv Bitcomp vector function
vec_ZZ_p Bitdecomp_vec(parameters & parameter,const vec_ZZ_p & data)
{
	vec_ZZ_p result;
	ZZ_p::init(parameter.Get_q());

    ZZ_p TWO;
	conv(TWO,2);
	
	for(int i=0;i<data.length();)
	{
		ZZ_p SUM;
		conv(SUM,0);
		ZZ_p MUL;
		conv(MUL,1);
		for(int j=0;j<parameter.Get_log();j++)
		{
			//cout<<"SUM = "<<SUM<<endl;
			ZZ_p x;
			mul(x,data[i],MUL);
			add(SUM,SUM,x);
			mul(MUL,MUL,TWO);
			i++;
		}
		result.append(SUM);
	}
	//cout<<"result = "<<result<<endl;
	return result;
}


//bitcomp matrix function
mat_ZZ_p Bitcomp_mat(parameters & parameter,const mat_ZZ_p & data)
{
	mat_ZZ_p result;
	ZZ_p::init(parameter.Get_q());

	result.SetDims(data.NumRows(),data.NumCols()*parameter.Get_log());

	const ZZ TWO=ZZ(2);
	for(int i=0;i<data.NumRows();i++)
	{
		int col=0;
		for(int j=0;j<data.NumCols();j++)
		{
			ZZ Temp;
			conv(Temp,data[i][j]);
			for(int k=0;k<parameter.Get_log();k++)
			{
				ZZ res;
				rem(res,Temp,TWO);
				div(Temp,Temp,TWO);

				ZZ_p myres;
				conv(myres,res);
				result[i][col++]=myres;
			}
		}
	}
	return result;
}

//inv bitcomp matrix function
mat_ZZ_p Bitdecomp_mat(parameters & parameter,const mat_ZZ_p &data)
{
	mat_ZZ_p result;
	ZZ_p::init(parameter.Get_q());

	result.SetDims(data.NumRows(),data.NumCols()/parameter.Get_log());

	ZZ_p TWO;
	conv(TWO,2);
	
	for(int i=0;i<data.NumRows();i++)
	{
		int col=0;
		for(int j=0;j<data.NumCols();)
		{

			ZZ_p SUM;
			conv(SUM,0);

			ZZ_p MUL;
			conv(MUL,1);
			for(int k=0;k<parameter.Get_log();k++)
			{
				ZZ_p x;
				mul(x,data[i][j],MUL);
				add(SUM,SUM,x);
				mul(MUL,MUL,TWO);
				j++;
			}
			result[i][col++]=SUM;
		}
	}
	
	//cout<<"result = "<<result<<endl;
	return result;
}

//flatten function
mat_ZZ_p Flatten_mat(parameters & parameter,const mat_ZZ_p & data)
{
	mat_ZZ_p DECOMP=Bitdecomp_mat(parameter,data);
	mat_ZZ_p COMP=Bitcomp_mat(parameter,DECOMP);
	return COMP;
}

//Powof2 function
vec_ZZ_p PowOf2_vec(parameters & parameter,const vec_ZZ_p &data)
{
	vec_ZZ_p result;
	ZZ_p::init(parameter.Get_q());

	ZZ_p TWO;
	conv(TWO,2);
	for(int i=0;i<data.length();i++)
	{
		ZZ_p MUL;
		conv(MUL,1);

		for(int j=0;j<parameter.Get_log();j++)
		{
			result.append(data[i]*MUL);
			MUL=MUL*TWO;
		}
	}
	return result;
}


//generate matrix of one
mat_ZZ_p GenerateONE(parameters & parameter,long length)
{
	mat_ZZ_p result;

	ZZ_p::init(parameter.Get_q());
	result.SetDims(length,length);
	
	ZZ_p Temp;
	conv(Temp,1);
	for(int i=0;i<length;i++)
	{
		result[i][i]=Temp;
	}

	return result;
}

//generate the random matrix
mat_ZZ_p GenerateRandomMat(parameters & parameter,long rows,long cols)
{
	mat_ZZ_p result;
	ZZ_p::init(parameter.Get_q());

	ZZ_p Temp;
	result.SetDims(rows,cols);
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			random(Temp);
			result[i][j]=Temp;
		}
	}
	return result;
}

#endif

