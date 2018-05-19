#!/usr/bin/env python3
import sys

def main():
    if len(sys.argv)!=2:
        print("Usage: ./caesar k");
        return 1;
    else:

        plaintext=str(input("plaintext: "))

        n=int(sys.argv[1])

        #analize plaintext
        ciphertext(plaintext,n)
        return 0


def ciphertext(plaintext,shift):
    aux="ciphertext: "

    #analize every letter of the input function
    n=len(plaintext)
    for i in range(n):
        #caesar_cipher implements the caesar cripthography algorithm
        aux+=str(chr(caesar_cipher(ord(plaintext[i]),shift)))
    print(aux)

def caesar_cipher(letter,shift):
    #work with lower letters and retun the letter avance shift letters in the alphabet
    if 97<=letter and letter<=122:
        return 97+(letter-97+ shift)%26
    #work with upper letters and retun the letter avance shift letters in the alphabet
    elif 65<=letter and letter<=90:
        return 65+(letter-65+shift)%26
    #if the variable letter is not a lower or upper letter of the alphabet,the function don`t realize the caesar cripthography algorithm
    else:
        return letter

if __name__=="__main__":
    main()