/*************************************************************************
    > File Name: userkeys.h
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月07日 星期二 15时15分44秒
 ************************************************************************/
#ifndef _USERKEYS_H_
#define _USERKEYS_H_

#include<iostream>
#include<fstream>
#include<sstream>
#include"parameters.h"
#include"serverkeys.h"
#include"utility.h"

using namespace std;
using namespace NTL;

class userkeys{
	private:
		mat_ZZ_p PK;
		vec_ZZ_p SK;
		vec_ZZ_p ENoise;
	public:
		userkeys(parameters & parameter,double var,double mea)
		{
			ZZ_p::init(parameter.Get_q());

			//generate PK* data
			mat_ZZ_p PK_Star;
			vec_ZZ_p SK_Star;

			PK_Star.SetDims(parameter.Get_m(),parameter.Get_n()-1);
			for(int i=0;i<parameter.Get_m();i++)
			{
				for(int j=0;j<parameter.Get_n()-1;j++)
				{
					ZZ_p Temp;
					random(Temp);
					PK_Star[i][j]=Temp;
				}
			}

			//generate SK* data
			for(int i=0;i<parameter.Get_n()-1;i++)
			{
				ZZ_p Temp;
				random(Temp);
				SK_Star.append(Temp);
			}

			//generate ENoise data
			for(int i=0;i<parameter.Get_m();i++)
			{
				ZZ Temp=GaussRand(var,mea);
				ZZ_p res;
				conv(res,Temp);
				ENoise.append(res);
			}

			//generate vector b
			vec_ZZ_p b=PK_Star*SK_Star+ENoise;
			//cout<<"b = "<<b<<endl;
			//cout<<"PK_Star = "<<PK_Star<<endl;
			//cout<<"SK_Star = "<<SK_Star<<endl;
			//cout<<"ENoise = "<<ENoise<<endl;


			//generate PK data
			PK.SetDims(parameter.Get_m(),parameter.Get_n());
			for(int i=0;i<parameter.Get_m();i++)
			{
				PK[i][0]=b[i];
			}
			for(int i=0;i<parameter.Get_m();i++)
			{
				for(int j=0;j<parameter.Get_n()-1;j++)
				{
					PK[i][j+1]=PK_Star[i][j];
				}
			}

			//cout<<"PK = "<<PK<<endl;
				
			ZZ_p ONE;
			conv(ONE,1);
			SK.append(ONE);
			for(int i=0;i<parameter.Get_n()-1;i++)
			{
				ZZ_p Temp;
				sub(Temp,ZZ_p::zero(),SK_Star[i]);
				SK.append(Temp);
			}

			//cout<<"SK = "<<SK<<endl;
		}

		//print the information of keys
		void PrintKeys()
		{
			cout<<"PK = "<<PK<<endl<<"SK = "<<SK<<endl<<"ENoise = "<<ENoise<<endl;
		}


		//get keys
		mat_ZZ_p Get_PK()
		{
			return PK;
		}
		vec_ZZ_p Get_SK()
		{
			return SK;
		}
		vec_ZZ_p Get_ENoise()
		{
			return ENoise;
		}

		//Export PK out to PK.txt
		void ExportPK()
		{
			ofstream fout;
			fout.open("PK.txt",ios_base::out);

			for(int i=0;i<PK.NumRows();i++)
			{
				string OutStr="";
				stringstream IO;
				for(int j=0;j<PK.NumCols();j++)
				{
					IO.clear();
					IO<<PK[i][j];

					string Temp;
					IO>>Temp;
					OutStr=OutStr+Temp+",";
				}
				OutStr.push_back('\n');
				fout<<OutStr;
			}
			fout.close();
		}

		//Export SK out to SK.txt
		void ExportSK()
		{
			ofstream fout;
			fout.open("SK.txt",ios_base::out);

			string OutStr="";
			stringstream IO;
			for(int i=0;i<SK.length();i++)
			{
				IO.clear();
				IO<<SK[i];
				string Temp;
				IO>>Temp;
				OutStr=OutStr+Temp+",";
			}
			fout<<OutStr;
			fout.close();
		}

		//Export ENoise out to ENoise.txt
		void ExportENoise()
		{
			ofstream fout;
			fout.open("ENoise.txt",ios_base::out);
			
			string OutStr="";
			stringstream IO;
			for(int i=0;i<ENoise.length();i++)
			{
				IO.clear();
				IO<<ENoise[i];
				string Temp;
				IO>>Temp;
				OutStr=OutStr+Temp+",";
			}
			fout<<OutStr;
			fout.close();
		}

		//Export All Data
		void ExportAllInformation()
		{
			ExportPK();
			ExportSK();
			ExportENoise();
		}
};

#endif

