#include<gmp.h>
#include<time.h>
#include<fstream>
#include<string.h>
#include<iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include<vector>
#include<windows.h>
#include"picosha2.h"
using namespace std;

int main()
{
    ///default the random seed
	gmp_randstate_t grt;
	gmp_randinit_default(grt);
	gmp_randseed_ui(grt, time(NULL));

	///public parameter generator
	cout<<"Start generating parameter and keys...\n";
	char *Param = "parameter.txt";
	FILE *ParamF;
	ParamF = fopen(Param,"wb");
    Sleep(500);
	cout<<"|#    | generate parameters..."<<endl;

	mpz_t q, temp , p; ///p = temp * q +1
	mpz_init(q);
	mpz_init(temp);
	mpz_init(p);


    mpz_t low_bound_q , low_bound_temp ; ///lower bound of q is 2^159 , p is 2^511 so temp is 2^(511-159)
	mpz_init(low_bound_q);
	mpz_init(low_bound_temp );

	mpz_ui_pow_ui (low_bound_q,2,159);
	mpz_ui_pow_ui (low_bound_temp,2,352);

    int prime = 0;
	do{
        mpz_urandomb(q,grt,160);
        mpz_nextprime(q,q);
	}while (mpz_cmp(q,low_bound_q)==0||mpz_cmp(q,low_bound_q)<0);

	do{
        do{
            mpz_urandomb(temp,grt,512);
        }while (mpz_cmp(temp,low_bound_temp)==0||mpz_cmp(temp,low_bound_temp)<0);
        mpz_mul(p,q,temp);
        mpz_add_ui(p,p,1);

        prime = mpz_probab_prime_p(p,10);///check it's prime or not

	}while (prime!=1);
    Sleep(500);

    cout<<"|##   | compute parameters..."<<endl;
	mpz_t g , h ; ///g^q mod p =1 , g= h^((p-1)/q) mod p
	mpz_init(g);
	mpz_init(h);
	do{
        mpz_sub_ui(h,p,2);
        mpz_urandomm(h,grt,h);
	}while (mpz_cmp_ui(h,1)==0||mpz_cmp_ui(h,0)==0);

	///(p-1)/q
	{
        mpz_sub_ui(temp,p,1);
        mpz_cdiv_q(temp,temp,q);
        mpz_powm(g,h,temp,p);

	}

	mpz_out_str(ParamF,16,p);
	fprintf(ParamF,"\n");
	mpz_out_str(ParamF,16,q);
	fprintf(ParamF,"\n");
	mpz_out_str(ParamF,16,g);
	fprintf(ParamF,"\n");
	fclose(ParamF);
	Sleep(500);
	///--------------------------------------------------------------------------------------///
	///private key
	cout<<"|###  | generate private key..."<<endl;
    char *Private = "PrivateKey.txt";
    FILE *PriF;
    PriF = fopen(Private,"wb");

    mpz_t x;
    mpz_init(x);

    mpz_sub_ui(temp,q,1);
    mpz_urandomm(x,grt,temp);
    mpz_add_ui(x,x,1);

    mpz_out_str(PriF,16,x);
    fprintf (PriF,"\n");
    fclose(PriF);
    Sleep(500);

	///public key
	cout<<"|#### | generate public key..."<<endl;
    char *Public = "PublicKey.txt";
    FILE *PuF;
    PuF = fopen(Public,"wb");

    mpz_t y;
    mpz_init(y);

    mpz_invert(temp,g,p); ///temp = g ^ -1
    mpz_powm(y,temp,x,p); /// y = g^-x mod p

    mpz_out_str(PuF,16,y);
    fprintf(PuF,"\n");
    fclose(PuF);
    cout<<"|#####| complete"<<endl;
    system("PAUSE");
    return 0;
}
