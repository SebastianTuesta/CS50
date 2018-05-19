#include<stdio.h>
#include<cs50.h>
int main(void){
    
    //declare variables, i am using a double variable because has more bits that a float, so is more precise to represent decimal number
    //float doesn`t work with 4.2 but double yes
    
    double money;
    int money1;
    
    //validate input
    printf("O hai! ");
    do{
        printf("How much change is owed?\n");
        money= get_double();
    }while(money<0);
    
    //declare variable and work with an integer to do more easy the homework
    int count=0;
    money1=(int)(money*100);
    
    //develop the algorithm inspirate in the euclide`s division algorithm
    /*
    ALGORITHM: input: money, a,b,c and d are non negative integers including 0
                if money>0.01
                    money = a*0.25 + b*0.1 + c*0.5 + d*0.01
                    return a+b+c+d;
    */            
    while(money1!=0){
        //money1 is the number of cents of money
        if(money1>=25){
            
            int aux=money1%25;
            
            count=count+(money1-aux)/25;
            money1=aux;
        }
        else if(money1>=10){
            int aux=money1%10;
            
            count=count+(money1-aux)/10;
            money1=aux;
        }
        else if(money1>=5){
            int aux=money1%5;
            
            count=count+(money1-aux)/5;
            money1=aux;
        }
        else if(money1>=1){
            int aux=money1%1;
            
            count=count+(money1-aux)/1;
            money1=aux;
        }
        else{
            money1=0;
        }
    }
    
    printf("%i\n",count);

}