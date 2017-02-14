/*************************************************************************
    > File Name: serverkeys.h
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月07日 星期二 15时16分02秒
 ************************************************************************/
#ifndef _SERVERKEYS_H_
#define _SERVERKEYS_H_

#include<iostream>
#include<NTL/mat_ZZ_p.h>
#include<NTL/ZZ_p.h>
#include<fstream>
#include<sstream>
#include"parameters.h"
using namespace std;
using namespace NTL;

class serverkeys{
	private:
		mat_ZZ_p A_Star;
	public:
		serverkeys(parameters & parameter)
		{
			ZZ_p::init(parameter.Get_q());

			A_Star.SetDims(parameter.Get_m(),parameter.Get_n()-1);

			for(int i=0;i<parameter.Get_m();i++)
			{
				for(int j=0;j<parameter.Get_n()-1;j++)
				{
					ZZ_p Temp;
					random(Temp);
					A_Star[i][j]=Temp;
				}
			}
		}

		//export A* out to AStar.txt
		void ExportAStar()
		{
			ofstream fout;
			fout.open("AStar.txt",ios_base::out);

			for(int i=0;i<A_Star.NumRows();i++)
			{
				string OutStr="";
				stringstream IO;
				for(int j=0;j<A_Star.NumCols();j++)
				{
					IO.clear();
					IO<<A_Star[i][j];
					string Temp;
					IO>>Temp;
					OutStr=OutStr+Temp+",";
				}
				OutStr.push_back('\n');
				fout<<OutStr;
			}
			fout.close();
		}

		
		//get A* 
		mat_ZZ_p Get_A_Star()
		{
			return A_Star;
		}
};

#endif

