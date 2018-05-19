#include<stdio.h>
#include<cs50.h>
#include<math.h>

int digit(int number){
    int value = 0, value1;
    int credit_number = number;
    int count = 0;
    while(credit_number > 0){
        credit_number = credit_number/10;
        count++;
    }

    for(int i=0; i<count; i++){
        value1 = number/(long long)pow(10, count-i-1);
        number = number - (long long)(value1*pow(10, count-i-1));
        value += value1;
    }
    return value;
}


int main(void){

    //declare variables
    long long credit_number;
    int count = 0;

    //validate input
    do{
        printf("Number: ");
        credit_number = get_long_long();
    }while(credit_number <= 0);

    //variable to don`t lose the credit_number`information
    long long credit_number1 = credit_number;

    //count the digits`number
    while(credit_number1 > 0){
        credit_number1 = credit_number1/10;
        count++;
    }

    //develop the algorithm
    //first validate that the credit number has a correct digit`number
    if(count!=13  && count!=15 && count!=16){
        printf("INVALID\n");
    }
    else{
        long number;

        credit_number1 = credit_number;

        int value = 0;

        for(int i=0; i<count; i++){
            //number : cipher of left to right
            /*
            number = credit_number1/(long long)pow(10, count-i-1);
            credit_number1 = credit_number1 - (long long)(number*pow(10, count-i-1));
            */

            //number: cipher of right to left
            number = credit_number1 - (credit_number1/10)*10;
            credit_number1 = (credit_number1 - number)/10;

            if(i%2 != 0){
                value += digit((int) (number*2));

            }
            else{
                value += number;
            }
        }

        if(value%10 != 0){
            printf("INVALID\n");
        }
        else{

            credit_number1 = credit_number;
            switch(count){
                //VISA card has 13 digits
                case 13:
                        //obtain the first digit of the credit number
                        number=credit_number1/(long long)pow(10,count-1);

                        //VISA card starts with 4
                        if(number == 4){
                            printf("VISA\n");
                        }
                        else{
                            printf("INVALID\n");
                        }
                        break;

                //AMERICAN EXPRESS card has 15 digits
                case  15:
                        //obtain the first digit of the credit number
                        number = credit_number1/(long long)pow(10, count-1);
                        if(number == 3){

                            //obtain the number without the first digit
                            credit_number1 = credit_number1 - (long long)(number*pow(10, count-1));

                            //obtain the second digit of the original credit number
                            number = credit_number1/(long long)pow(10, count-2);

                            //AMERICA EXPRESS card starts with 4 or 7
                            if(number==4 || number==7){
                                printf("AMEX\n");
                            }
                            else{
                                printf("INVALID\n");
                            }
                        }
                        else{
                            printf("INVALID\n");
                        }
                        break;

                //VISA and MASTERCARD card have 16 digits
                case 16:
                        //obtain the first number of the credit number
                        number=credit_number1/(long long)pow(10, count-1);

                        //VISA card starts with 4
                        if (number == 4){
                                printf("VISA\n");
                        }
                        //MASTERCARD card starts with 51-55
                        else if(number == 5){

                            //obtain the number without the first digit
                            credit_number1 = credit_number1 - (long long)(number*pow(10, count-1));

                            //obtain the second digit of the original credit number
                            number = credit_number1/(long long)pow(10, count-2);

                            if(number==1 || number==2 || number==3 || number==4 || number==5){
                                printf("MASTERCARD\n");
                            }
                            else{
                                printf("INVALID\n");
                            }
                        }
                        else{
                            printf("INVALID\n");
                        }
                        break;
            }


        }

    }

}

