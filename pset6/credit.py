#!/usr/bin/env python3

def digit(number):
    value = 0
    credit_number = number
    count = 0

    while credit_number >0:
        credit_number = credit_number//10
        count += 1

    for i in range(count):
        value1 = number//pow(10, count-i-1)
        number = number - value1*pow(10, count-i-1)
        value += value1;

    return value

def main():
    #declare variables
    count=0

    #validate input

    credit_number= int(input("Number: "))

    while credit_number<=0 :
        credit_number= int(input("Number: "))


    #variable to don`t lose the credit_number`information
    credit_number1=credit_number;

    #count the digits`number
    while credit_number1>0:
        credit_number1=credit_number1//10
        count+=1

    #develop the algorithm
    #first validate that the credit number has a correct digit`number
    if count!=13 and count!=15 and count!=16:
        print("INVALID")
    else:
        credit_number1=credit_number

        value = 0

        for i in range(count):
            number = credit_number1 - (credit_number1//10)*10
            credit_number1 = (credit_number1 - number)/10

            if i%2 != 0:
                value += digit(number*2)
            else:
                value += number

        if value%10 != 0:
            print("INVALID")
        else:
            #VISA card has 13 digits
            credit_number1 = credit_number

            if count==13:
                #obtain the first digit of the credit number
                number=credit_number1//pow(10,count-1)

                #VISA card starts with 4
                if number==4:
                    print("VISA")
                else:
                    print("INVALID")
                    #AMERICAN EXPRESS card has 15 digits
            if count==15:
                #obtain the first digit of the credit number
                number=credit_number1//pow(10,count-1)

                if number==3:
                    #obtain the number without the first digit
                    credit_number1=credit_number1-number*pow(10,count-1)

                    #obtain the second digit of the original credit number
                    number=credit_number1//pow(10,count-2);

                    #AMERICA EXPRESS card starts with 4 or 7
                    if number==4 or number==7:
                        print("AMEX")
                    else:
                        print("INVALID")
                else:
                    print("INVALID")

                #VISA and MASTERCARD card have 16 digits
                if count==16:
                    #obtain the first number of the credit number
                    number=credit_number1//pow(10,count-1);

                    #VISA card starts with 4
                    if number==4:
                        print("VISA")
                        #MASTERCARD card starts with 51-55
                    elif number==5:
                        #obtain the number without the first digit
                        credit_number1=credit_number1-number*pow(10,count-1)

                        #obtain the second digit of the original credit number
                        number=credit_number1//pow(10,count-2);

                        if number==1 or number==2 or number==3 or number==4 or number==5:
                            print("MASTERCARD")
                        else:
                            print("INVALID")
                    else:
                        print("INVALID")


if __name__=="__main__":
    main()