#include<stdio.h>
#include<cs50.h>
int main(void){
    
    //declare the variable
    int heigh;
    
    //validate the input
    do{
        printf("Height: ");
        heigh = get_int();
    }while(heigh<0 || heigh>23);
    
    //print the triangule
    for(int i=0;i<heigh;i++){
        int j=0;
        
        //print the white spaces
        for(;j<heigh-i-1;j++){
            printf(" ");
        }
        
        //pritn the #
        for(int k=j;k<heigh+1;k++){
            printf("#");
        }
        printf("\n");
    }
    
}