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
    ///Verification
    cout<<"Starting Verification..."<<endl;
    FILE *VerF;
    VerF = fopen("Verification.txt","rb");
    FILE *User;
    User = fopen("User.txt","rb");
    FILE *paramF;
    paramF = fopen("parameter.txt","rb");
    FILE *publicF;
    publicF = fopen("PublicKey.txt","rb");

    cout<<"|#    | Fetching files..."<<endl;
    char public_key[500];
    char param_p[500];
    char param_q[500];
    char param_g[500];
    char str_e[500];
    char str_s[500];
    char verify[500];
    char message[500];
    fscanf(User , "%s" , &message);
    fscanf(paramF , "%s" , &param_p);
    fscanf(paramF , "%s" , &param_q);
    fscanf(paramF , "%s" , &param_g);
    fscanf(publicF , "%s" , &public_key);
    fscanf(VerF,"%s",&str_e);
    fscanf(VerF,"%s",&str_s);
    //printf("%s %s\n",str_e,str_s);
    Sleep(500);

    /// p,q,g -> public params ; y -> public key ; ver_e,ver_s,ver_r -> e,s,r for verify ; temp , temp2 -> for temporary value
    cout<<"|##   | Set variables..."<<endl;
    mpz_t p , q , g , y ,ver_e , ver_s , temp , temp2 ,ver_r ;
    mpz_init(p);
    mpz_init(q);
    mpz_init(g);
    mpz_init(y);
    mpz_set_str(p , param_p ,16);
    mpz_set_str(q , param_q ,16);
    mpz_set_str(g , param_g ,16);
    mpz_set_str(y , public_key ,16);
    mpz_init(ver_e);
    mpz_init(ver_s);
    mpz_init(ver_r);
    mpz_init(temp);
    mpz_init(temp2);
    mpz_set_str(ver_e,str_e,16);
    mpz_set_str(ver_s,str_s,16);
    Sleep(500);

    ///(g^s*y^e) mod p = ((g^s)mod p *(y^e)mod p) mod p for mpz don't have power only function
    cout<<"|###  | Compute..."<<endl;
    mpz_powm(temp , g , ver_s ,p);
    mpz_powm(temp2 , y , ver_e ,p);
    mpz_mul(temp , temp ,temp2);
    mpz_mod(ver_r , temp , p);

    mpz_get_str(verify ,16,ver_r); ///copy ver_r to verify(c-string)
    strcat(message , verify); ///hash(M||r)

    string sha(message);
    string hash_hex_str;
    string sigE(str_e);
    picosha2::hash256_hex_string(sha, hash_hex_str);
    Sleep(500);
    //cout<<sigE<<" "<<hash_hex_str<<endl;
    cout<<"|#### | Verifying..."<<endl;
    if (sigE == hash_hex_str)
    {
        cout<<"correct!"<<endl;
    }
    else
    {

        cout<<"error!"<<endl;
    }

    fclose(VerF);
    cout<<"|#####| Complete..."<<endl;
    system("PAUSE");
	return 0;

}
