#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>

int main(){
    //declare variables
    string name=get_string();
    
    //i am using a centinel
    bool b=true;
    
    //validate that the name exits
    if(name!=NULL){
        /*
        ALGORITHM: if b=true the program was in the allocated pointer of the string or in a white space in the last pass
                             if b is not a white space
                                then the program is now in the first letter of the string or in a letter next to a white space(may be many spaces)
                                the program print the letter and make b=false
        */
        for(int i=0;i<strlen(name);i++){
            if(name[i]==' '){
                b=true;
            }
            else{
                if(b==true){
                    printf("%c",toupper(name[i]));
                }
                b=false;
            }
        }
    }
    printf("\n");
    
}