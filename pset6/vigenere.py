#!/usr/bin/env python3

import sys

def main():
    if len(sys.argv)!=2:
        print("FAIL, NEXT AGAIN")
        return 1
    else:
        #only accept argv[1] if all of its characters are letter
        if validate(sys.argv[1]):
            plaintext= str(input("plaintext: "))

            #analize plaintext
            vigenere_cipher(plaintext,sys.argv[1])
            return 0
        else:
            print("FAIL, NEXT AGAIN")
            return 1

def vigenere_cipher(plaintext,key):
    n_key=len(key)
    key_array = list()
    #analize key and save in
    #key_array the position in the alphabets-1 of every letter of key
    for i in range(n_key):
        orde=ord(key[i])
        if 97<=orde and orde<=122:
            key_array.append(orde-97)
        elif 65<=orde and orde<=90:
            key_array.append(orde-65)

    k=-1

    #implement vigenere algorithm using caesar algorithm

    #analize every letter of the input function
    n=len(plaintext)
    aux="ciphertext: "
    for i in range(n):
        #implement vigenere cripthography algorithm only with letters
        orde=ord(plaintext[i])
        if (97<=orde and orde<=122)or(65<=orde and orde<=90):
            k+=1
            if k==n_key:
                k=0

        #using caesar cripthography algorithm for implement the vigenere cripthography
        #algorithm in the plaintext sub i and the key sub k
        aux+=str(chr(caesar_cipher(ord(plaintext[i]),key_array[k])))
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

def validate(argv):

    #analize every letter of the input function
    n = len(argv)
    for i in range(n):
        #if only one character is not a letter the program return false, else return true
        if (97>ord(argv[i]) or ord(argv[i])>122) and (65>ord(argv[i]) or ord(argv[i])>90):
            return False

    return True

if __name__=="__main__":
    main()