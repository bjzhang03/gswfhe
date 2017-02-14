/*************************************************************************
    > File Name: userkeys_test.cpp
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月07日 星期二 16时08分08秒
 ************************************************************************/

#include<iostream>
#include"userkeys.h"
#include"parameters.h"
using namespace std;
using namespace NTL;
int main()
{

	parameters p(32,6,8);
	p.PrintParameters();

	userkeys userkey(p,5,20);
	userkey.PrintKeys();
	cout<<"ExportData!"<<endl;
	userkey.ExportAllInformation();
	cout<<"Export Data Success!"<<endl;
	return 0;
}
