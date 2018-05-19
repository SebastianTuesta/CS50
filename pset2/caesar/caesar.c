#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

void ciphertext(string plaintext,int shift);
char caesar_cipher(char letter,int shift);

int main(int argc,char* argv[]){
    if(argc!=2){
        //return error
        printf("INSERT ONLY the calling of the file and a non negative integer number");
        return 1;
    }
    else{
        string plaintext;
        printf("plaintext: ");
        plaintext=get_string();
        
        int n=atoi(argv[1]);
        
        //analize plaintext
        ciphertext(plaintext,n);
        return 0;
    
    }
}

void ciphertext(string plaintext,int shift){
    printf("ciphertext: ");
    
    //analize every letter of the input function
    for(int i=0,n=strlen(plaintext);i<n;i++){
        
        //caesar_cipher implements the caesar cripthography algorithm
        printf("%c",caesar_cipher(plaintext[i],shift));
    }
    printf("\n");
}

char caesar_cipher(char letter,int shift){
    //work with lower letters and retun the letter avance shift letters in the alphabet
    if('a'<=letter && letter<='z'){
        return 'a'+(letter-'a'+ shift)%26; 
    }
    //work with upper letters and retun the letter avance shift letters in the alphabet
    else if('A'<=letter && letter<='Z'){
        return 'A'+(letter-'A'+shift)%26;
    }
    //if the variable letter is not a lower or upper letter of the alphabet,the function don`t realize the caesar cripthography algorithm
    else return letter;
}

