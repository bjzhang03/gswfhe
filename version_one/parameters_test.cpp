/*************************************************************************
    > File Name: parameters_test.cpp
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月07日 星期二 10时30分06秒
 ************************************************************************/

#include<iostream>
#include"parameters.h"
using namespace std;
int main()
{
	parameters parameter(128,20,30);
	parameter.PrintParameters();
	return 0;
}
