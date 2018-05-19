#!/usr/bin/env python3

def main():

    #validate input
    money= float(input("O hai! How much change is owed?\n"))

    while money<0:
        money= float(input("O hai! How much change is owed?\n"))

    #declare variable and work with an integer to do more easy the homework
    count=0;
    money1=(int)(money*100)

    #develop the algorithm inspirate in the euclide`s division algorithm
    """
    ALGORITHM: input: money, a,b,c and d are non negative integers including 0
                if money>0.01
                    money = a*0.25 + b*0.1 + c*0.5 + d*0.01
                    return a+b+c+d;
    """
    while money1!=0 :
        #money1 is the number of cents of money
        if money1>=25:
            aux=money1%25

            count=count+(money1-aux)//25
            money1=aux
        elif money1>=10:
            aux=money1%10

            count=count+(money1-aux)//10
            money1=aux
        elif money1>=5:
            aux=money1%5

            count=count+(money1-aux)//5
            money1=aux
        elif money1>=1:
            aux=money1%1

            count=count+(money1-aux)//1
            money1=aux
        else:
            money1=0

    print(count);

if __name__=="__main__":
    main()

