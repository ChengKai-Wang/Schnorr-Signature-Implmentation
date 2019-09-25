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
	///Signature
	///default the random seed
	gmp_randstate_t grt;
	gmp_randinit_default(grt);
	gmp_randseed_ui(grt, time(NULL));

	FILE *SigF;
    SigF = fopen("Signature.txt","wb");
    FILE *User;
    User = fopen("User.txt","rb");
    FILE *paramF;
    paramF = fopen("parameter.txt","rb");
    FILE *privF;
    privF = fopen("PrivateKey.txt","rb");

	char priv_key[500];
    char param_p[500];
    char param_q[500];
    char param_g[500];
	char message[500];
	char str_r[500];
	fscanf(User , "%s" , &message);
    fscanf(paramF , "%s" , &param_p);
    fscanf(paramF , "%s" , &param_q);
    fscanf(paramF , "%s" , &param_g);
    fscanf(privF , "%s" , &priv_key);

	mpz_t p , q , g , x , e , k , r , s , temp ;
	mpz_init(p);
    mpz_init(q);
    mpz_init(g);
    mpz_init(x);
    mpz_set_str(p , param_p ,16);
    mpz_set_str(q , param_q ,16);
    mpz_set_str(g , param_g ,16);
    mpz_set_str(x , priv_key ,16);
    mpz_init(k);
    mpz_init(r);
    mpz_init(s);
    mpz_init(e);
    mpz_init(temp);

	mpz_urandomb(k,grt,159);
    mpz_add_ui(k,k,1);
    mpz_powm(r,g,k,p);

	///hash(M||r)
	mpz_get_str(str_r,16,r);
	strcat(message , str_r);
	//cout<<message<<endl;
	string hash_hex_str;
    string sha(message);
    picosha2::hash256_hex_string(sha, hash_hex_str);
    const char *c_hash  = hash_hex_str.c_str();
	mpz_set_str(e , c_hash ,16);
	mpz_out_str(SigF,16,e);
    fprintf(SigF,"\n");

	mpz_mul(temp , x , e); ///temp = e*x
    mpz_add(temp , k , temp); ///temp = k + e*x
    mpz_mod(s,temp,q); ///s=(k+xe) mod q
	mpz_out_str(SigF,16,s);
	fprintf(SigF,"\n");
    fclose(SigF);
	system("PAUSE");
	return 0;

}
