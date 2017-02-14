/*************************************************************************
    > File Name: example.cpp
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月08日 星期三 14时23分07秒
 ************************************************************************/

#include<iostream>
#include<NTL/ZZ_p.h>
#include"parameters.h"
#include"userkeys.h"
#include"encryption.h"
#include"decryption.h"
using namespace std;
using namespace NTL;

int main()
{
	parameters p(8,5,6);
	p.PrintParameters();

	userkeys userkey(p,5,10);

	long message = 0;
	cout<<"message = "<<message<<endl;
	mat_ZZ_p ciphertext=Encryption(p,userkey,message);

	//cout<<"ciphertext = "<<ciphertext<<endl;

	ZZ_p plaintext=Decryption(p,userkey,ciphertext);

	cout<<"plaintext = "<<plaintext<<endl;

	return 0;
}
