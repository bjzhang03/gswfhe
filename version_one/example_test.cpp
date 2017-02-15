/*************************************************************************
    > File Name: example.cpp
    > Author: bjzhang03
    > Mail: bjzhang1991@gmail.com
    > Created Time: 2017年02月08日 星期三 14时23分07秒
 ************************************************************************/

#include<iostream>
#include<time.h>
#include<vector>
#include<fstream>
#include<sstream>
#include<NTL/ZZ_p.h>
#include"parameters.h"
#include"userkeys.h"
#include"encryption.h"
#include"decryption.h"
using namespace std;
using namespace NTL;

int main()
{

	vector<int> keyslength={64,72,80,88,96,104,112,120,128};

	ofstream fout;
	fout.open("RESULT.txt",ofstream::out);
	fout.close();

	for(auto it=keyslength.begin();it!=keyslength.end();it++)
	{
		parameters p(*it,100,50);
		p.PrintParameters();

		userkeys userkey(p,3.2,0);
		userkey.ExportPK();
		userkey.ExportSK();
		userkey.ExportENoise();

		const int loop =100;
		vector<double> Encryption_Times;
		vector<double> Decryption_Times;

		long ciphertextlength=0;

		for(int i=0;i<loop;i++)
		{
			long message = 0;
			if(0==rand()%2)
				message = 1;
			cout<<endl<<"i = "<<i<<",message = "<<message<<endl;

			clock_t start_time_En=clock();
			mat_ZZ_p ciphertext=Encryption(p,userkey,message);
			clock_t end_time_En=clock();
			double encryption_time = static_cast<double>(end_time_En-start_time_En)/CLOCKS_PER_SEC*1000;
			cout<<"Encryption Time is = "<<encryption_time<<"ms;"<<endl;

			Encryption_Times.push_back(encryption_time);

			ciphertextlength=ciphertext.NumRows()*ciphertext.NumCols();
			cout<<"Size of ciphertext = "<<ciphertext.NumRows()*ciphertext.NumCols()<<endl;

			//cout<<"ciphertext = "<<ciphertext<<endl;

			clock_t start_time_De=clock();
			ZZ plaintext=Decryption(p,userkey,ciphertext);
			clock_t end_time_De=clock();
			double decryption_time = static_cast<double>(end_time_De-start_time_De)/CLOCKS_PER_SEC*1000;
			cout<<"Decryption Time is = "<<decryption_time<<"ms;"<<endl;

			Decryption_Times.push_back(decryption_time);

			cout<<"plaintext = "<<plaintext<<endl;
		}
		fout.open("RESULT.txt",ofstream::app);
		fout<<"keys = "<<*it<<endl;
		fout<<"Encryption Times :"<<endl;

		double sum = 0;

		for(auto itemp=Encryption_Times.begin();itemp!=Encryption_Times.end();itemp++)
		{
			fout<<*itemp<<",";
			sum+=*itemp;
		}
		fout<<endl;
		fout<<"Mean of Encryption = "<<sum/Encryption_Times.size()<<endl;

		fout<<"Decryption Times :"<<endl;
		sum=0;
		for(auto itemp=Decryption_Times.begin();itemp!=Decryption_Times.end();itemp++)
		{
			fout<<*itemp<<",";
			sum+=*itemp;
		}
		fout<<endl;
		fout<<"Mean of Decryption = "<<sum/Decryption_Times.size()<<endl;
		fout<<"Size of ciphertext is =  "<<ciphertextlength<<endl<<endl;
		fout.close();
	}

	return 0;
}
