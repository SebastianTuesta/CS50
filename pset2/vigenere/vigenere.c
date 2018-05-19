#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

void vigenere_cipher(string plaintext,string key);
char caesar_cipher(char letter,int shift);
bool validate(string argv);

int main(int argc,char* argv[]){
    if(argc!=2){
        //return error
        printf("FAIL, NEXT AGAIN");
        return 1;
    }
    else{
        
        //only accept argv[1] if all of its characters are letter
        if(validate(argv[1])){
            string plaintext;
            printf("plaintext: ");
            plaintext=get_string();
        
            printf("ciphertext: ");

            //analize plaintext
            vigenere_cipher(plaintext,argv[1]);
            return 0;
        }
        else{
            //return error
            printf("FAIL, NEXT AGAIN");
            return 1;
        }
    }
}

void vigenere_cipher(string plaintext,string key){
    
    int n_key=strlen(key);
    int key_array[n_key];
    
    //analize key and save in
    //key_array the position in the alphabets-1 of every letter of key 
    for(int i=0;i<n_key;i++){
        if('a'<=key[i] && key[i]<='z'){
            key_array[i]=key[i]-'a'; 
        }
        else if('A'<=key[i] && key[i]<='Z'){
            key_array[i]=key[i]-'A';
        }
    }
    
    int k=-1;
    
    //implement vigenere algorithm using caesar algorithm
    
    //analize every letter of the input function
    for(int i=0,n=strlen(plaintext);i<n;i++){
        
        //implement vigenere cripthography algorithm only with letters
        if(('a'<=plaintext[i] && plaintext[i]<='z')||('A'<=plaintext[i] && plaintext[i]<='Z')){
         k++;
         if(k==n_key) k=0;
        }
        
        //using caesar cripthography algorithm for implement the vigenere cripthography
        //algorithm in the plaintext sub i and the key sub k
        printf("%c",caesar_cipher(plaintext[i],key_array[k]));
    }
    printf("\n");
}

char caesar_cipher(char letter,int shift){
    //work with lower letters and retun the letter avance shift letters in the alphabet
    if('a'<=letter && letter<='z'){
        return 'a'+(letter-'a'+shift)%26; 
    }
    //work with upper letters and retun the letter avance shift letters in the alphabet
    else if('A'<=letter && letter<='Z'){
        return 'A'+(letter-'A'+shift)%26;
    }
    //if the variable letter is not a lower or upper letter of the alphabet,the function don`t realize the caesar cripthography algorithm
    else return letter;
}

bool validate(string argv){
    
    //analize every letter of the input function
    for(int i=0,n=strlen(argv);i<n;i++){
        //if only one character is not a letter the program return false, else return true 
        if(('a'>argv[i] || argv[i]>'z')&&('A'>argv[i] || argv[i]>'Z')){
            return false;
        }
    }   
    return true;
}