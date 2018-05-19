#!/usr/bin/env python3

def main():
    #validate the input
    heigh = int(input("Heigh: "))


    while heigh<0 or heigh>23 :
        heigh = int(input("Heigh: "))

    #print the triangule
    for i in range(heigh):
        aux=""
        #print the white spaces
        for j in range(heigh-i):
            aux+=" "

        #pritn the #
        for k in range(j,heigh+1):
            aux+="#"

        aux = aux[1:]
        print(aux)

if __name__=="__main__":
    main()