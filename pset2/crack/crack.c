#define _XOPEN_SOURCE

#include<stdio.h>
#include<cs50.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char* argv[]){
    if(argc!=2){
        //return error
        printf("FATAL ERROR\n");
        return 1;
    }
    else{
        char salt[2],
        password[5],
        alpha[] = {'\0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                          'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

        strncpy(salt, argv[1], 2);

        for (int i = 1;i<52;i++){
            password[0] = alpha[i];
            for (int j = 0;j<52;j++){
                password[1]=alpha[j];
                for (int k = 0;k<52;k++){
                    password[2]=alpha[k];
                    for (int l = 0;l<52;l++){
                        password[3]=alpha[l];

                        if (strcmp(argv[1],crypt(password,salt)) == 0){
                            printf("%s\n",password);
                            return(0);
                        }
                    }
                }
            }
        }
    }

}