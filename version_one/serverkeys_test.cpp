/*************************************************************************
    > File Name: serverkeys_test.cpp
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月07日 星期二 15时27分31秒
 ************************************************************************/

#include<iostream>
#include"parameters.h"
#include"serverkeys.h"
using namespace std;
using namespace NTL;
int main()
{
	parameters p(128,5,8);
	p.PrintParameters();

	serverkeys serverkey(p);
	cout<<serverkey.Get_A_Star()<<endl;
	cout<<"Export A_Star!"<<endl;
	serverkey.ExportAStar();
	cout<<"Export Success!"<<endl;

	return 0;
}
